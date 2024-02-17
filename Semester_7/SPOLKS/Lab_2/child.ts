const { Transform } = require("stream");
const fs = require("fs");
const path = require("path");
const UPLOAD_DIR = path.join(__dirname, "uploads");

if (!fs.existsSync(UPLOAD_DIR)) {
  fs.mkdirSync(UPLOAD_DIR);
}

let currentFile;
let fileName;
let currentFileStream;
let uploadedBytes = 0;
let isUploading = false; // Flag to check if the current operation is an upload
let totalReceivedBytes = 0;

class ByteCounter extends Transform {
  bytesSent: number;

  constructor() {
    super();
    this.bytesSent = 0;
  }

  _transform(chunk: any, encoding: string, callback: () => void) {
    this.bytesSent += chunk.length;
    this.push(chunk);
    callback();
  }
}
const byteCounter = new ByteCounter();

byteCounter.on("finish", () => {
  console.log(`Sent ${byteCounter.bytesSent} bytes`);
});

interface job {
  clientId: string;
  fileName: string;
  isFinished: boolean;
  totalFileBytes: number;
}
[];

const bytesReceivedMap = new Map();
let clientUploadJobs: job[] = [];
let clientDownloadJobs: job[] = [];

function getActiveClientJobs(jobsArray: job[], clientId: string) {
  return (
    jobsArray.filter(
      (item) => item.clientId === clientId && !item.isFinished
    ) || null
  );
}

function markJobAsCompleted(
  jobsArray: job[],
  clientId: string,
  fileName: string
) {
  return jobsArray.map((item) => {
    if (item.clientId === clientId && item.fileName === fileName) {
      return { ...item, isFinished: true };
    } else {
      return item;
    }
  });
}

process.on("message", (msg: any, socket: any) => {
  if (msg.command === "setName") {
    process.title = msg.name;
  }

  if (msg === "socket") {
    const clientId = `${socket.remoteAddress}`;
    console.log(`Child process: Client connected`);

    const hasUploadJobs =
      getActiveClientJobs(clientUploadJobs, clientId).length > 0;
    const hasDownloadJobs =
      getActiveClientJobs(clientDownloadJobs, clientId).length > 0;

    console.log("hasUploadJobs: ", hasUploadJobs);

    if (hasUploadJobs) {
      console.log("renewing upload.....");
      currentFile = path.join(UPLOAD_DIR, clientUploadJobs[0].fileName);
      socket.write(`RENEWUPLOAD ${clientUploadJobs[0].fileName}`);
    }

    socket.on("data", (data) => {
      const [command, commandData, totalFileBytes] = data.toString().split(" ");

      switch (command) {
        case "UPLOAD":
          fileName = commandData;
          if (bytesReceivedMap.has(fileName)) {
            console.log("Continue write to file...");
            uploadedBytes = bytesReceivedMap.get(fileName);
          } else {
            uploadedBytes = 0;
          }
          isUploading = true;
          currentFile = path.join(UPLOAD_DIR, fileName);
          clientUploadJobs.push({
            clientId,
            fileName,
            isFinished: false,
            totalFileBytes: parseInt(totalFileBytes, 10),
          });
          if (fs.existsSync(currentFile)) {
            uploadedBytes = fs.statSync(currentFile).size;
          } else {
            uploadedBytes = 0;
          }
          currentFileStream = fs.createWriteStream(currentFile, {
            flags: "a",
            start: uploadedBytes,
          });
          currentFileStream.on("finish", () => {
            console.log(`Write operation to ${currentFile} ended`);
            if (
              fs.statSync(currentFile).size ===
              clientUploadJobs[0].totalFileBytes
            ) {
              console.log(
                `Write operation to ${currentFile} completed succefully`
              );
              clientUploadJobs = [];
            }
          });
          socket.write(`CONTINUE ${uploadedBytes}`);
          break;
        case "DOWNLOAD":
          isUploading = false;
          currentFile = path.join(UPLOAD_DIR, commandData);
          if (fs.existsSync(currentFile)) {
            currentFileStream = fs.createReadStream(currentFile, {
              start: uploadedBytes,
            });
            currentFileStream.pipe(byteCounter).pipe(socket);
          } else {
            socket.write("FILE NOT FOUND");
          }
          break;
        case "ECHO":
          console.log(commandData);
          socket.write(commandData);
          break;
        case "TIME":
          const currentTime = new Date().toTimeString() + "\n";
          console.log(currentTime);
          socket.write(currentTime);
          break;
        case "CLOSE":
          socket.end();
          break;
        default:
          if (currentFileStream && isUploading) {
            currentFileStream.write(data);
            const prevVal = bytesReceivedMap.get(fileName) || 0;
            bytesReceivedMap.set(fileName, prevVal + data.length);
          }
          break;
      }

      if (isUploading) {
        totalReceivedBytes += data.length;
        process.stdout.write(
          `Total bytes received: ${totalReceivedBytes / 1_000_000}mb\r`
        );
      }
    });

    socket.on("end", () => {
      if (currentFileStream && isUploading) {
        currentFileStream.end();
      }
      console.log("\nChild process: Client disconnected");
      process.send("finished");
    });

    socket.on("error", (err) => {
      console.error("Error:", err);
      process.send("finished");
    });
  }
});
