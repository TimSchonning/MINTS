#!/bin/bash

echo "Initialising gateway..."

cd /home/mints/MINTS/

git pull

cd /home/mints/MINTS/gateway/src/

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

if [ $? -eq 0 ]; then
    echo "Compiled. Starting Python."
    sudo python3 main.py
else
    echo "Compile failed."
    exit 1
fi