//Run this file with "node server.js"
var app        = require('express')();
var http       = require('http').Server(app);
var io         = require('socket.io')(http);
var serialport = require('serialport');
var exec = require('child_process').exec;
var SerialPort = serialport.SerialPort;
var serial;

//When a request come into the server for / give the client the file index.html
app.get('/', function(req, res){res.sendFile('./index.html', { root: __dirname});});
app.get('/js/jquery.js', function(req, res){res.sendFile('./js/jquery.js', { root: __dirname});});
app.get('/js/index.js', function(req, res){res.sendFile('./js/index.js', { root: __dirname});});

//Listen for incoming connections
http.listen(3000, function(){console.log("listening on port 3000");});

//When the serial port is successfully opened...
var onSerialOpen = function()
{
	console.log("opened serial port");
	//When we get data from the serial port...
	serial.on('data', function(data)
	{
		console.log("got some data from Arduino: ", data);

		//Send to the browser; 'data' is the name of the event
		io.emit('to browser', data);
	});

};

//Here's what happens when a connection is made from the browser
io.sockets.on('connection',
	function(socket)
	{
		console.log("someone connected");

		//Since the socket is open, we can now accept "to serial" messages
		// from the browser
		socket.on('to serial', function(data)
		{
			if(serial && serial.isOpen())
			{
				serial.write(data + '\n');
				console.log("Send '" + data + "' to serial");
			}
			else
				console.log("Serial port not open");
		});
	}
);

serialport.list(function (err, ports) {
  if(ports){
    ports.forEach( function(port) {
      if(JSON.stringify(port).match(/.*duino.*/gi)) {
        console.log(port.comName);
        serial = new SerialPort( port.comName, {parser: serialport.parsers.readline('\n')});
        serial.on('open', onSerialOpen);
      }
    });
  }
});
