//Assertion failed: (uv__has_active_reqs(handle->loop)), function uv__udp_run_completed, file ../deps/uv/src/unix/udp.c, line 154.
//Abort trap: 6


// OSC communication and UPD port
//---------------------
"use strict";

var Bean = require('ble-bean');

var osc = require('osc-min');

var dgram = require('dgram');
var udp = dgram.createSocket("udp4");

var outport = 41234;
console.log("sending messages to http://localhost:" + outport);

//  OSC Stuff

var sendData = function(piezoVal ) {
  var buf;
  buf = osc.toBuffer({
    elements: [
      {
        address: "/p1",
        args: piezoVal
      }
    ]
  });
  return udp.send(buf, 0, buf.length, outport, "localhost");
};

// Bean communication
//-----------------------
var intervalId;
var connectedBean;

Bean.discover(function(bean){
  connectedBean = bean;
  process.on('SIGINT', exitHandler.bind(this));

  bean.on("serial", function(data, valid){
    console.log(data.toString());
  });

  bean.on("disconnect", function(){
    process.exit();
  });

  bean.connectAndSetup(function(){

    bean.notifyOne(
      //called when theres data
      function(data){
        if(data && data.length>=2){
          var value = data[1]<<8 || (data[0]);
          sendData([value]);
          console.log("one:", value);
        }
      },
      //called when the notify is successfully or unsuccessfully setup
      function(error){
        if(error) console.log("one setup: ", error);
      });

    bean.notifyTwo(
      //called when theres data
      function(data){
        if(data && data.length>=2){
          var value = data[1]<<8 || (data[0]);
          sendData([value], "/p2");
          console.log("two:", value);
        }
      },
      //called when the notify is successfully or unsuccessfully setup
      function(error){
        if(error) console.log("two setup: ", error);
      });

    bean.notifyThree(
      //called when theres data
      function(data){
        if(data && data.length>=2){
          var value = data[1]<<8 || (data[0]);
          sendData([value], "/p3");
          console.log("three:", value);
        }
      },
      //called when the notify is successfully or unsuccessfully setup
      function(error){
        if(error) console.log("two setup: ", error);
      });

  });

});


process.stdin.resume();//so the program will not close instantly
var triedToExit = false;

//turns off led before disconnecting
var exitHandler = function exitHandler() {

  var self = this;
  if (connectedBean && !triedToExit) {
    triedToExit = true;
    console.log('Turning off led...');
    clearInterval(intervalId);
    connectedBean.setColor(new Buffer([0x0,0x0,0x0]), function(){});
    //no way to know if succesful but often behind other commands going out, so just wait 2 seconds
    console.log('Disconnecting from Device...');
    setTimeout(connectedBean.disconnect.bind(connectedBean, function(){}), 2000);
  } else {
    process.exit();
  }
};


