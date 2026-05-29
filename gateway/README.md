Updated 2026/05/28.

## Brief
The full workings of the node can be found within the authors' Bachelor thesis, linked in the main README.

The gateways core logic:
1. Always-on listening
2. Receives and parses packet
3. Packet handling
If the packet is a node payload:
4. Check if received before - discard if true.
5. Send data to database
If the packet is an error message:
4. Log the error

## gateway/ structure
The project is organized into modular directories separating definitions (`include/`) from execution logic:

### Include Directory (`include/`)
Contains all header files:

* **`config.h`**: Global configuration settings
* **`debug_macros.h`**: Helper macros.
* **`protocol.h`**: Protocol definitions.
* **`utils/`**: Helper utilities, error utilities.

### Source Directory (`src/`)

* **`experimental/`**: Sandbox interfaces and test setups for features currently under development.
* **`databaseConnection.py`**: Initializes the Firebase Admin SDK and provides a method to batch-upload grouped sensor measurements into a Firestore database.
* **`gatewayLogic.cpp`**: Manages the hardware-level LoRa transceiver to receive, filter, and validate incoming wireless sensor packets before outputting them as CSV strings.
* **`main.py`**: main executable. Executes the C++ LoRa gateway process, parses received sensor data packets, and uploads them to Firebase.
* **`measurement.py`**: Defines a class to group and timestamp sensor readings (PM2.5, PM1, and Noise) by station.
* **`run_gateway.sh`**: Bash script that pulls the latest project updates, compiles the gatewayLogic executable with the RadioLib library, and launches the main Python application.

## Initialisation w/ Raspberry PI
0. TODO
1. TODO
2. TODO

## Other
See the main README for the teams contact info.