import bluetooth
import time
import threading

bd_addr = "00:06:66:7B:AE:A6" #The address from the HC-05 sensor
port = 1
sock = bluetooth.BluetoothSocket (bluetooth.RFCOMM)
delay = time.sleep
t = 1

def read_thread(sock, t):
	data = ""
	while 1:
		try:
			data = sock.recv(1024);
			if(data):
				print(data);
		except KeyboardInterrupt:
			break

def write_thread(sock, t):
	while 1:
		try:
			sock.send("1");
			delay(1);
			sock.send("0");
			delay(1);
			
		except KeyboardInterrupt:
			break



while 1:
	try:
		sock.connect((bd_addr,port))
		break
	except:
		print("Can't connect");
		delay(1);
print("Connected..")

t_a = threading.Thread(target=read_thread, args=(sock, t))
t_b = threading.Thread(target=write_thread, args=(sock,t))
t_a.start();
t_b.start();