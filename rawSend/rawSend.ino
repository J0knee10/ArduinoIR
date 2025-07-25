/* rawSend.ino Example sketch for IRLib2
 *  Illustrates how to send a code Using raw timings which were captured
 *  from the "rawRecv.ino" sample sketch.  Load that sketch and
 *  capture the values. They will print in the serial monitor. Then you
 *  cut and paste that output into the appropriate section below.
 */
#include <IRLibSendBase.h>    //We need the base code
#include <IRLib_HashRaw.h>    //Only use raw sender

IRsendRaw mySender;

void setup() {
  Serial.begin(9600);
  delay(2000); while (!Serial); //delay for Leonardo
  Serial.println(F("Every time you press a key is a serial monitor we will send."));
}
/* Cut and paste the output from "rawRecv.ino" below here. It will 
 * consist of a #define RAW_DATA_LEN statement and an array definition
 * beginning with "uint16_t rawData[RAW_DATA_LEN]= {…" and concludes
 * with "…,1000};"
 */
#define RAW_DATA_LEN 100
uint16_t rawData[RAW_DATA_LEN] = {
3534, 1622, 534, 1190, 470, 1258, 442, 422, 
442, 426, 458, 402, 426, 1302, 398, 470, 
394, 494, 398, 1330, 394, 1326, 394, 478, 
390, 1334, 366, 506, 366, 498, 390, 1334, 
366, 1358, 390, 506, 362, 1334, 390, 1334, 
386, 478, 366, 502, 390, 1362, 338, 526, 
342, 526, 366, 1358, 342, 522, 362, 506, 
338, 526, 366, 506, 338, 530, 338, 526, 
338, 526, 342, 522, 366, 510, 366, 502, 
366, 502, 366, 502, 366, 502, 342, 526, 
362, 506, 338, 522, 342, 526, 338, 530, 
338, 526, 362, 506, 338, 1382, 338, 526, 
362, 506, 338, 1000};




/*
 * Cut-and-paste into the area above.
 */
   
void loop() {
  if (Serial.read() != -1) {
    //send a code every time a character is received from the 
    // serial port. You could modify this sketch to send when you
    // push a button connected to an digital input pin.
    mySender.send(rawData,RAW_DATA_LEN,36);//Pass the buffer,length, optionally frequency
    Serial.println(F("Sent signal."));
  }
}

