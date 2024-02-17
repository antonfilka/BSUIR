var __extends = (this && this.__extends) || (function () {
    var extendStatics = function (d, b) {
        extendStatics = Object.setPrototypeOf ||
            ({ __proto__: [] } instanceof Array && function (d, b) { d.__proto__ = b; }) ||
            function (d, b) { for (var p in b) if (Object.prototype.hasOwnProperty.call(b, p)) d[p] = b[p]; };
        return extendStatics(d, b);
    };
    return function (d, b) {
        if (typeof b !== "function" && b !== null)
            throw new TypeError("Class extends value " + String(b) + " is not a constructor or null");
        extendStatics(d, b);
        function __() { this.constructor = d; }
        d.prototype = b === null ? Object.create(b) : (__.prototype = b.prototype, new __());
    };
})();
var __assign = (this && this.__assign) || function () {
    __assign = Object.assign || function(t) {
        for (var s, i = 1, n = arguments.length; i < n; i++) {
            s = arguments[i];
            for (var p in s) if (Object.prototype.hasOwnProperty.call(s, p))
                t[p] = s[p];
        }
        return t;
    };
    return __assign.apply(this, arguments);
};
var Transform = require("stream").Transform;
var fs = require("fs");
var path = require("path");
var UPLOAD_DIR = path.join(__dirname, "uploads");
if (!fs.existsSync(UPLOAD_DIR)) {
    fs.mkdirSync(UPLOAD_DIR);
}
var currentFile;
var fileName;
var currentFileStream;
var uploadedBytes = 0;
var isUploading = false; // Flag to check if the current operation is an upload
var totalReceivedBytes = 0;
var ByteCounter = /** @class */ (function (_super) {
    __extends(ByteCounter, _super);
    function ByteCounter() {
        var _this = _super.call(this) || this;
        _this.bytesSent = 0;
        return _this;
    }
    ByteCounter.prototype._transform = function (chunk, encoding, callback) {
        this.bytesSent += chunk.length;
        this.push(chunk);
        callback();
    };
    return ByteCounter;
}(Transform));
var byteCounter = new ByteCounter();
byteCounter.on("finish", function () {
    console.log("Sent ".concat(byteCounter.bytesSent, " bytes"));
});
[];
var bytesReceivedMap = new Map();
var clientUploadJobs = [];
var clientDownloadJobs = [];
function getActiveClientJobs(jobsArray, clientId) {
    return (jobsArray.filter(function (item) { return item.clientId === clientId && !item.isFinished; }) || null);
}
function markJobAsCompleted(jobsArray, clientId, fileName) {
    return jobsArray.map(function (item) {
        if (item.clientId === clientId && item.fileName === fileName) {
            return __assign(__assign({}, item), { isFinished: true });
        }
        else {
            return item;
        }
    });
}
process.on("message", function (msg, socket) {
    if (msg.command === "setName") {
        process.title = msg.name;
    }
    if (msg === "socket") {
        var clientId_1 = "".concat(socket.remoteAddress);
        console.log("Child process: Client connected");
        var hasUploadJobs = getActiveClientJobs(clientUploadJobs, clientId_1).length > 0;
        var hasDownloadJobs = getActiveClientJobs(clientDownloadJobs, clientId_1).length > 0;
        console.log("hasUploadJobs: ", hasUploadJobs);
        if (hasUploadJobs) {
            console.log("renewing upload.....");
            currentFile = path.join(UPLOAD_DIR, clientUploadJobs[0].fileName);
            socket.write("RENEWUPLOAD ".concat(clientUploadJobs[0].fileName));
        }
        socket.on("data", function (data) {
            var _a = data.toString().split(" "), command = _a[0], commandData = _a[1], totalFileBytes = _a[2];
            switch (command) {
                case "UPLOAD":
                    fileName = commandData;
                    if (bytesReceivedMap.has(fileName)) {
                        console.log("Continue write to file...");
                        uploadedBytes = bytesReceivedMap.get(fileName);
                    }
                    else {
                        uploadedBytes = 0;
                    }
                    isUploading = true;
                    currentFile = path.join(UPLOAD_DIR, fileName);
                    clientUploadJobs.push({
                        clientId: clientId_1,
                        fileName: fileName,
                        isFinished: false,
                        totalFileBytes: parseInt(totalFileBytes, 10)
                    });
                    if (fs.existsSync(currentFile)) {
                        uploadedBytes = fs.statSync(currentFile).size;
                    }
                    else {
                        uploadedBytes = 0;
                    }
                    currentFileStream = fs.createWriteStream(currentFile, {
                        flags: "a",
                        start: uploadedBytes
                    });
                    currentFileStream.on("finish", function () {
                        console.log("Write operation to ".concat(currentFile, " ended"));
                        if (fs.statSync(currentFile).size ===
                            clientUploadJobs[0].totalFileBytes) {
                            console.log("Write operation to ".concat(currentFile, " completed succefully"));
                            clientUploadJobs = [];
                        }
                    });
                    socket.write("CONTINUE ".concat(uploadedBytes));
                    break;
                case "DOWNLOAD":
                    isUploading = false;
                    currentFile = path.join(UPLOAD_DIR, commandData);
                    if (fs.existsSync(currentFile)) {
                        currentFileStream = fs.createReadStream(currentFile, {
                            start: uploadedBytes
                        });
                        currentFileStream.pipe(byteCounter).pipe(socket);
                    }
                    else {
                        socket.write("FILE NOT FOUND");
                    }
                    break;
                case "ECHO":
                    console.log(commandData);
                    socket.write(commandData);
                    break;
                case "TIME":
                    var currentTime = new Date().toTimeString() + "\n";
                    console.log(currentTime);
                    socket.write(currentTime);
                    break;
                case "CLOSE":
                    socket.end();
                    break;
                default:
                    if (currentFileStream && isUploading) {
                        currentFileStream.write(data);
                        var prevVal = bytesReceivedMap.get(fileName) || 0;
                        bytesReceivedMap.set(fileName, prevVal + data.length);
                    }
                    break;
            }
            if (isUploading) {
                totalReceivedBytes += data.length;
                process.stdout.write("Total bytes received: ".concat(totalReceivedBytes / 1000000, "mb\r"));
            }
        });
        socket.on("end", function () {
            if (currentFileStream && isUploading) {
                currentFileStream.end();
            }
            console.log("\nChild process: Client disconnected");
            process.send("finished");
        });
        socket.on("error", function (err) {
            console.error("Error:", err);
            process.send("finished");
        });
    }
});
