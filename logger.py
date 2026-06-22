import serial

ser = serial.Serial("COM5", 115200)

with open("pulse_log.csv", "a") as f:

    f.write("CPS,AVG,MAX,INT\n")

    while True:

        line = ser.readline().decode().strip()

        if line:
            print(line)
            f.write(line + "\n")
            f.flush()