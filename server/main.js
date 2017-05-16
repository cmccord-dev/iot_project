var express = require('express')
var app = express()

app.get('/', function (req, res) {
  res.send('Hello World!')
})
app.use(express.static("public"));
app.listen(9090, function () {
  console.log('Example app listening on port 9090!')
})

const WebSocket = require("ws");
const wss = new WebSocket.Server({
	port:9090 });

wss.on("connection", function(ws){
	ws.on("message", function(message){
		console.log("received: %s", message);
	});
});
