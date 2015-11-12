$(document).ready(function() {
  var socket = io();
  socket.on('to browser', function(data) {
    $('#messages').append($('<li>').text(data));
  });

  var ping = function() {
    console.log("sending servo command");
    socket.emit('to serial', "ping");
    socket.emit('to serial', 0);
  }

  var sendWave = function() {
    console.log("sending servo command");
    socket.emit('to serial', "servo");
    socket.emit('to serial', $( "#height" ).val() );
  }

  var sendFrequency = function() {
    console.log("sending servo command");
    socket.emit('to serial', "frequency");
    socket.emit('to serial', $( "#frequency" ).val() );
  }

  var sendDelay = function() {
    console.log("sending servo command");
    socket.emit('to serial', "delay");
    socket.emit('to serial', $( "#delay" ).val() );
  }

  var sendBreathing = function() {
    console.log("sending servo command");
    socket.emit('to serial', "breathingstate");
    socket.emit('to serial', $( "#breathing" ).val() );
  }

  var sendStepperPos = function() {
    console.log("sending servo command");
    socket.emit('to serial', "setstepperposition");
    socket.emit('to serial', $( "#stepperPos" ).val() );
  }

  var sendTide = function() {
    console.log("sending servo command");
    socket.emit('to serial', "tide");
    socket.emit('to serial', $( "#tide" ).val() );
  }

  $( "#in" ).click(function() {
    console.log("sending forward command");
    socket.emit('to serial', "forward");
    socket.emit('to serial', $( "#amount" ).val() );
  });

  $( "#out" ).click(function() {
    console.log("sending backward command");
    socket.emit('to serial', "backward");
    socket.emit('to serial', $( "#amount" ).val() );
  });

  $( "#ping" ).click(ping);
  $( "#wave" ).click(sendWave);
  $( "#frequencyBtn" ).click(sendFrequency);
  $( "#delayBtn" ).click(sendDelay);
  $( "#breathingBtn" ).click(sendBreathing);
  $( "#stepperPosBtn" ).click(sendStepperPos);
  $( "#tideBtn" ).click(sendTide);

  $('#height').keyup(function(e){
    if(e.keyCode == 13)
    {
      sendWave();
    }
  });

  $('#frequency').keyup(function(e){
    if(e.keyCode == 13)
    {
      sendFrequency();
    }
  });

  $('#delay').keyup(function(e){
    if(e.keyCode == 13)
    {
      sendDelay();
    }
  });

  $('#breathing').keyup(function(e){
    if(e.keyCode == 13)
    {
      sendBreathing();
    }
  });

  $('#stepperPos').keyup(function(e){
    if(e.keyCode == 13)
    {
      sendStepperPos();
    }
  });

  $('#tide').keyup(function(e){
    if(e.keyCode == 13)
    {
      sendTide();
    }
  });

});
