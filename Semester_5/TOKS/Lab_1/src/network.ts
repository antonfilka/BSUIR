import { exec } from "child_process";
import { SerialPort } from "serialport";

class Network {
  port: any;

  constructor(option: string) {
    if (option === "w") {
      this.port = new SerialPort({
        path: `/dev/ttys001`,
        baudRate: 57600,
      });
    } else if (option === "r") {
      this.port = new SerialPort({
        path: `/dev/ttys002`,
        baudRate: 57600,
      });
    }
  }

  async listSerialPorts() {
    await SerialPort.list().then((ports) => {
      console.log("ports", ports);
    });
  }

  async write() {
    return this.port.write(Buffer.from("byte "), function (err: any) {
      if (err) {
        return console.log("Error on write: ", err.message);
      }
      console.log("message sent");
    });
  }

  read() {
    const subprocess = exec("cat < /dev/ttys002");

    if (subprocess.stdout)
      subprocess.stdout.on("data", (data) =>
        console.log(Buffer.from(data).toString())
      );
  }

  async updateBaudRate(baudRate: number) {
    if (this.port.isOpen) {
      this.port.update({ baudRate });
    }

    return;
  }
}

export default Network;
