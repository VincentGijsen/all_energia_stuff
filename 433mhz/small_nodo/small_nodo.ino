

#include <VirtualWire.h>

#define RXPIN P1_4
#define BUFFERSIZE 3
#define BLINKDELAY 20

#define DIMOUT P1_2

const char myAddress = 0x01;

byte buffer[BUFFERSIZE];
byte bufferSize = BUFFERSIZE;

#define PWM0 P1_5
#define PWM1 P1_6
#define PWM2 P1_7



volatile byte pwmCounter = 0;
byte pwm[3] = {0x00,0x00,0x00};


//this HACK is called via the VirtualWire TimerOverflow Signal
  void interruptHack(){
  pwmCounter < 0xFF? pwmCounter++: pwmCounter=0;
  digitalWrite(PWM0, pwm[0] < pwmCounter? HIGH: LOW);
  digitalWrite(PWM1, pwm[1] < pwmCounter? HIGH: LOW);
  digitalWrite(PWM2, pwm[2] < pwmCounter? HIGH: LOW);
}

void setup()
{
  pinMode(RXPIN, INPUT);
  pinMode(RED_LED, OUTPUT);
  digitalWrite(RED_LED, LOW);
  
  
  pinMode(DIMOUT, OUTPUT);
  pinMode(DIMOUT,LOW);
  
  blink(2);
  /*
  *  Setup Virtual Wire
  */
  vw_setup(200);
  vw_set_rx_pin(RXPIN);
  vw_rx_start();
  
  //pass callback into TimerOverflow 
  vw_setCallBack(interruptHack);
  blink(5);
}

void loop()
{
  while(!vw_get_message(buffer, &bufferSize))
  {
    //wait forever until msg received;
  }
  //The message is ours
  if (buffer[0] == myAddress){
   // blink(1);
   
    if(buffer[1] == 1){
     // blink(4);//
     digitalWrite(RED_LED, HIGH);
    }
    else{
      //blink(8);
      //
      digitalWrite(RED_LED, LOW);  
    //blink(2);
    }
  }
  //The message is for somebody else
  else{
   blink(2); 
  // delay(2000);
  }
  
}

void blink(int times){
   for (int x=0;x<times;x++){
     digitalWrite(RED_LED, HIGH);
     delay(BLINKDELAY);
     digitalWrite(RED_LED, LOW);
     delay(BLINKDELAY);
     
   } 
}

