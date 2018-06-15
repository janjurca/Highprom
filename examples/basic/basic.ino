#include "highprom.h"


Highprom prom(100); //Reserve first 100 bytes to be used by this library

void setup(){
    Serial.begin(9600);

    while (!Serial.available()) {
       if (Serial.read() == 'e') {
           prom.init(); // This erases eeprom and prepare it to be used ba lib, It is not need to run it every time, just when you start to use this
       }
       if (millis() > 10000) {
           //user doesnt erased it in first 10 seconds so go on to program
           break;
       }
    }
    prom.insertValue("key","value");
    prom.insertValue("key","value1");//There is Update semantics, so the first value will be replaced by this

    char buff[20];
    prom.getValue("key",dst,20);
    Serial.print("This was readed from EEPROM: ");
    Serial.println(dst);

    prom.removeValue("key"); //As the value was inserted it can be removed

}

void loop(){

}
