#!/usr/bin/env python3
import sys
import time

import serial
import threading



RED = "\x1b[31m"
GREEN = "\x1b[32m"
YELLOW = "\x1b[33m"
WHITE = "\x1b[37m"
PORT_PATH = "/dev/ttys"
STATIONS = ('010', '013', '011', '014')

MS = 4
received_ack = []


def reader_routine(r_port: serial.Serial, w_port: serial.Serial):
    print(f"Start reader routine")
    message_part = ''
    message = ''

    while True:
        message_part = ''
        while r_port.inWaiting():
            message_part = message_part + r_port.read().decode()

        if message_part != '':
            if message_part[5:8] == 'ACK':
                print(f"ACK CONFIRMED --> received: {message_part[-4:]}  ")
                received_ack.append(message_part[2:5])
                continue

            ack_message = message_part[0:5] + 'ACK' + message_part[8:]
            w_port.write(ack_message.encode())

            message += message_part[11:]
            if message_part[8:11] == "FIN":
                print(f"Message: {message}\n> ")
                message = ''

            if message_part == 'exit':
                break


def main():
    if len(sys.argv) < 2:
        print(f"{RED}Error. Need to pass is station number (0/1){WHITE}")
        exit(-1)

    reader_file = PORT_PATH + STATIONS[-int(sys.argv[1])]
    writer_file = PORT_PATH + STATIONS[2 - int(sys.argv[1])]

    # writer_file = PORT_PATH + str(int('2') + int(sys.argv[1]))
    print(f"Writer port: {writer_file[-1]}")
    w_port = serial.Serial(writer_file)

    # Start reader routine
    r_port = serial.Serial(reader_file)
    print(f"Reader port: {reader_file[-1]}")
    reader = threading.Thread(target=reader_routine, args=(r_port, w_port))
    reader.start()

    # Writer routine
    while True:
        message = input("Input message\n> ")

        # Sent by 3 parts of message (static windows)
        message_parts = [message[i:i + MS * 3] for i in range(0, len(message), MS * 3)]
        idx = 0
        for part in message_parts:
            window = []

            for line in [part[i:i + MS] for i in range(0, len(part), MS)]:
                idx = format(idx).zfill(3)
                FIN = 'FIN' if len(line) < 3 else 'XXX'
                window.append(STATIONS[-1 + int(sys.argv[1])] + STATIONS[1 + int(sys.argv[1])] + \
                              idx + 'XXX' + FIN + line)
                print(window[-1])

                idx = int(idx) + 1

            while True:
                for package in window:
                    w_port.write(package.encode())
                    time.sleep(0.01)
                time.sleep(1)

                check_window = window.copy()

                for package in window:
                    if package[2:5] in received_ack:
                        check_window.remove(package)
                        received_ack.remove(package[2:5])

                if len(check_window) == 0:
                    print(f"Window sent")
                    break

        # w_port.write(message.encode())
        if message == 'exit':
            break

        print(f"Transmitted message: {message}\n")

    reader.join()


if __name__ == '__main__':
    main()