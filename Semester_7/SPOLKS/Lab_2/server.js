"use strict";
exports.__esModule = true;
var fork = require("child_process").fork;
var net = require("net");
var fs = require("fs");
var path = require("path");
process.title = "SPOLKSPARENT";
var server = net.createServer();
var PORT = 8080;
var UPLOAD_DIR = path.join(__dirname, "uploads");
var MAX_PROCESSES = 15; // Nmax
var PROCESS_TIMEOUT = 5000; // Таймаут в миллисекундах
var activeProcesses = 0;
var waitingProcesses = [];
server.on("connection", function (socket) {
    var clientId = "".concat(socket.remoteAddress);
    console.log("Parent process: Client ".concat(clientId, " connected"));
    if (activeProcesses < MAX_PROCESSES) {
        var childProcess_1 = fork("./child.js");
        activeProcesses++;
        childProcess_1.send({
            command: "setName",
            name: "SPOLKSCHILD-".concat(activeProcesses)
        });
        childProcess_1.send("socket", socket);
        childProcess_1.on("message", function (msg) {
            if (msg === "finished") {
                activeProcesses--;
                if (waitingProcesses.length > 0 && activeProcesses < MAX_PROCESSES) {
                    var nextSocket = waitingProcesses.shift();
                    childProcess_1.send("socket", nextSocket);
                }
                else {
                    setTimeout(function () {
                        childProcess_1.kill();
                    }, PROCESS_TIMEOUT);
                }
            }
        });
        childProcess_1.on("exit", function () {
            activeProcesses--;
        });
    }
    else {
        if (waitingProcesses.length < MAX_PROCESSES * 2) {
            waitingProcesses.push(socket);
        }
        else {
            socket.end("Server overloaded");
        }
    }
});
server.listen(PORT, function () {
    console.log("Server started on port ".concat(PORT));
});
