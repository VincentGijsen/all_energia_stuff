/*
 * This sketch receives and decodes data from a 433MHz thermo weather sensor.
 *
 * Setup:
 * - Connect digital output of a 433MHz receiver to digital pin 2 of Arduino
 * - Enable the serial monitor at 115200 baud. 
 *
 */

#include <SpaceLen.h>

volatile uint8_t data[4]= {0,0,0,0};
volatile boolean flag = false;

void setup() {
  Serial.begin(9600);
  pinMode(RED_LED, OUTPUT);
  digitalWrite(RED_LED, LOW);
  
  // Init the receiver on interrupt pin 0 (digital pin 2).
  // Set the callback to function "showTempHumi", which is called
  // whenever valid sensor data has been received.
  pinMode(P1_4, INPUT);
  SpaceLen::init(P1_4, showRaw);
  Serial.println("Started");
}

void loop() {
  // Empty! However, you can do other stuff here if you like.
  delay(3000);
  Serial.println("--mark--" );
  //Serial.println(micros);
  Serial.flush();
  
  if(flag)
  {
    blink(4);

    if ( (data[3]) == 0xF0 ) {							
      int channel=((data[1]&0x30)>>4)+1;
      byte high=((data[1]&0x08)?0xf0:0)+(data[1]&0x0f);
      byte low=data[2];
      int temp10= high*256+low;
      Serial.print("Channel: ");
      Serial.print(channel);
    
      Serial.flush();
      Serial.print(" Temp: ");
      Serial.print(temp10/10);
      Serial.print(".");
      Serial.print(abs((temp10)%10));
      Serial.flush();
      
      Serial.print(" BYTE0: ");
      Serial.println(data[0],BIN);
      Serial.flush();
      
    } else {
      if (true) {
        Serial.print(" B0: ");
        Serial.print(data[0],BIN);
        Serial.print("--");
        Serial.print(data[1],BIN);
        Serial.print("--");
        Serial.print(data[2],BIN);
        Serial.print("--"); 
        Serial.print(data[3],BIN);
        Serial.println('**');
        
      }
     
    }
    Serial.flush();
    SpaceLen::enable();
    flag = false;
  } 

}


void showRaw(byte *datain) {
  SpaceLen::disable();
  for (int x=0; x<4;x++){
    data[x] = datain[x];
  }
  flag = true;

}

void blink(int times)
{
 for(int x =0;x< times;x++) {
    digitalWrite(RED_LED, HIGH);
    delay(100);
    digitalWrite(RED_LED, LOW); 
    delay(100);
    }
}

