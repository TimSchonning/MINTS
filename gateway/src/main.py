# Code to send the received packet to Firebase
# Automatically runs (but does not compile) the gatewayLogic file
# TODO: Implement connection to Firebase.

import subprocess
from databaseConnection import DbConnection
from measurement import MeasurementGroup

# Change to oath where gatewayLogic.exe exists
cpp_exe_path = r"C:/Users/deode/Documents/kod/Kandidatebaete/MINTS/gateway/src/gatewayLogic.exe"

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
    print("Listening to LoRa packets.")
    
    return process

def toFirebase(node_id, pm10, pm25, noise):
    measurement_group = MeasurementGroup(node_id, pm10, pm25, noise)
    db_connection.save_measurements(measurement_group)
    
    print(f"Received ID: {node_id}, PM10: {pm10}, PM2.5: {pm25}, Noise: {noise}")

def main():
    process = run_lora(cpp_exe_path)
    
    for line in iter(process.stdout.readline, ""): # type: ignore
        line = line.strip()
        if line:
            # Split the CSV data
            try:
                node_id, pm10, pm25, noise = line.split(",")
                   
                toFirebase(node_id, pm10, pm25, noise)
                    
            except ValueError:
                print(f"Value Error: {line}") # Everything that isn't in the data packet struct gets printed here.
                    
if __name__ == "__main__":
    main()