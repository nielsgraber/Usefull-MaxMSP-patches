const int MAX_CHANNELS = 10;
// Amount of channels to receive data on, make sure this is the same or more than the
// amount of channels in your MaxMSP sketch

int channelData[MAX_CHANNELS];

String inputBuffer = "";
bool readingPacket = false;

// Include the servo library:
#include "Servo.h"

// Create a new servo object:
Servo myservo1, myservo2;

// Define the servo pin:
#define servoPin1 10
#define servoPin2 9
int servoValue1 = 1;
int servoValue2 = 1;

void setup() {
  Serial.begin(9600);
  myservo1.attach(servoPin1);
  myservo2.attach(servoPin2);
}

void loop() {
  // Handle serial input
  while (Serial.available() > 0) {
    char incomingChar = Serial.read();

    // Start reading the code when the ascii character 91 is detected to mark the beginning of a packet
    if (incomingChar == '[') {
      readingPacket = true;
      inputBuffer = "";
      // Then also start to check if the ascii character is 93 to mark the end of a packet
    } else if (incomingChar == ']') {
      readingPacket = false;
      parsePacket(inputBuffer);
    } else if (readingPacket) {
      // When the ascii character isnt 91 or 93 it is the incoming data, so write it to a buffer
      inputBuffer += incomingChar;
    }
  }

  servoValue1 = channelData[1];
  servoValue2 = channelData[2];
}


// Function for assinging the right value to the right string
void parsePacket(String packet) {
  packet.trim();
  int spaceIndex = packet.indexOf(' ');

  if (spaceIndex != -1) {
    int channel = packet.substring(0, spaceIndex).toInt();
    int value = packet.substring(spaceIndex + 1).toInt();

    if (channel >= 0 && channel < MAX_CHANNELS) {
      channelData[channel] = value;

      // Use these to debug, otherwise u can disable them using two dashes
      Serial.print("Channel ");
      Serial.print(channel);
      Serial.print(" set to ");
      Serial.println(value);

      // Used to assign the written data in the buffer to the right motor, using the channel number
      if (channel == 1) {
        int angle = constrain(servoValue1, 0, 180);  // servo expects 0–180
        myservo1.write(angle);
      }

      if (channel == 2) {
        int angle = constrain(servoValue2, 0, 180);  // servo expects 0–180
        myservo2.write(angle);
      }
    }
  }
}
