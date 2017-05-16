var btSerial = new (require('bluetooth-serial-port')).BluetoothSerialPort();
var stream = require("stream");
var readline = require("readline");
var WebSocket = require('ws');
 




btSerial.on('found', function(address, name) {
	btSerial.findSerialPortChannel(address, function(channel) {
		btSerial.connect(address, channel, function() {
			console.error("Connected to ", address, name);
			var btinStream = new stream.Readable();
			btinStream._read = function noop(){};
			var btinLines = readline.createInterface({input:btinStream});
			var stdinLines = readline.createInterface({input:process.stdin});
			btSerial.on('data', function(buffer) {
				btinStream.push(buffer.toString("utf-8"));
			});
			
			var ws = new WebSocket('ws://turrisserver.ddns.net:9191/');

			//var ws = {on:function(){}};
			ws.on('open', function open() {
				ws.on('message', function incoming(data, flags) {
					//received data from console (later server)
					
					
					
					
					//don't mess with this!
					btSerial.write(new Buffer(data, "utf-8"), function(err, bytes){
						if(bytes != data.length){
							console.error("did not write all the data...");
						}
						if(err){
							console.error(err);
						}
					});
				});
				
				
				btinLines.on("line", function(data){
					//message from arduino
					console.log("from arduino: ", data)
					ws.send(data.toString("utf-8"));
					
					
					
					//console.log(data);
				});
				
			
			});
			
			
			
			
			
			
		}, function () {
			console.error(address, 'cannot connect');
		});

		// close the connection when you're ready
		btSerial.close();
	}, function() {
		console.error('found nothing');
	});
});

btSerial.inquire();