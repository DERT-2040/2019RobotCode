#include <QTRSensors.h>
#include <Wire.h>

QTRSensorsRC qtrrc((unsigned char[]) {2,3,4}, 3);
unsigned values[3];

float output = 45;
void setup() {
  Serial.begin(9600);
  Wire.begin(4);
  Wire.onReceive(receiveEvent);
  Wire.onRequest(requestEvent);
  // put your setup code here, to run once:
  
}

void loop() {
  // put your main code here, to run repeatedly:
  
  qtrrc.read(values, QTR_EMITTERS_ON);
  Serial.println(values[0]);
  Serial.println(values[1]);
  Serial.println(values[2]);
  Serial.println();
}

void requestEvent(){
    Wire.write("Hello");
}
void receiveEvent(int bytes){

}
