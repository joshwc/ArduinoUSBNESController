# ArduinoUSBNESController
NES controller to USB gamepad with Arduino Leonardo

Converts the output of 2 NES controllers into USB HID input 
so that the controllers become recognized as two seperate gamepads by computers.

Tested on windows, and PS3

Simply connect controller pins according to the description at the top of the .ino file
and replace the standard HID.cpp and USBAPI.h files (found in C:\Program Files (x86)\Arduino\hardware\arduino\avr\cores\arduino) with the versions provided.

It is reccomended that you keep the original files.
Simply rename original files to HID_ORIGINAL.CPP and USBAPI_ORIGINAL.H before copying the new files

