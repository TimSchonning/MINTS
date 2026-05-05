# Script that automatically compiles and runs the neccessary gateway files

#!/bin/bash

cd /home/mints/MINTS/gateway/src/

echo "Compiles gatewayLogic and its dependencies..."

g++ gatewayLogic.cpp \
../RadioLib/src/Hal.cpp \
../RadioLib/src/Module.cpp \
../RadioLib/src/utils/Utils.cpp \
../RadioLib/src/utils/CRC.cpp \
../RadioLib/src/utils/FEC.cpp \
../RadioLib/src/protocols/PhysicalLayer/PhysicalLayer.cpp \
../RadioLib/src/modules/SX126x/SX126x.cpp \
../RadioLib/src/modules/SX126x/SX1262.cpp \
../RadioLib/src/modules/SX126x/SX126x_commands.cpp \
../RadioLib/src/modules/SX126x/SX126x_config.cpp \
../RadioLib/src/modules/SX126x/SX126x_LR_FHSS.cpp \
-I../RadioLib/src \
-I../include \
-DRADIOLIB_STATIC \
-llgpio -lpthread \
-o gatewayLogic.out

# Kontrollera om kompileringen lyckades
if [ $? -eq 0 ]; then
    echo "Kompilering klar. Startar Python..."
    # Kör python-skriptet med sudo för att säkra GPIO-tillgång
    sudo python3 main.py
else
    echo "Kompilering misslyckades!"
    exit 1
fi