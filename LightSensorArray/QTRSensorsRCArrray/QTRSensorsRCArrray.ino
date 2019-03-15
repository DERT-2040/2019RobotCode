#include <QTRSensors.h>
#include <Wire.h>

QTRSensorsRC qtrrc((unsigned char[]) {2,3,4,5,6,7,8,9,10,11,12 }, 11, 2500);
unsigned values[11];
int lineThreshold = 500;
float inches = -6;
int inchesRollAvgSize = 10;
float inchesRollAvg[10];
int inchesRollAvgIndex = 0;
int nullSize = inchesRollAvgSize;
float inchesToReturn = -6;
char inchesToReturnFinal[80];
void calibrate()
{
  Serial.println("calibration started");
   for (int i = 0; i < 250 ; i++)  // make the calibration take about 5 seconds
  {
    qtrrc.calibrate();
    delay(20);
  }
  for(int i = 0; i < 11; i++)
  {
    Serial.println(qtrrc.calibratedMaximumOn[i]);
    Serial.println(qtrrc.calibratedMinimumOn[i]);
    Serial.println(" ");
  }
  Serial.println("calibration ended"); 
}

void setup() {
  for(int i = 0; i < inchesRollAvgSize; i++){
    inchesRollAvg[0] = 0;
  }
  Serial.begin(9600);
  Wire.begin(4);
  Wire.onReceive(receiveEvent);
  Wire.onRequest(requestEvent);
  // put your setup code here, to run once: 
  calibrate(); 
  //qtrrc.calibrate();
  /*
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
  
  qtrrc.calibratedMaximumOn[8] = 1268;
  qtrrc.calibratedMinimumOn[8] = 540;
  
  qtrrc.calibratedMaximumOn[9] = 1268;
  qtrrc.calibratedMinimumOn[9] = 540;
  
  qtrrc.calibratedMaximumOn[10] = 1268;
  qtrrc.calibratedMinimumOn[10] = 540;
  */
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
  Serial.print(" ");
  Serial.print(values[8]);
  Serial.print(" ");
  Serial.print(values[9]);
  Serial.print(" ");
  Serial.print(values[10]);
  Serial.println(" ");
  delay(10);  
}

void printSensorValuesFormatted()
{
  char str[7];

  sprintf(str,"%04d",values[0]);
  Serial.print(str);
  Serial.print(" ");
  sprintf(str,"%04d",values[1]);
  Serial.print(str);
  Serial.print(" ");
  sprintf(str,"%04d",values[2]);
  Serial.print(str);
  Serial.print(" ");
  sprintf(str,"%04d",values[3]);
  Serial.print(str);
  Serial.print(" ");
  sprintf(str,"%04d",values[4]);
  Serial.print(str);
  Serial.print(" ");
  sprintf(str,"%04d",values[5]);
  Serial.print(str);
  Serial.print(" ");
  sprintf(str,"%04d",values[6]);
  Serial.print(str);
  Serial.print(" ");
  sprintf(str,"%04d",values[7]);
  Serial.print(str);
  Serial.print(" ");
  sprintf(str,"%04d",values[8]);
  Serial.print(str);
  Serial.print(" ");
  sprintf(str,"%04d",values[9]);
  Serial.print(str);
  Serial.print(" ");
  sprintf(str,"%04d",values[10]);
  Serial.print(str);
  Serial.print("\n");
  delay(100);  
}

float inchesOff(){
  float inches = 0; 
  int count = 0;
  bool state = false;
  for(int i =0; i < 11; i++){
        if(values[i] < lineThreshold){
          state = true;
          inches += i-5;
          count++;
        }
        else if (state == true){
          break;
        }
   }
   if(count!=0){
    inches = inches/count;
    return inches;
   }
   else{
    return -6;
   }
}
void loop() {
  // put your main code here, to run repeatedly:
  qtrrc.readCalibrated(values, QTR_EMITTERS_ON);
  //printSensorValuesFormatted();
  inches = inchesOff();
  inchesRollAvg[inchesRollAvgIndex] = inches;
  int tempIndex = inchesRollAvgIndex;
  bool detectLine = false;
  for(int i = 0; i< nullSize; i++){
    if(tempIndex == -1){
      tempIndex = inchesRollAvgSize-1;
    }
    if(inchesRollAvg[tempIndex]!=-6){
      detectLine = true;
    }
    tempIndex--;
  }
  int sizeOfAvg = inchesRollAvgSize;
  if(detectLine){
    for(int i = 0; i < inchesRollAvgSize; i++){
      if(inchesRollAvg[i] != -6){
        inchesToReturn += inchesRollAvg[i];
      }
      else{
        sizeOfAvg--;
      }
    }
    if(sizeOfAvg != 0){
      inchesToReturn /= (1+sizeOfAvg);
    }
    else{
      inchesToReturn = 88;
    }
  }
  else{
    inchesToReturn = -6;
  }
  inchesRollAvgIndex++;
  if(inchesRollAvgIndex > inchesRollAvgSize){
    inchesRollAvgIndex = 0;
  }
  dtostrf(inchesToReturn,6,2,inchesToReturnFinal);
  //sprintf(inchesToReturnFinal,"y = %f",inchesToReturn);
  //Serial.println(inchesToReturnFinal);
}

void requestEvent(){
  
  //Serial.println("Hello");
  Wire.write(inchesToReturnFinal);
}
void receiveEvent(int bytes){

}
