#include <SPI.h>
#include "Adafruit_BLE_UART.h"

#define ADAFRUITBLE_REQ 10
#define ADAFRUITBLE_RDY 2     
#define ADAFRUITBLE_RST 9

Adafruit_BLE_UART BTLEserial = Adafruit_BLE_UART(ADAFRUITBLE_REQ, ADAFRUITBLE_RDY, ADAFRUITBLE_RST);
/**************************************************************************/
/*!
    Configure the Arduino and start advertising with the radio
*/
/**************************************************************************/

int static isBlinkyTime;

int static isFadeTime;

String onTime;

String offTime;

String word1;

int fadeTime;

void setup()
{ 
  pinMode(6,OUTPUT);
  Serial.begin(9600);
  while(!Serial); // Leonardo/Micro should wait for serial init
  Serial.println(F("Adafruit Bluefruit Low Energy nRF8001 Print echo demo"));

  // BTLEserial.setDeviceName("NEWNAME"); /* 7 characters max! */
  BTLEserial.begin();
}

/**************************************************************************/
/*!
    Constantly checks for new events on the nRF8001
*/
/**************************************************************************/
aci_evt_opcode_t laststatus = ACI_EVT_DISCONNECTED;

void loop()
{
  // Tell the nRF8001 to do whatever it should be working on.
  BTLEserial.pollACI();

  // Ask what is our current status
  aci_evt_opcode_t status = BTLEserial.getState();
  // If the status changed....
  if (status != laststatus) {
    // print it out!
    if (status == ACI_EVT_DEVICE_STARTED) {
        Serial.println(F("* Advertising started"));
    }
    if (status == ACI_EVT_CONNECTED) {
        Serial.println(F("* Connected!"));
    }
    if (status == ACI_EVT_DISCONNECTED) {
        Serial.println(F("* Disconnected or advertising timed out"));
    }
    // OK set the last status change to this one
    laststatus = status;
  }

  if (status == ACI_EVT_CONNECTED) {
    // Lets see if there's any data for us!
    if (BTLEserial.available()) {
      Serial.print("* "); Serial.print(BTLEserial.available()); Serial.println(F(" bytes available from BTLE"));
    }


    
    // OK while we still have something to read, get a character and print it out
    while (BTLEserial.available()) 
      {
      char c = BTLEserial.read();
      word1 = word1 + c;
      Serial.print(c); 
      }
    
    
   
    
    

    // Next up, see if we have any data to get from the Serial console

    if (Serial.available()) {
      // Read a line from Serial
      Serial.setTimeout(100); // 100 millisecond timeout
      String s = Serial.readString();

      // We need to convert the line to bytes, no more than 20 at this time
      uint8_t sendbuffer[20];
      s.getBytes(sendbuffer, 20);
      char sendbuffersize = min(20, s.length());

      Serial.print(F("\n* Sending -> \"")); Serial.print((char *)sendbuffer); Serial.println("\"");

      // write the data
      BTLEserial.write(sendbuffer, sendbuffersize);
    }
  }

    //-----------------------------------------------------------------------------------------------
    //---------------------------------------  Digital signal  --------------------------------------
    //-----------------------------------------------------------------------------------------------
    if(word1.startsWith("L")){
      isFadeTime = 0;
      isBlinkyTime = 0;
      analogWrite(6,LOW);
      word1 = "";
      }
    if(word1.startsWith("H")){
      isBlinkyTime = 0;
      analogWrite(6,HIGH);
      word1 = "";
      }  
    //-----------------------------------------------------------------------------------------------
    //---------------------------------------  Anaglog signal  --------------------------------------
    //-----------------------------------------------------------------------------------------------
    if(word1.startsWith("A")){
      isFadeTime = 0;
      isBlinkyTime = 0;
      word1 = word1.substring(1);
      int semnalPwm = word1.toInt();
      word1 = "";
      if(semnalPwm != 0) {
         analogWrite(6,semnalPwm);
         }
       
      }
    //-----------------------------------------------------------------------------------------------
    //---------------------------------------  Blink example   --------------------------------------
    //-----------------------------------------------------------------------------------------------
    if(word1.startsWith("B")){
      isBlinkyTime = 1;
      isFadeTime = 0;
      onTime = word1.substring(1,2);
      offTime = word1.substring(2); 
      word1 = "";
      }
     
    if (isBlinkyTime != 0){
      Serial.println("val de blinky: "+String(isBlinkyTime));
      analogWrite(6,HIGH);
      int delayOn = onTime.toInt();
      delayOn = delayOn*1000;
      delay(delayOn);
      analogWrite(6,LOW);
      delay(offTime.toInt()*1000);
      Serial.println("iz tru");
      word1 = "";
      }
    //-----------------------------------------------------------------------------------------------
    //---------------------------------------  Fade example   ---------------------------------------
    //-----------------------------------------------------------------------------------------------
    if(word1.startsWith("F")){
        isFadeTime = 1;
        isBlinkyTime = 0;
        word1 = word1.substring(1);
        fadeTime = word1.toInt();
        }
     if(isFadeTime !=0){
        int x = 1;
        for (int i = 0; i > -1; i = i + x){
          analogWrite(6, i);
          if (i == 255) x = -1;             // switch direction at peak
          delay(fadeTime*1000/255);
          } 
        word1 = "";
        }
         
}
