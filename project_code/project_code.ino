#include <SoftwareSerial.h>// import the serial library
SoftwareSerial atharva(10, 11); // RX, TX
int ledpin=13; // led on D13 will show blink on / off
int BluetoothData; // the data given from Computer
int recordTime=3000;

#define REC 2               // pin 2 is used for recording
#define PLAY_E 3            // pin 3 is used for playback-edge trigger
#define FT 5                // pin 5 is used for feed through and will NOT record



void setup() {
  // put your setup code here, to run once:
  pinMode(REC,OUTPUT);// set the REC pin as output
  pinMode(PLAY_E,OUTPUT);// set the PLAY_e pin as output
  pinMode(FT,OUTPUT);// set the FT pin as output  
  Serial.begin(9600);// set up Serial monitor 
  atharva.begin(9600);
  atharva.println("Device Connected, send r for record,p for play");
  atharva.println("s for setting record time");
  pinMode(ledpin,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (atharva.available())
  {
    BluetoothData=atharva.read();
    if(BluetoothData=='s')
    {
      
      atharva.println("Enter time for recording");
      digitalWrite(ledpin,1);
      delay(5000);
      digitalWrite(ledpin,0);
      BluetoothData=atharva.read();
      int time=BluetoothData-48;
      recordTime=time*1000;  
      atharva.println("Time was set to ");
      atharva.println(recordTime);
    }
    if(BluetoothData=='p' || BluetoothData=='P')
    {
      digitalWrite(PLAY_E, HIGH);
      
      atharva.println("Playback Started");  
      delay(recordTime);
      digitalWrite(PLAY_E, LOW);  
      atharva.println("Playback Ended");
    }
    if(BluetoothData =='r' || BluetoothData =='R')
    {
      digitalWrite(REC, HIGH);
      atharva.println("Recording started");
      delay(recordTime);
      digitalWrite(REC, LOW);
      atharva.println("Recording Stopped ");              
     } 
  }
}
