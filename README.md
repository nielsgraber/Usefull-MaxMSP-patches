# Usefull-MaxMSP-patches
A collection of usefull MaxMSP patches / subpatches to use in your projects. 


MIDI patch has three usefull objects to work with MIDI
- One patch to read the incoming MIDI signals value, channel and device
- One patch to use buttons that give a 127 value on press and a 0 value on release as a singular push
- One patch that then latches when a button is pressed


Max_OSC_Receiver
- Patch to receive incoming OSC signals into MaxMSP, to then use these values in sound processing


Max_to_arduino patch + accompanying arduino sketch can be used to control physical devices from the MaxMSP environment
- I made a custom protocol using brackets and channel numbers to easily and robustely send data from MaxMSP to arduino to control physical objects like motors, leds and relais

