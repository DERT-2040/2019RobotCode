/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/ArduinoCommunications.h"
using byte = uint8_t;

ArduinoCommunications::ArduinoCommunications() : Subsystem("ArduinoCommunications") { 
  wire = new frc::I2C(frc::I2C::Port::kOnboard,4);
}

void ArduinoCommunications::InitDefaultCommand() {
  // Set the default command for a subsystem here.
  // SetDefaultCommand(new MySpecialCommand());
}
void ArduinoCommunications::Periodic(){
  getValues();
}
void ArduinoCommunications::getValues(){
  
    byte* data = new byte[12];//create a byte array to hold the incoming data
    wire->Read(4, 12, data);//use address 4 on i2c and store it in data
    inchesOffLine = bytesToFloat(data[0],data[1],data[2],data[3]);
    angle = bytesToFloat(data[4],data[5],data[6],data[7]);
    distance = bytesToFloat(data[8],data[9],data[10],data[11]);
    frc::SmartDashboard::PutNumber("InchesOffLine",inchesOffLine);
    frc::SmartDashboard::PutNumber("angle",angle);
    frc::SmartDashboard::PutNumber("distance",distance);
   
}
float ArduinoCommunications::getInchesOffLine(){
  return inchesOffLine;
}
float ArduinoCommunications::getAngle(){
  return angle;
}
float ArduinoCommunications::getUltrasonicDistance(){
  return distance;
}
float ArduinoCommunications::bytesToFloat(byte b0, byte b1, byte b2, byte b3) 
{ 
    byte byte_array[] = { b3, b2, b1, b0 };
    float result;
    std::copy(reinterpret_cast<const char*>(&byte_array[0]),
              reinterpret_cast<const char*>(&byte_array[4]),
              reinterpret_cast<char*>(&result));
    return result;
} 
// Put methods for controlling this subsystem
// here. Call these from Commands.
