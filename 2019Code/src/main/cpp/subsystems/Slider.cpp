/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/Slider.h"

Slider::Slider() : Subsystem("Slider") 
{

}

void Slider::InitDefaultCommand() {
  // Set the default command for a subsystem here.
  // SetDefaultCommand(new MySpecialCommand());
}

void Slider::setPosition(double _position)
{


}

double Slider::getPosition()
{
  return slideMotor->GetSelectedSensorPosition();
}

bool Slider::atPosition()
{
  return true;
}
