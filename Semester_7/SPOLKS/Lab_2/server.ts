import { Transform } from "stream";

const { fork } = require("child_process");
const net = require("net");
const fs = require("fs");
const path = require("path");

process.title = "SPOLKSPARENT";
const server = net.createServer();

const PORT = 8080;
const UPLOAD_DIR = path.join(__dirname, "uploads");
const MAX_PROCESSES = 10; // Nmax
const PROCESS_TIMEOUT = 5000; // Таймаут в миллисекундах

let activeProcesses = 0;
let waitingProcesses: any = [];

server.on("connection", (socket: any) => {
  const clientId = `${socket.remoteAddress}`;
  console.log(`Parent process: Client ${clientId} connected`);

  if (activeProcesses < MAX_PROCESSES) {
    const childProcess = fork("./child.js");
    activeProcesses++;
    childProcess.send({
      command: "setName",
      name: `SPOLKSCHILD-${activeProcesses}`,
    });
    childProcess.send("socket", socket);

    childProcess.on("message", (msg) => {
      if (msg === "finished") {
        activeProcesses--;
        if (waitingProcesses.length > 0 && activeProcesses < MAX_PROCESSES) {
          const nextSocket = waitingProcesses.shift();
          childProcess.send("socket", nextSocket);
        } else {
          setTimeout(() => {
            childProcess.kill();
          }, PROCESS_TIMEOUT);
        }
      }
    });

    childProcess.on("exit", () => {
      activeProcesses--;
    });
  } else {
    if (waitingProcesses.length < MAX_PROCESSES * 2) {
      waitingProcesses.push(socket);
    } else {
      socket.end("Server overloaded");
    }
  }
});

server.listen(PORT, () => {
  console.log(`Server started on port ${PORT}`);
});
