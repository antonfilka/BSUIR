Bun.listen({
  hostname: "172.20.10.2",
  port: 8080,
  socket: {
    data(socket, data) {
      const parsedData = Buffer.from(data).toString();
      if (parsedData.startsWith("ECHO")) {
        const restOfData = parsedData.split("ECHO ")[1];
        console.log(restOfData);
        socket.write(restOfData);
      } else if (parsedData.startsWith("TIME")) {
        const currentTime = new Date().toTimeString() + "\n";
        console.log(currentTime);
        socket.write(currentTime);
      } else if (parsedData.startsWith("CLOSE")) {
        socket.end();
      } else {
        console.log("Command not found");
      }
    },
    open(socket) {
      console.log("Connection established");
    },
    close(socket) {
      console.log("Connection closed");
    },
  },
});
