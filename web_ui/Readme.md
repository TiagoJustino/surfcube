#Individual Assignment 2 helper files
This repository contains helper files to give you an example of
communicating between your Photon and your web browser via the USB
port.

##What does it do?
The key problem here is how to connect your computer's local resources
(i.e., the serial port) to the web browser. Because of security
concerns, the web browser isn't generally allowed to access hardware
directly. We can use node from the command line to get to the serial
port using the `serialport` module, but it would be nice to use the
graphical capabilities of the browser to do cool stuff like
visualizations.

There are two parts to the code in this repository. One is a web
server that runs with node. It talks to the serial port and gets data
from your Photon, Arduino, or whatever else is connected. It then
sends this data over a _websocket_[^1] to the other part, which is a web
page loaded in the browser via that web server. In this way, the
serial port is opened up to the browser, but in a controlled,
more-secure manner.

##How to install it?
Check out this repository, change into the directory, then run `npm
install` to get the necessary items.

- `blinky.ino`: A file to program onto your Photon. It sends a message
	over the serial port every second or two, and blinks the LED.
- `server.js`: Run this with `node server.js`. It will make a web
	server on port 3000; you can then open
	[http://localhost:3000](http://localhost:3000).
- `index.html`: The file served by the little web server.
- `package.json`: Contains the information necessary for `npm install`
	to work.

The source code is commented; read it to find out what it's doing.

##Bonus
As a bonus, I added `Spark.publish()` calls
([documentation](https://docs.particle.io/reference/firmware/photon/#spark-publish-))
to also send data to Particle's cloud. If you have successfully connected
to the Internet with your Photon, you can use (on Mac at least):

`curl https://api.particle.io/v1/devices/events?access_token=<your
token>`

to see a stream of events from your Photon in real time:

```
event: LEDEvent
data: {"data":"on","ttl":"60","published_at":"2015-09-09T21:05:12.415Z","coreid":"33001c001747343337363432"}

event: LEDEvent
data: {"data":"off","ttl":"60","published_at":"2015-09-09T21:05:14.415Z","coreid":"33001c001747343337363432"}

event: LEDEvent
data: {"data":"on","ttl":"60","published_at":"2015-09-09T21:05:15.416Z","coreid":"33001c001747343337363432"}
```

Please note Particle's limitations on events (from the
documentation page above):

_**NOTE**: Currently, a device can publish at rate of about 1 event/sec,
with bursts of up to 4 allowed in 1 second. Back to back burst of 4
messages will take 4 seconds to recover._

##Footnotes
[^1]: A websocket is much like a regular networking socket, but it
	happens in the web browser. There are handy libraries like `socket.io`
	that take care of this kind of stuff for you.
