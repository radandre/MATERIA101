#!/bin/bash

if [ "$1" = "" ]; then
   FILE=applet/Marlin.hex
else
   FILE=$1
fi

avrdude -D -C /etc/avrdude.conf \
        -p atmega2560 -P /dev/ttyACM0 -c wiring \
        -b 115200 \
        -U flash:w:$FILE:i
