import time
import usb.core
import usb.util

VID = 0x0de7
PID = 0x0191

dev = usb.core.find(idVendor = VID, idProduct = PID)
if not dev:
	print("Could not find device")
	exit(1)
print("found it")


command = [0x05, 0, 0, 0, 0, 0, 0, 0]

dev.ctrl_transfer(0x21, 9, 0x0200, 0, command)


exit(0)
