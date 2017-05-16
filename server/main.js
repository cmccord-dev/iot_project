var express = require('express')
var app = express()
var readline = require("readline");
app.get('/', function (req, res) {
  res.send('Hello World!')
})
app.use(express.static("public"));
/*app.listen(9090, function () {
  console.log('Example app listening on port 9090!')
})
/**/

//https://www.websocket.org/echo.html
const WebSocket = require("ws");
const wss = new WebSocket.Server({
	port:9191 });
//const wss2 = new WebSocket.Server({
//	port:9292 });

//gateway connection
wss.on("connection", function(ws){
	ws.on("message", function(message){
		console.log("received: %s", message);
	});
	var stdinLines = readline.createInterface({input:process.stdin});
	stdinLines.on("line", function(data){ws.send(data.toString("utf-8"))});
});
/*
//website connection
wss2.on("connection", function(ws){
	ws.on("message", function(message){
		console.log("received: ", message);
	});
});
/**/
