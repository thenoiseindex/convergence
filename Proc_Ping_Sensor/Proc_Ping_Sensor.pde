import processing.serial.*;

// MIDI setup
import rwmidi.*;
MidiOutput output;

float pingValue = 0;        // ping sensor value
float lastPing = 0;
Serial myPort;

void setup() {
  size(200, 200);

  // List all the available serial ports
  println(Serial.list());

  // I know that the first port in the serial list on my mac
  // is always my  Arduino, so I open Serial.list()[0].
  // Open whatever port is the one you're using.
  myPort = new Serial(this, Serial.list()[0], 9600);

  // don't generate a serialEvent() unless you get a newline character:
  myPort.bufferUntil('\n');


  /* start MIDI */
  // Show available MIDI output devices in console 

  println("Set up MIDI");
  MidiInputDevice devices[] = RWMidi.getInputDevices(); 
  for (int i = 0; i < devices.length; i++) { 
    println(i + ": " + devices[i].getName());
  } 

  output = RWMidi.getOutputDevices()[1].createOutput();
}

void draw() {
  // set the background color with the ping value:
  //background(pingValue);
  if (pingValue != lastPing) {
    output.sendController(1, 1, int(pingValue));
    lastPing = pingValue;
  }
}

void sendMidi() {
  output.sendController(1, 1, int(pingValue));
}

void serialEvent(Serial myPort) { 
  //println("go!");
  // get the ASCII string:
  String inString = myPort.readStringUntil('\n');

  if (inString != null) {
    // trim off any whitespace:
    inString = trim(inString);
    // split the string on the commas and convert the 
    // resulting substrings into an integer array:
    float[] sensor = float(split(inString, ","));
    // if the array has at least three elements, you know
    // you got the whole thing.  Put the numbers in the
    // color variables:
    if (sensor.length >=1) {
      //pingValue = constrain(map(sensor[0], 18, 110, 127, 0), 0, 100);
      pingValue = constrain(sensor[0], 12, 130);
      pingValue = map(pingValue, 12, 130, 110, 0);
      //output.sendController(1, 1, int(pingValue));
      //println(pingValue);
    }
  }
}

