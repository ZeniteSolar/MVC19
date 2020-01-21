cd lib/avr-can-lib/src/
make clean
make lib
cd ../../oled_display
make clean
make
cd ../../../
cd src
rm can_ids.h
wget https://raw.githubusercontent.com/ZeniteSolar/CAN_IDS/master/can_ids.h
cd ..
