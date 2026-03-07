import serial
import csv
import time

# -------- CONFIG --------
SERIAL_PORT = 'COM3'   # Change to your Arduino port (Linux/Mac example: '/dev/ttyACM0')
BAUD_RATE = 115200
CSV_FILE = 'sensor_data.csv'
# ------------------------

# Open serial connection
ser = serial.Serial(SERIAL_PORT, BAUD_RATE, timeout=1)

time.sleep(2)  # Allow Arduino time to reset

# CSV header
header = ["Pressure", "Temp1_F", "Humidity", "Temp2_F", "Floor"]

# Create CSV file and write header if empty
with open(CSV_FILE, 'a', newline='') as file:
    writer = csv.writer(file)
    writer.writerow(header)

current_data = {}

print("Logging started... Press CTRL+C to stop")

try:
    while True:
        line = ser.readline().decode('utf-8').strip()

        if not line:
            continue

        print(line)

        if "Pressure:" in line:
            current_data["Pressure"] = line.split(":")[1].strip()

        elif "Temp1:" in line:
            current_data["Temp1_F"] = line.split(":")[1].strip()

        elif "Humidity%:" in line:
            current_data["Humidity"] = line.split(":")[1].strip()

        elif "Temp2:" in line:
            current_data["Temp2_F"] = line.split(":")[1].strip()

        elif "Floor Number:" in line:
            current_data["Floor"] = line.split(":")[1].strip()

            # Once floor number arrives, we assume the full dataset is complete
            #timestamp = time.strftime("%Y-%m-%d %H:%M:%S")

            row = [
                #timestamp,
                current_data.get("Pressure"),
                current_data.get("Temp1_F"),
                current_data.get("Humidity"),
                current_data.get("Temp2_F"),
                current_data.get("Floor")
            ]

            with open(CSV_FILE, 'a', newline='') as file:
                writer = csv.writer(file)
                writer.writerow(row)

            print("Saved row:", row)

            current_data = {}

except KeyboardInterrupt:
    print("\nLogging stopped.")
    ser.close()