const net = require("net");
const fs = require("fs");
const path = require("path");
const readline = require("readline");

const PORT = 8080;
const HOST = "localhost";
const client = new net.Socket({ writeable: true });

const rl = readline.createInterface({
  input: process.stdin,
  output: process.stdout,
});

let currentFile;
let currentFileStream;
let uploadedBytes = 0;
let totalReceivedBytes = 0;
let isUploading = false; // Flag to check if the current operation is an upload

client.connect(PORT, HOST, () => {
  console.log("Connected to server");
  promptUser();
  client.setNoDelay(true);
});

function promptUser() {
  rl.question("", (answer) => {
    const [command, data] = answer.split(" ");

    if (command === "UPLOAD") {
      isUploading = true;
      currentFile = path.join(__dirname, data);
      client.write(`${command} ${data} ${fs.statSync(currentFile).size} `);
    } else if (command === "DOWNLOAD") {
      isUploading = false;
      currentFile = path.join(__dirname, data);
      client.write(`${command} ${data}`);
    } else if (command === "EXIT") {
      console.log("Завершение работы...");
      rl.close();
      client.end();
    } else {
      console.log(
        "Неверная команда. Пожалуйста, используйте UPLOAD или DOWNLOAD."
      );
      promptUser(); // Prompt the user again
    }
  });
}

client.on("data", (data) => {
  const [command, bytes] = data.toString().split(" ");

  switch (command) {
    case "CONTINUE":
      uploadedBytes = parseInt(bytes, 10);
      if (isUploading) {
        currentFileStream = fs.createReadStream(currentFile, {
          start: uploadedBytes,
        });
        currentFileStream.pipe(client);
      }
      break;
    case "RENEWUPLOAD":
      const [command, fileName] = data.toString().split(" ");
      isUploading = true;
      currentFile = path.join(__dirname, fileName);
      console.log(fileName);
      client.write(`UPLOAD ${fileName} `);
      break;
    default: // Ask the user if they want to continue or quit
      if (data.toString() === "Файл не найден") {
        console.log("Данные от сервера:", data.toString());
      } else if (!isUploading) {
        if (!currentFileStream) {
          currentFileStream = fs.createWriteStream(currentFile);
          currentFileStream.on("finish", () => {
            console.log("File downloaded successfully");
          });
        }
        currentFileStream.write(data);
      }
      break;
  }

  if (!isUploading) {
    totalReceivedBytes += data.length;
    process.stdout.write(
      `Общее количество полученных байт: ${totalReceivedBytes / 1000000}mb\r`
    );
  }
});

client.on("close", () => {
  console.log("Connection closed");
  if (currentFileStream && !isUploading) {
    currentFileStream.end();
  }
  client.end();
});

client.on("error", (err) => {
  console.error("Ошибка: не удается подсоединиться");
});
