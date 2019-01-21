/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/ArduinoCommunications.h"
using byte = unsigned char;

ArduinoCommunications::ArduinoCommunications() : Subsystem("ArduinoCommunications") { 
  wire = new frc::I2C(frc::I2C::Port::kOnboard,4);
}

void ArduinoCommunications::InitDefaultCommand() {
  // Set the default command for a subsystem here.
  // SetDefaultCommand(new MySpecialCommand());
}
void ArduinoCommunications::Periodic(){
  inputArray = getValues();
}
float* ArduinoCommunications::getValues(){
  
    byte* data = new byte[32];//create a byte array to hold the incoming data
		wire->Read(4, 32, data);//use address 4 on i2c and store it in data
		char* output = new char[sizeof(data)];
    int size = 1;
    for (int i = 0; i < sizeof(data); i++){
      output[i] = (char)data[i];
      if ((char)data[i] == '|'){
        size++;
      }
    }
    std::string s = output;
    std::string delimiter = "|";
    char * pch;
    pch  = strtok(output,"|");
    float* floatData = new float[size];
    int iterator = 0;
    while (pch != NULL){
      floatData[iterator] = (float)atof(pch);
      iterator++;
      pch = strtok(NULL,"|");
    }
    return floatData;
    //create a string from the byte array
    //im not sure what these last two lines do
}
// Put methods for controlling this subsystem
// here. Call these from Commands.
