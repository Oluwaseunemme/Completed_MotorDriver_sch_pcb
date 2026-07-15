#include "Motor_class_opp.h"

motorDriver myDriver = motorDriver(LATCHPIN, CLOCKPIN, DATAPIN, L1E1, L1E2, L2E1, L2E2);

void setup(){
  myDriver.init();
  Serial.begin(9600);
}

bool isChange=true;
long interval=1000, lastime;
void loop(){
    //int m1Speed = map(analogRead(A0), 0, 1023, 0, 255);
    if(millis()-lastime>=interval){
      lastime=millis();
      //Serial.println("m1 speed:"+String(analogRead(A0)));
      myDriver.setSpeed(250, 100, 50, 250);
      myDriver.setDirection("backward", "forward", "backward", "forward");
     }
}