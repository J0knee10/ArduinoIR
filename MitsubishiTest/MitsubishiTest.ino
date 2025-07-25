#include <IRremote.hpp>
#include <IRRemoteControl.h>
#define RAW_DATA_LEN 600

const int IRBlaster = 3;
IRRecv irRecv;
const int IR_RECV_PIN = 2;
const int FREQ_KHZ = 40;
int key = 0;
//IRsendRaw sendSignal;
int b1 = 4; // sending mode button pin 4
int b2 = 5; // receving mode button pin 5
int size = 583; // Get the array size
int isOn = -1;
int SETDELAY = 200;
int ButtonDelay = 1000;

//Data for on/off/temp control signals
uint16_t SIGNAL[RAW_DATA_LEN]  = {
	3456, 1728, 416, 1296, 416, 1296, 416, 464, 420, 464, 416, 464, 420, 1292, 420, 460, 420, 464, 416, 1292, 
	420, 1292, 420, 464, 416, 1292, 420, 464, 420, 464, 416, 1292, 420, 1292, 420, 460, 420, 1292, 420, 1292, 
	420, 464, 416, 464, 420, 1292, 420, 460, 420, 464, 416, 1296, 416, 464, 420, 464, 416, 464, 416, 464, 
	420, 464, 416, 464, 420, 460, 420, 464, 416, 468, 416, 460, 420, 464, 416, 464, 420, 464, 416, 464, 
	420, 464, 416, 464, 420, 460, 420, 460, 420, 464, 420, 460, 424, 1288, 424, 460, 420, 460, 424, 460, 
	424, 456, 428, 452, 428, 1284, 416, 1296, 384, 496, 404, 480, 404, 476, 432, 448, 408, 476, 408, 472, 
	408, 476, 408, 472, 408, 472, 408, 476, 408, 472, 408, 472, 432, 1256, 436, 1272, 436, 476, 408, 472, 
	408, 472, 408, 1276, 460, 1252, 460, 448, 408, 476, 408, 1276, 436, 1280, 428, 1276, 436, 1276, 460, 1252, 
	460, 448, 408, 476, 428, 452, 432, 448, 408, 476, 432, 448, 432, 452, 404, 476, 408, 472, 408, 476, 
	428, 452, 408, 472, 412, 472, 408, 472, 408, 476, 428, 452, 408, 476, 404, 476, 408, 472, 408, 476, 
	404, 476, 408, 472, 408, 476, 408, 472, 408, 472, 408, 476, 404, 476, 424, 460, 404, 476, 408, 472, 
	408, 476, 404, 476, 408, 472, 408, 476, 408, 472, 412, 472, 408, 472, 408, 472, 432, 452, 408, 472, 
	408, 472, 408, 476, 408, 472, 408, 476, 408, 472, 408, 472, 436, 448, 408, 472, 416, 468, 408, 472, 
	432, 452, 432, 448, 408, 472, 408, 476, 408, 472, 432, 452, 432, 448, 408, 1276, 436, 1276, 436, 1276, 
	444, 1264, 436, 476, 404, 476, 408, 472, 408, 1280, 456, 15520, 3488, 1692, 448, 1292, 420, 1292, 420, 460, 
	420, 464, 416, 464, 420, 1292, 420, 460, 420, 464, 416, 1292, 420, 1292, 420, 464, 420, 1292, 416, 464, 
	420, 464, 416, 1292, 420, 1292, 420, 464, 416, 1296, 416, 1292, 420, 464, 420, 460, 420, 1292, 420, 460, 
	424, 460, 420, 1288, 424, 460, 424, 460, 424, 456, 416, 464, 384, 496, 384, 500, 404, 476, 408, 476, 
	408, 472, 408, 476, 416, 464, 408, 472, 408, 476, 408, 472, 432, 452, 432, 448, 408, 476, 404, 476, 
	412, 468, 408, 476, 432, 1248, 436, 476, 408, 472, 408, 476, 404, 476, 408, 476, 404, 1276, 460, 1252, 
	436, 476, 428, 452, 408, 476, 404, 476, 408, 472, 408, 472, 432, 452, 408, 472, 408, 476, 404, 476, 
	408, 476, 404, 476, 408, 1276, 436, 1272, 440, 472, 408, 472, 408, 476, 408, 1276, 432, 1276, 436, 476, 
	408, 472, 432, 1252, 436, 1276, 436, 1276, 436, 1272, 436, 1276, 436, 476, 428, 452, 408, 476, 404, 476, 
	408, 476, 404, 476, 408, 476, 404, 476, 404, 476, 408, 476, 428, 452, 432, 452, 404, 476, 404, 476, 
	432, 452, 404, 476, 408, 476, 404, 476, 404, 480, 404, 476, 404, 476, 408, 476, 404, 476, 408, 472, 
	408, 476, 404, 476, 408, 472, 408, 476, 408, 472, 408, 476, 404, 476, 432, 452, 428, 452, 408, 472, 
	408, 476, 404, 476, 408, 476, 404, 476, 408, 476, 404, 476, 404, 476, 408, 472, 408, 476, 408, 472, 
	408, 476, 408, 472, 408, 472, 408, 476, 432, 452, 404, 476, 404, 476, 408, 476, 404, 476, 408, 472, 
	408, 476, 404, 476, 408, 476, 404, 1276, 436, 1276, 436, 1276, 436, 1276, 436, 472, 408, 476, 408, 472, 
	408, 1276, 436};



