// client.js
const net = require("net");
const PORT = 8080;
const HOST = "localhost";
const TOTAL_CONNECTIONS = 100;
const CONNECT_DELAY_MS = 100; // Delay in milliseconds between connection attempts
const DISCONNECT_DELAY_MS = 100; // Delay in milliseconds between disconnections
const WAIT_BEFORE_DISCONNECT_MS = 5000; // Wait 5 seconds before starting disconnections

let connections = [];

function connectToServer(i) {
  const client = net.createConnection({ port: PORT, host: HOST }, () => {
    console.log(`Connected to server! Connection number: ${i + 1}`);
    if (i === TOTAL_CONNECTIONS - 1) {
      // All connections are established, start the disconnection process after a delay
      setTimeout(disconnectAll, WAIT_BEFORE_DISCONNECT_MS);
    }
  });

  client.on("data", (data) => {
    console.log(data.toString());
  });

  client.on("end", () => {
    console.log(`Disconnected from server. Connection number: ${i + 1}`);
  });

  connections.push(client);
}

function disconnectAll() {
  connections.forEach((client, i) => {
    setTimeout(() => {
      client.end();
    }, i * DISCONNECT_DELAY_MS);
  });
}

for (let i = 0; i < TOTAL_CONNECTIONS; i++) {
  setTimeout(() => {
    connectToServer(i);
  }, i * CONNECT_DELAY_MS);
}
