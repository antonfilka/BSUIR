const dgram = require("dgram");
const fs = require("fs");
const path = require("path");

const server = dgram.createSocket("udp4");
const PORT = 12345;
const TIMEOUT = 5000; // 5 seconds
const MAX_PROCESSING_RATE = 1000000; // Example threshold for processing rate

let clients = {};
let fileProgress = {}; // Object to keep track of file progress

server.on("message", (msg, rinfo) => {
  const clientKey = `${rinfo.address}:${rinfo.port}`;
  let client = clients[clientKey];

  if (!client) {
    console.log(`New client connected: ${clientKey}`);
    client = clients[clientKey] = {
      lastPacketTime: Date.now(),
      fileName: null,
      fileStream: null,
      timeoutChecker: null,
      expectedSequenceNumber: 0,
      totalReceivedBytes: 0,
      startTime: Date.now(),
    };
    startTimeoutChecker(clientKey);
  } else {
    client.lastPacketTime = Date.now();
  }

  const messageText = msg.toString().trim();

  if (messageText.startsWith("GET_PROGRESS")) {
    const fileName = msg.toString().substring("GET_PROGRESS ".length).trim();
    client.fileName = fileName;
    handleProgressRequest(fileName, rinfo);
  } else if (messageText === "PING") {
    console.log(`PING received from ${clientKey}, sending PONG`);
    server.send("PONG", rinfo.port, rinfo.address);
  } else if (!client.fileName) {
    if (isValidFileName(messageText)) {
      client.fileName = messageText;
      client.fileStream = fs.createWriteStream(
        path.join(__dirname, client.fileName)
      );
      console.log(`Receiving file: ${client.fileName} from ${clientKey}`);
    } else {
      console.error(`Invalid file name received from ${clientKey}`);
      // Handle invalid file name scenario
    }
  } else if (messageText === "EOF") {
    console.log(`EOF received from ${clientKey}, closing connection.`);
    closeClientConnection(clientKey);
  } else {
    const receivedSequenceNumber = msg.readUInt8(0);
    if (receivedSequenceNumber !== client.expectedSequenceNumber) {
      console.error(`Sequence error for ${clientKey}`);
      // Optionally, handle sequence error
      return;
    }

    const data = msg.slice(1);
    client.totalReceivedBytes += data.length;
    process.stdout.write(
      `Received from ${clientKey}: ${(
        client.totalReceivedBytes /
        (1024 * 1024)
      ).toFixed(2)} MB\r`
    );
    client.fileStream.write(data);

    fileProgress[client.fileName] =
      (fileProgress[client.fileName] || 0) + data.length;
    client.expectedSequenceNumber = (client.expectedSequenceNumber + 1) % 256;
  }

  const serverOverwhelmed = checkServerLoad(clientKey);
  const feedbackMessage = serverOverwhelmed ? "slow down" : "proceed";
  server.send(feedbackMessage, rinfo.port, rinfo.address);
});

function isValidFileName(fileName) {
  return true; // Adjust this regex as needed
}

function handleProgressRequest(fileName, rinfo) {
  const progress = fileProgress[fileName] || 0;
  const client = clients[`${rinfo.address}:${rinfo.port}`];

  server.send(`PROGRESS:${progress}`, rinfo.port, rinfo.address);

  if (progress > 0) {
    console.log("RENEW UPLOAD ", fileName, " WITH PROGRESS ", progress);
    // If there is progress and no file stream, it means the client is reconnecting
    if (client.fileStream) client.fileStream.close();
    client.fileStream = fs.createWriteStream(
      path.join(__dirname, fileName),
      { flags: "a" } // Append mode
    );
  }

  client.fileStream = fs.createWriteStream(
    path.join(__dirname, client.fileName)
  );
}

function closeClientConnection(clientKey) {
  const client = clients[clientKey];
  if (client) {
    if (client.fileStream) {
      client.fileStream.close();
    }
    stopTimeoutChecker(clientKey);
    delete clients[clientKey];
  }
}

function startTimeoutChecker(clientKey) {
  clients[clientKey].timeoutChecker = setInterval(() => {
    if (
      !clients[clientKey] ||
      Date.now() - clients[clientKey].lastPacketTime > TIMEOUT
    ) {
      console.log(`Connection timeout for ${clientKey}. Closing connection.`);
      stopTimeoutChecker(clientKey);
      if (clients[clientKey]) {
        if (clients[clientKey].fileStream) {
          clients[clientKey].fileStream.close();
        }
        delete clients[clientKey];
      }
    }
  }, TIMEOUT);
}

function stopTimeoutChecker(clientKey) {
  if (clients[clientKey] && clients[clientKey].timeoutChecker) {
    clearInterval(clients[clientKey].timeoutChecker);
  }
}

function checkServerLoad(clientKey) {
  const client = clients[clientKey];
  if (!client) return false;

  const elapsedTime = Date.now() - client.startTime;
  const processingRate = client.totalReceivedBytes / (elapsedTime / 1000);
  return processingRate > MAX_PROCESSING_RATE;
}

server.on("listening", () => {
  const address = server.address();
  console.log(`Server listening ${address.address}:${address.port}`);
});

server.on("close", () => {
  console.log("Server socket is closed.");
});

server.bind(PORT);