void setup() {
  // put your setup code here, to run once:
  pinMode(b1, INPUT);
  pinMode(b2, INPUT);
  pinMode(IRBlaster, OUTPUT);
  Serial.begin(9600);
  IrSender.begin(IRBlaster, true, 0); // Start the blaster
  Serial.println(F("Ready to send/rec IR signals"));
  while (! Serial);
  digitalWrite(9, HIGH);
  delay(1000);           
  digitalWrite(9, LOW);
  Serial.println(F("\nRemote ready to go"));
}

void loop() {
  // put your main code here, to run repeatedly:
  // Serial.println(F("\n Loop started"));
  digitalWrite(9, HIGH);

  // Change value of key based on buttons pressed
  if (digitalRead (b1) == LOW){
    Serial.println(F("Sending mode..."));
    key = 0;
    isOn *= -1;
    delay(ButtonDelay);
  }
  else if (digitalRead(b2) == LOW){
    //sendSignal.send (rawDataOFF, RAW_DATA_LEN, 38);
    Serial.println(F("Receiving mode..."));
    key = 1;
    delay(ButtonDelay);
  }

  //check if last pressed key is on or off
  switch (key) {
    // On/Off aircon
    case 0:
      if (isOn == 1){
        Serial.println(F("Sending signal"));
        IrSender.sendRaw(SIGNAL, sizeof(SIGNAL) / sizeof(SIGNAL[0]), 38);
      }
      break;

    // Change fan speed
    case 1:
      Serial.print(F("Ready to receive signals"));
      digitalWrite(9, LOW);
      delay(1000);
      digitalWrite(9, HIGH);
      int currentIrBufferLength = 0;
      irRecv.start(IR_RECV_PIN, SIGNAL, RAW_DATA_LEN, currentIrBufferLength); // start the receiver
      delay(5000);
      if (currentIrBufferLength > 0){
        irRecv.stop(IR_RECV_PIN);
        Serial.println(F("Signal received"));
        for (int i = 0; i < size - 1; i++) {
          SIGNAL[i] = SIGNAL[i + 1];
        }
        SIGNAL[size] = 0;
        for (int i = 0; i < currentIrBufferLength; i++) {
          if( (i % 20)==0) Serial.print(F("\n\t"));
          Serial.print(SIGNAL[i]);
          if (!(i > currentIrBufferLength)) {
            Serial.print(F(", "));
          }
        }
      }else{
        Serial.println(F("Signal failed to receive"));
      }
      key = 0;
      digitalWrite(9, LOW);
      break;
  }
  // receiving signal print it
  /*if (myReceiver.getResults()) { 
    Serial.println(recvGlobal.recvLength,DEC);
    Serial.print(F("uint16_t rawData[RAW_DATA_LEN]={\n\t"));
    for(bufIndex_t i=1;i<recvGlobal.recvLength;i++) {
      Serial.print(recvGlobal.recvBuffer[i],DEC);
      Serial.print(F(", "));
      if( (i % 8)==0) Serial.print(F("\n\t"));
    }
    Serial.println(F("1000};"));//Add arbitrary trailing space
    myReceiver.enableIRIn();      //Restart receiver
  } */
  digitalWrite(9, LOW);
  delay(SETDELAY);
}
