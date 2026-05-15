# Code to send the received packet to Firebase
# Automatically runs (but does not compile) the gatewayLogic file

import subprocess
from databaseConnection import DbConnection
from measurement import MeasurementGroup

# Change to oath where gatewayLogic.exe exists
cpp_exe_path = r"./gatewayLogic.out"

db_connection = DbConnection()

# Creates a process and:
#   Runs gatewayLogic.exe
#   Establishes connection between the files
# Returns the created process
def run_lora(gatewayLogicPath):
    process = subprocess.Popen(
        [cpp_exe_path],
        stdout=subprocess.PIPE,
        stderr=subprocess.STDOUT,
        text=True,
        bufsize=1
    )
    
    print("Python is now connected with LoRa...")
    print("Listening for LoRa packets.")
    
    return process

def toFirebase(batch_nr, node_id, pm1, pm25, noise):
    measurement_group = MeasurementGroup(batch_nr, node_id, pm1, pm25, noise)
    db_connection.save_measurements(measurement_group)
    
    print(f"Received ID: {node_id}, PM1: {pm1}, PM2.5: {pm25}, Noise: {noise}")

def main():
    process = run_lora(cpp_exe_path)
    
    for line in iter(process.stdout.readline, ""): # type: ignore
        print(f"Line (whole batch): {line}")
        line = line.strip()
                
        if line:
            # Split the CSV data
            try:
                parts = line.split(",")
                print(f"Parts (whole set within batch): {parts}")

                if len(parts) % 5 != 0:
                    print(f"[Warning]: Incomplete batch received. Total values: {len(parts)} (need to be multiple of five)")

                for i in range(0, len(parts), 5):
                    batch = parts[i : i + 5]
                    print(f"length of batch: {len(batch)}")
                    if len(batch) == 5:
                        batch_nr, node_id, pm1, pm25, noise = batch
                        toFirebase(batch_nr, node_id, pm1, pm25, noise)
                    
            except ValueError:
                print(f"Value Error: {line}") # Everything that isn't in the data packet struct gets printed here.
                    
if __name__ == "__main__":
    main()