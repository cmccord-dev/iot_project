import bluetooth
 
bd_addr = "00:06:66:7B:AE:A6" #The address from the HC-05 sensor
port = 1
sock = bluetooth.BluetoothSocket (bluetooth.RFCOMM)
sock.connect((bd_addr,port))
 
data = ""
while 1:
	try:
		sock.send("1");
	except KeyboardInterrupt:
		break
sock.close()