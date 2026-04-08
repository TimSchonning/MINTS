import serial
import winsound

port = 'COM3' 
baud = 115200

freq = 2500
time = 200

def pling(frequency, duration, iterations):
    counter = 0
    while iterations - counter != 0:
        winsound.Beep(frequency - 1000, duration)
        winsound.Beep(frequency, duration)
        winsound.Beep(frequency + 1000, duration)
        counter += 1

pling(freq, time, 1)

try:
    ser = serial.Serial(port, baud, timeout=1)
    print(f"Listening on {port}...")
    
    while True:
        line = ser.readline().decode('utf-8', errors='ignore').strip()
        if "Hittat!" in line:
            print("🚨 LADIES AND GENTLEMEN, WE GOT 'EM!")
            pling(freq, time, 3)
            
except KeyboardInterrupt:
    print("Stopped.")