Updated 2026/05/28.

## Brief
The full workings of the node can be found within the authors' Bachelor thesis, linked in the main README.

config.h hosts all of the sytems changeable parameters.

The nodes core logic:
1. Wakeup
2. Disable peripherals
3. Sample the particle sensor
4. Sample the noise sensor
5. Encode the payload (add to the batch)
    6. Send the payload (when the batch is full)
7. Disable the radio
9. Sleep

## node/ structure

The project is organized into modular directories separating definitions (`include/`) from execution logic:

### Root Files
* **`main.cpp`**: The primary application entry point; handles system initialization and the core runtime loop.

### Include Directory (`include/`)
Contains all header files:

* **`config.h`**: Global configuration settings, pin definitions, constants, and system-wide parameters.
* **`master.h`**: Top-level header file including all other .h-files.
* **`drivers/`**: Interface definitions for peripheral hardware and sensor abstractions (e.g., air quality sensors).
* **`network/`**: Headers for managing connectivity, communication protocols, and data payloads.
* **`utils/`**: Helper macros, error utilities.
* **`experimental/`**: Sandbox interfaces and test setups for features currently under development.

## Initialisation w/ Arduinos IDE
0. Disable debug mode when in production. Can be done in include/utils/debug_macros.h

1. Navigate into node/ and execute the build script:

```powershell
.\build.ps1
```

2. Copy the path to build.ino within build/
3. Within Arduinos IDE:
    A. File
    B. Open
    C. Paste the path and open.
4. Now has all of the appropriate node files been opened within the IDE and the program can be flashed onto the microcontroller

## Other
See the main README for the teams contact info.