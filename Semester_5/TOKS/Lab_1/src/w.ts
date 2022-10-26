import Network from "./network";

const network = new Network("w");

async function main() {
  await Promise.all(
    [110, 300, 4800, 9600, 57600, 57600].map(async (baudRate) => {
      await network.write();
      await network.updateBaudRate(baudRate);
      return;
    })
  );
}

main().catch((err) => console.error(err));
