
  var wsUri = "ws://turrisserver.ddns.net:9292";
  var output;

  function init()
  {
    testWebSocket();
  }

  function testWebSocket()
  {
    websocket = new WebSocket(wsUri);
    websocket.onopen = function(evt) { onOpen(evt) };
    websocket.onclose = function(evt) { onClose(evt) };
    websocket.onmessage = function(evt) { onMessage(evt) };
    websocket.onerror = function(evt) { onError(evt) };
  }

  function onOpen(evt)
  {
	console.log("opened");
  }

  function onClose(evt)
  {
	  console.log("closed");
  }

  function onMessage(evt)
  {
	var msg = evt.data; 
	console.log("received", msg);
	if(msg == "ALARM!") document.getElementById("alarmSection").innerHTML = "Alarm Activated!!";
	if(msg == "Alarm deactivated") document.getElementById("alarmSection").innerHTML = "Alarm Deactivated!!";
	
  }

  function onError(evt)
  {
	  console.log(evt.data);
  }

  function doSend(message)
  {
	  console.log("sending", message);
    websocket.send(message);
  }

  window.addEventListener("load", init, false);
  
  function activateAlarm(){
	  doSend("0");
  }
  function openDoor(){
	  doSend("1");
  }
  function deactivateAlarm(){
	  doSend("2");
  }
