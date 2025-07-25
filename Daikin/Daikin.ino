#include <DYIRDaikin.h>
#include <IRLibRecvPCI.h>

DYIRDaikin irdaikin;
IRrecvPCI myReceiver(2);//pin number for the receiver
int key = 0;
//IRsendRaw sendSignal;
int b1 = 4; // on button pin 4
int b2 = 5; // off button pin 5
int b3 = 6; // up temp button pin 6
int b4 = 7; // dw temp button pin 7
int temp = 22;
int isOn = -1;
int fan = 3;
int SETDELAY = 200;
int ButtonDelay = 1000;

//Data for on/off/temp control signals

void setup() {
  // put your setup code here, to run once:
  pinMode(b1, INPUT);
  pinMode(b2, INPUT);
  pinMode(b3, INPUT);
  pinMode(b4, INPUT);
  Serial.begin(9600);
  myReceiver.enableIRIn(); // Start the receiver
  Serial.println(F("Ready to receive IR signals"));
  #ifdef DYIRDAIKIN_SOFT_IR
	irdaikin.begin(3);
	#else
	irdaikin.begin();
	#endif
	irdaikin.on();
	irdaikin.setSwing_on(); 
	irdaikin.setMode(1);
	irdaikin.setFan(fan); //FAN speed to 0-4
	irdaikin.setTemp(temp);
	//----everything is ok and to execute send command-----
	irdaikin.sendCommand();
  while (! Serial);
  digitalWrite(9, HIGH);
  delay(1000);           
  digitalWrite(9, LOW);
  Serial.println("\nRemote ready to go");
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println("\n Loop started");
  digitalWrite(9, HIGH);

  // Change value of key based on buttons pressed
  if (digitalRead (b1) == LOW){
    Serial.println("On/Off button pressed");
    isOn *= -1;
    key = 0;
    if (isOn == -1){
      Serial.println("Aircon switched off");
      irdaikin.off();
      irdaikin.sendCommand();
    }
    delay(ButtonDelay);
  }
  else if (digitalRead(b2) == LOW){
    //sendSignal.send (rawDataOFF, RAW_DATA_LEN, 38);
    Serial.println("fan button pressed");
    fan++;
    if (fan > 4){
      fan = 0;
    }
    key = 1;
    delay(ButtonDelay);
  }
  else if (digitalRead(b3) == LOW){
    Serial.println("Up button pressed");
    key = 2;
    delay(ButtonDelay);
  }
  else if (digitalRead(b4) == LOW){
    Serial.println("Down button pressed");
    key = 3;
    delay(ButtonDelay);
  }

  //check if last pressed key is on or off
  switch (key) {
    // On/Off aircon
    case 0:
    if (isOn == 1){
      irdaikin.on();
      Serial.println("Aircon switched on");
      Serial.print("Fan speed: ");
      Serial.println(fan);
      Serial.print("Temperature: ");
      Serial.println(temp);
      irdaikin.sendCommand();
      digitalWrite(3, HIGH);          
      digitalWrite(3, LOW);
    } else if (isOn == -1){
      Serial.println("Aircon switched off");
    }
    break;

    // Change fan speed
    case 1:
    Serial.print("Changing fan to fan speed: ");
    Serial.println(fan);
    irdaikin.setFan(fan);
    irdaikin.sendCommand();
    digitalWrite(3, HIGH);          
    digitalWrite(3, LOW);
    key = 0;
    break;

    // Temp up
    case 2:
    Serial.print("Moving temp down by 1 degree, temp:");
    temp--;
    if (temp < 18){
      temp = 18;
    }
    irdaikin.setTemp(temp); //sendSignal.send (rawDataUP, RAW_DATA_LEN, 38);
    irdaikin.sendCommand();
    Serial.println(temp);
    digitalWrite(3, HIGH);         
    digitalWrite(3, LOW);
    key = 0;
    break; 

    // Temp down
    case 3:
    Serial.print("Moving temp up by 1 degree, temp: ");
    temp++;
    if (temp > 28){
      temp = 28;
    }
    irdaikin.setTemp(temp); //sendSignal.send (rawDataDW, RAW_DATA_LEN, 38);
    irdaikin.sendCommand();
    Serial.println(temp);
    digitalWrite(3, HIGH);    
    digitalWrite(3, LOW);
    key = 0;
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
