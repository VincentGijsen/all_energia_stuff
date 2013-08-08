//
//  utils.c
//
//
//  Created by Vincent Gijsen on 7/5/13.
//
//
//

#include "Utils.h"




void Utils::initRed(){
    pinMode(RED_LED, OUTPUT);
    digitalWrite(RED_LED, LOW);
}

Utils::Utils(){
    _average = 0;
}

void Utils::blinkRed(uint8_t times){
  int x;
  for (x=0; x< times; x++){
    Utils::blink();
  }
}
void Utils::blinkRed()
{
   Utils::blink();
}

void Utils::blink(){
   digitalWrite(RED_LED, HIGH);
   delay(BLINK_DELAY);
   digitalWrite(RED_LED, LOW);
}


uint32_t Utils::readTemperature(){
    // Formula: http://www.43oh.com/forum/viewtopic.php?p=18248#p18248
    int i;
    for (i=0;i<SAMPLES;i++)
    {
        _average -= _values[i];
        _values[i] = ((uint32_t)analogRead(TEMPSENSOR)*27069 - 18169625) *10 >> 16;
        _average += _values[i];
    }
    return (_average/SAMPLES);
}

uint16_t Utils::readBattery(){
    uint16_t adc = analogRead(A1);
    uint32_t volt = (adc >> 10) * 1500;
    return volt;
}

#if VERBOSE > 0
void Utils::printDec(uint32_t ui) {
    Serial.print(ui/10, DEC);
    Serial.print(".");
    Serial.print(ui%10, DEC);
}


void dump_radio_status_to_serialport(uint8_t status)
{
    Serial.print("Enrf24 radio transceiver status: ");
    switch (status) {
        case ENRF24_STATE_NOTPRESENT:
            Serial.println("NO TRANSCEIVER PRESENT");
            break;

        case ENRF24_STATE_DEEPSLEEP:
            Serial.println("DEEP SLEEP <1uA power consumption");
            break;

        case ENRF24_STATE_IDLE:
            Serial.println("IDLE module powered up w/ oscillators running");
            break;

        case ENRF24_STATE_PTX:
            Serial.println("Actively Transmitting");
            break;

        case ENRF24_STATE_PRX:
            Serial.println("Receive Mode");
            break;

        default:
            Serial.println("UNKNOWN STATUS CODE");
    }

}
#endif
