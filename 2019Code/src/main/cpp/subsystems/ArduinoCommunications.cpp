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
		uint8_t test = 't';
    wire->Read(4, 32, data);//use address 4 on i2c and store it in data
    wire->Write(4,test);
    char* output = new char[12];
    int size = 1;
    for (int i = 0; i < 12; i++){
      output[i] = data[i];
      /*if ((char)data[i] == '|'){
        size++;
      }*/
    }
    output[11] = 0;//Terminating String so it doesn't overflow
    frc::SmartDashboard::PutString("I2C",output);
    /*
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
    */
    //create a string from the byte array
}
// Put methods for controlling this subsystem
// here. Call these from Commands.
