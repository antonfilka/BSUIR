const dgram = require("dgram");
const fs = require("fs");
const path = require("path");
const readline = require("readline");

const client = dgram.createSocket("udp4");
const SERVER_HOST = "localhost";
const SERVER_PORT = 12345;
const TIMEOUT = 5000; // Adjust as needed, especially for large files

const rl = readline.createInterface({
  input: process.stdin,
  output: process.stdout,
});

let socketClosed = false;
let lastPingTime = Date.now();
let isFileTransferInProgress = false;
let pingInterval;
let dataRate = 1; // Data rate control variable
let totalSentBytes = 0;
let sequenceNumber = 0; // Sequence number for datagrams

function startPing() {
  lastPingTime = Date.now();
  pingInterval = setInterval(() => {
    if (!isFileTransferInProgress && Date.now() - lastPingTime > TIMEOUT) {
      console.log("Timeout. No PONG received. Closing connection.");
      clearInterval(pingInterval);
      if (!socketClosed) {
        client.close();
        socketClosed = true;
      }
    } else if (!socketClosed) {
      client.send("PING", SERVER_PORT, SERVER_HOST);
    }
  }, TIMEOUT);
}

function readFileFromByte(filePath, startByte) {
  return new Promise((resolve, reject) => {
    const readStream = fs.createReadStream(filePath, { start: startByte });
    let data = "";

    readStream.on("data", (chunk) => {
      data += chunk;
    });

    readStream.on("end", () => {
      resolve(data);
    });

    readStream.on("error", (err) => {
      reject(err);
    });
  });
}

function sendFile(filePath) {
  const FILE_PATH = path.resolve(filePath);
  const fileName = path.basename(FILE_PATH);
  isFileTransferInProgress = true;

  client.send(`GET_PROGRESS ${fileName}`, SERVER_PORT, SERVER_HOST, (error) => {
    if (error) throw error;

    client.once("message", (msg) => {
      if (msg.toString().startsWith("PROGRESS:")) {
        const progress = parseInt(
          msg.toString().substring("PROGRESS:".length),
          10
        );
        sendChunk(FILE_PATH, progress, 1024); // Set chunk size to 1024 or adjust as needed
      }
    });
  });
}

function sendChunk(filePath, index, chunkSize) {
  fs.open(filePath, "r", (err, fd) => {
    if (err) {
      console.error("Error opening file:", err);
      return;
    }

    const buffer = Buffer.alloc(chunkSize);
    fs.read(fd, buffer, 0, chunkSize, index, (err, bytesRead) => {
      if (err) {
        console.error("Error reading file:", err);
        fs.close(fd, () => {});
        return;
      }

      if (bytesRead > 0) {
        const dataToSend = buffer.slice(0, bytesRead);
        const packet = Buffer.concat([
          Buffer.from([sequenceNumber]),
          dataToSend,
        ]);

        totalSentBytes += packet.length;
        process.stdout.write(
          `Sent: ${(totalSentBytes / (1024 * 1024)).toFixed(2)} MB\r`
        );

        client.send(packet, SERVER_PORT, SERVER_HOST, (error) => {
          if (error) {
            console.error("Error sending data:", error);
            fs.close(fd, () => {});
            return;
          }

          sequenceNumber = (sequenceNumber + 1) % 256;
          sendChunk(filePath, index + bytesRead, chunkSize);
        });
      } else {
        // End of file reached
        client.send("EOF", SERVER_PORT, SERVER_HOST, (error) => {
          fs.close(fd, () => {});
          if (error) {
            console.error("Error sending EOF:", error);
            return;
          }
          isFileTransferInProgress = false;
          stopPing();
        });
      }
    });
  });
}

function stopPing() {
  clearInterval(pingInterval);
  if (!socketClosed) {
    client.close();
  }
}

function adjustDataRate(change) {
  dataRate += change;
  dataRate = Math.max(1, dataRate); // Ensure dataRate doesn't fall below 1
}

client.on("message", (msg, rinfo) => {
  if (msg.toString() === "slow down") {
    adjustDataRate(-0.5); // Decrease data rate
  } else if (msg.toString() === "proceed") {
    adjustDataRate(0.5); // Increase data rate
  } else if (msg.toString() === "PONG") {
    console.log("PONG received");
    lastPingTime = Date.now();
  }
});

client.on("close", () => {
  console.log("Client socket closed.");
  socketClosed = true;
  clearInterval(pingInterval);
});

rl.question("Enter the path of the file to send: ", (filePath) => {
  sendFile(filePath);
  startPing();
  rl.close();
});
