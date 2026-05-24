Updated 2026/05/24.

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

## Initialisation w/ Arduinos IDE
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