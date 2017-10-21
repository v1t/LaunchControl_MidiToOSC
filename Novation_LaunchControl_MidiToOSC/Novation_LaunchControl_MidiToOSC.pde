import netP5.*;
import oscP5.*;

import themidibus.*;
MidiBus myBus;

OscP5 oscP5;
NetAddress myRemoteLocation;



void setup() {
  this.surface.setVisible(false); //makes invisible
  background(0);
  MidiBus.list(); 
  myBus = new MidiBus(this, 1, 2);

  oscP5 = new OscP5(this, 12001); //12000 incoming port
  myRemoteLocation = new NetAddress("127.0.0.1", 12000); //sending to port
}

void draw() {
}

void noteOn(int channel, int pitch, int velocity) {
  println();
  println("Note On:");
  println("--------");
  println("Channel:"+channel);
  println("Pitch:"+pitch);
  println("Velocity:"+velocity);

  OscMessage myMessage = new OscMessage("/LaunchControl/Button");

  myMessage.add(channel); /* add an int to the osc message */
  myMessage.add(pitch); /* add a float to the osc message */
  myMessage.add(velocity); /* add a string to the osc message */
  oscP5.send(myMessage, myRemoteLocation); 

  int col;
  if (channel == 14) {
    col = 60;
  } else {
    col = 62;
  }
  myBus.sendNoteOn(channel, pitch, col);
}

void noteOff(int channel, int pitch, int velocity) {
  
  OscMessage myMessage = new OscMessage("/LaunchControl/Button");
  
  myMessage.add(channel); /* add an int to the osc message */
  myMessage.add(pitch); /* add a float to the osc message */
  myMessage.add(velocity); /* add a string to the osc message */
  oscP5.send(myMessage, myRemoteLocation); 
  
  myBus.sendNoteOff(channel, pitch, 0);
}

void controllerChange(int channel, int number, int value) {
  // Receive a controllerChange
  println();
  println("Controller Change:");
  println("--------");
  println("Channel:"+channel);
  println("Number:"+number);
  println("Value:"+value);
  
  OscMessage myMessage = new OscMessage("/LaunchControl/Knob");
  
  myMessage.add(channel); /* add an int to the osc message */
  myMessage.add(number); /* add a float to the osc message */
  myMessage.add(value); /* add a string to the osc message */
  oscP5.send(myMessage, myRemoteLocation); 
  
  int col = 127;
  if (number > 113 && number < 118) {
    if (value == 0) col = 12;
    myBus.sendNoteOn(channel, number, col); 
    myBus.sendControllerChange(channel, number, col);
  }
}