# Här ska koden som kopplar Raspberryn till Firebase vara

import subprocess

# Change to your setup
cpp_exe_path = r"C:/Users/deode/Documents/kod/Kandidatebaete/MINTS/gateway/src/main.exe"

def run_lora():
    process = subprocess.Popen(
        [cpp_exe_path],
        stdout=subprocess.PIPE,
        stderr=subprocess.STDOUT,
        text=True,
        bufsize=1
    )
    
    print("Python is now connected with LoRa...")
    print("Listening to LoRa packets.")
    

    for line in iter(process.stdout.readline, ""): # type: ignore
        line = line.strip()
        if line:
            # Split the CSV data
            try:
                node_id, pm10, pm25, noise = line.split(",")
                   
                # Lägg in här vad vi ska skicka till firebase
                # Nu kommer det bara printas
                  
                print(f"Received ID: {node_id}, PM10: {pm10}, PM2.5: {pm25}, Noise: {noise}")
                    
            except ValueError:
                print(f"Value Error: {line}") # Everything that isn't in the data packet struct gets printed here.
                    
if __name__ == "__main__":
    run_lora()