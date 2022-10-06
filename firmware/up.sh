#!/bin/sh
#cppcheck  --force --std=c99 --language=c --platform=avr8 src/ lib/
make clean
rm -rf bin obj
make all
#fuser -k /dev/ttyACM0
#avrdude -c arduino -P /dev/ttyUSB0 -p m328p -D -U flash:w:bin/firmware.elf
avrdude -c arduino -P /dev/ttyS13 -p m328p -D -U flash:w:bin/firmware.elf

# testando com arduino nano
# avrdude -c arduino -P /dev/ttyUSB0 -b 57600 -p m328p -D -U flash:w:bin/firmware.elf

#figlet "MVC19"
stty 57600 < /dev/ttyS13 && cat /dev/ttyS13 
#stty -F /dev/ttyS13 57600
#cat /dev/ttyS13
