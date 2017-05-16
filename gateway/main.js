var btSerial = new (require('bluetooth-serial-port')).BluetoothSerialPort();
var stream = require("stream");
var readline = require("readline");




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
			
			
			
			
			
			stdinLines.on("line", function(data){
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
				
				
				
				
				console.log(data);
			});
			
			
			
			
			
			
			
			
		}, function () {
			console.error('cannot connect');
		});

		// close the connection when you're ready
		btSerial.close();
	}, function() {
		console.error('found nothing');
	});
});

btSerial.inquire();