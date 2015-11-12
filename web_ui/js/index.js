$(document).ready(function() {
  var socket = io();
  socket.on('to browser', function(data) {
    if(data.trim() === 'pong') {
      $('#pong').html("<b>Pong</b>");
      setTimeout(function() {
        $('#pong').text("Pong");
      }, 2000);
    }
  });

  var ping = function() {
    socket.emit('to serial', "ping");
    socket.emit('to serial', 0);
  }

  var sendWave = function() {
    socket.emit('to serial', "servo");
    socket.emit('to serial', $( "#height" ).val() );
  }

  var sendFrequency = function() {
    socket.emit('to serial', "frequency");
    socket.emit('to serial', $( "#frequency" ).val() );
  }

  var sendDelay = function() {
    socket.emit('to serial', "delay");
    socket.emit('to serial', $( "#delay" ).val() );
  }

  var sendBreathing = function() {
    socket.emit('to serial', "breathingstate");
    socket.emit('to serial', $( "#breathing" ).val() );
  }

  var sendStepperPos = function() {
    socket.emit('to serial', "setstepperposition");
    socket.emit('to serial', $( "#stepperPos" ).val() );
  }

  var sendTide = function() {
    socket.emit('to serial', "tide");
    socket.emit('to serial', $( "#tide" ).val() );
  }

  var sendTemperature = function() {
    socket.emit('to serial', "temperature");
    socket.emit('to serial', $( "#temperature" ).val() );
  }

  $( "#in" ).click(function() {
    socket.emit('to serial', "forward");
    socket.emit('to serial', $( "#amount" ).val() );
  });

  $( "#out" ).click(function() {
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
  $( "#temperatureBtn" ).click(sendTemperature);

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

  $('#temperature').keyup(function(e){
    if(e.keyCode == 13)
    {
      sendTemperature();
    }
  });

  $( "#demo1" ).click(function() {
    socket.emit('to serial', "tide");
    socket.emit('to serial', 0 );
    socket.emit('to serial', "servo");
    socket.emit('to serial', 50 );
    socket.emit('to serial', "delay");
    socket.emit('to serial', 7 );
    socket.emit('to serial', "frequency");
    socket.emit('to serial', 7000 );
    socket.emit('to serial', "temperature");
    socket.emit('to serial', 14 );
  });

  $( "#demo2" ).click(function() {
    socket.emit('to serial', "tide");
    socket.emit('to serial', 15 );
    socket.emit('to serial', "servo");
    socket.emit('to serial', 50 );
    socket.emit('to serial', "delay");
    socket.emit('to serial', 7 );
    socket.emit('to serial', "frequency");
    socket.emit('to serial', 7000 );
    socket.emit('to serial', "temperature");
    socket.emit('to serial', 26 );
  });

  $( "#demo3" ).click(function() {
    socket.emit('to serial', "tide");
    socket.emit('to serial', 15 );
    socket.emit('to serial', "servo");
    socket.emit('to serial', 50 );
    socket.emit('to serial', "delay");
    socket.emit('to serial', 4 );
    socket.emit('to serial', "frequency");
    socket.emit('to serial', 5000 );
    socket.emit('to serial', "temperature");
    socket.emit('to serial', 17 );
  });

  $( "#demo4" ).click(function() {
    socket.emit('to serial', "tide");
    socket.emit('to serial', 15 );
    socket.emit('to serial', "servo");
    socket.emit('to serial', 0 );
    socket.emit('to serial', "delay");
    socket.emit('to serial', 2 );
    socket.emit('to serial', "frequency");
    socket.emit('to serial', 2000 );
    socket.emit('to serial', "temperature");
    socket.emit('to serial', 35 );
  });

});
