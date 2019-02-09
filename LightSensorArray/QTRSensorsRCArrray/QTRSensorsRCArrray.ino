#include <QTRSensors.h>
#include <Wire.h>

QTRSensorsRC qtrrc((unsigned char[]) {4,3,2,5,6,7,8,9}, 8, 2500);
unsigned values[8];

float output = 45;

void calibrate()
{
  Serial.println("calibration started");
   for (int i = 0; i < 250 ; i++)  // make the calibration take about 5 seconds
  {
    qtrrc.calibrate();
    delay(20);
  }
  for(int i = 0; i < 8; i++)
  {
    Serial.println(qtrrc.calibratedMaximumOn[i]);
    Serial.println(qtrrc.calibratedMinimumOn[i]);
    Serial.println(" ");
  }
  Serial.println("calibration ended"); 
}

void setup() {
  
  Serial.begin(9600);
  Wire.begin(4);
  Wire.onReceive(receiveEvent);
  Wire.onRequest(requestEvent);
  // put your setup code here, to run once: 
  //calibrate(); 
  qtrrc.calibrate();
  qtrrc.calibratedMaximumOn[0] = 2500;
  qtrrc.calibratedMinimumOn[0] = 612;
  
  qtrrc.calibratedMaximumOn[1] = 1340;
  qtrrc.calibratedMinimumOn[1] = 748;
  
  qtrrc.calibratedMaximumOn[2] = 1688;
  qtrrc.calibratedMinimumOn[2] = 476;
  
  qtrrc.calibratedMaximumOn[3] = 1064;
  qtrrc.calibratedMinimumOn[3] = 340;
  
  qtrrc.calibratedMaximumOn[4] = 792;
  qtrrc.calibratedMinimumOn[4] = 276;
  
  qtrrc.calibratedMaximumOn[5] = 928;
  qtrrc.calibratedMinimumOn[5] = 340;
  
  qtrrc.calibratedMaximumOn[6] = 928;
  qtrrc.calibratedMinimumOn[6] = 404;
  
  qtrrc.calibratedMaximumOn[7] = 1268;
  qtrrc.calibratedMinimumOn[7] = 540;

  for(int i = 0; i < 8; i++)
  {
    Serial.println(qtrrc.calibratedMaximumOn[i]);
    Serial.println(qtrrc.calibratedMinimumOn[i]);
    Serial.println(" ");
  }
}

void printSensorValues()
{
  Serial.print(values[0]);
  Serial.print(" ");
  Serial.print(values[1]);
  Serial.print(" ");
  Serial.print(values[2]);
  Serial.print(" ");
  Serial.print(values[3]);
  Serial.print(" ");
  Serial.print(values[4]);
  Serial.print(" ");
  Serial.print(values[5]);
  Serial.print(" ");
  Serial.print(values[6]);
  Serial.print(" ");
  Serial.print(values[7]);
  Serial.println();
  delay(10);  
}

void loop() {
  // put your main code here, to run repeatedly:
  qtrrc.readCalibrated(values, QTR_EMITTERS_ON);
  printSensorValues();
}

void requestEvent(){
    Wire.write("Hello");
}
void receiveEvent(int bytes){

}
