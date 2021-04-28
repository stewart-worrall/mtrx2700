# This is a Python script to parse the example messages from a file.

import struct

MSG_HEADER_SIZE = 16


def parse_data(file_name):
    # open the file
    with open(file_name, "rb") as f:
        while True:
            header_bytes = f.read(MSG_HEADER_SIZE)

            if len(header_bytes) < MSG_HEADER_SIZE:
                # must be out of messages
                break

            header_data = struct.unpack(">H8sHHH", header_bytes)
            print("header sentinels: " + str(hex(header_data[0])) + ", " + str(hex(header_data[4])))
            message_type = header_data[1].split(b'\0', 1)[0]  # remove the null characters from the string
            print(message_type)
            print("message size: " + str(header_data[2]))

            if message_type == b"text":
                text_bytes = f.read(header_data[2])
                print("text message: " + str(text_bytes))
            elif message_type == b"gyro":
                gyro_bytes = f.read(header_data[2])
                print("gyro message: " + str(gyro_bytes[1]) + ", " + str(gyro_bytes[2]) + ", " + str(gyro_bytes[3]) + ", time=" + str(gyro_bytes[4]))
            elif message_type == b"buttons":
                buttons_bytes = f.read(header_data[2])
                print("buttons message: " + str(hex(buttons_bytes[1])) + ", time=" + str(buttons_bytes[2]))



# main program entry point
if __name__ == '__main__':
    #parse_data('/home/stew/src/mtrx2700/serialise-example/data.dat')
    parse_data('/home/stew/received.log')

