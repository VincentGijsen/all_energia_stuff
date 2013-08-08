#include <RemoteReceiver.h>
#include <RemoteTransmitter.h>

#define BLINKDELAY 5


ElroTransmitter elroTransmitter(P1_5);
//ElroTransmitter elroTransmitter(P1_5);

void setup()
{
  Serial.begin(9600);
  Serial.println("hoi");
  // put your setup code here, to run once:M
   pinMode(P1_4, INPUT);
   
   pinMode(P1_5, OUTPUT);
   digitalWrite(P1_5, HIGH);
   delay(500);
   digitalWrite(P1_5, LOW);
   
   
   RemoteReceiver::init(P1_4, 3, translateCode);
   pinMode(RED_LED, OUTPUT);
   digitalWrite(RED_LED, LOW);
 
   blink();  
 }

int count =0;
volatile bool FLAG = false;
void loop()
{
  if (count == 0){
    for (byte b=0;b<=31;b++){   
      long elroFF = elroTransmitter.getTelegram(b,'D', false) & 0xFFFFF;
      Serial.println(elroFF);
      Serial.flush();
     }
  count++;
  }
  
  if (count == 1){
    RemoteReceiver::disable();
    for (byte x = B0; x<= B11111; x++)
    {
       elroTransmitter.sendSignal(x, 'A', true);
       elroTransmitter.sendSignal(x, 'B', true);
       blink(6);
    }
    Serial.println("send on");
    blink(10);
    count++; 
   RemoteReceiver::enable();
  }
  
  
if(FLAG){
  blink();
  FLAG=false;
 }
delay(100);
      

 
}

  
void translateCode(unsigned long receivedCode, unsigned int period){
   interrupts();
   FLAG=true;
   RemoteReceiver::disable();
  
  Serial.print("Code: ");
  Serial.print(receivedCode, HEX);
  Serial.flush();
  Serial.print(", period duration: ");
  Serial.print(period);
  Serial.println("us.");
 // brute(receivedCode);
 // RemoteTransmitter::sendCode(P1_4, receivedCode, period, 3);
 RemoteReceiver::enable();
}

//BruteForce the possible command:
void brute(long input){
  for (char address=B00000; address<=B11111;address++){
    for (int dev=1; dev<=4;dev++){
      for (int b=0; b<=1;b++){
        long elro = elroTransmitter.getTelegram(dev,address, b);
   
        if(RemoteTransmitter::isSameCode(elro, input))
        {
          Serial.println("found elro");
        }
   
      }
    }
  }
  
    
  Serial.println("no match found");
}

void blink(int times){
  for (int i=0; i< times; i++)
  blink();
}
void blink(){
 digitalWrite(RED_LED, HIGH);
  delay(BLINKDELAY);
 digitalWrite(RED_LED,LOW); 
 delay(BLINKDELAY);
}
