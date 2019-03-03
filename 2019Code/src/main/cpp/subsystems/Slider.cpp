/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/Slider.h"
#include <iostream>

Slider::Slider() : Subsystem("Slider") 
{
  rawHallSensorInput = new frc::AnalogInput(kSliderEncoder);
  rawHallSensorInput->SetSampleRate(10000);
  rawHallSensorTrigger = new frc::AnalogTrigger(rawHallSensorInput);
  rawHallSensorTrigger->SetLimitsVoltage(3,3.5);
  distanceTraveled = new frc::Counter(*rawHallSensorTrigger);
  reCenterer = new frc::DigitalInput(kSliderLimitSwitch);
  /*distanceTraveled->SetUpSource(0);
  distanceTraveled->SetUpDownCounterMode();
  distanceTraveled->Reset();*/
  sliderMotor = new WPI_TalonSRX(kSliderMotorPort);
}

void Slider::InitDefaultCommand() {
  // Set the default command for a subsystem here.
  // SetDefaultCommand(new MySpecialCommand());
}
void Slider::Periodic(){

  std::cout << distanceTraveled->GetPeriod() << std::endl;
  if(sliderMotor->Get() > 0){
    position += distanceTraveled->Get() - previousPosition;
  }
  else if (sliderMotor->Get() < 0){
    position -= distanceTraveled->Get() - previousPosition;
  }
  previousPosition =  distanceTraveled->GetPeriod();//std::cout << distanceTraveled->Get() << std::endl;
  //std::cout << reCenterer->Get() << std::endl;
}
void Slider::setPosition(double _position)
{

}

double Slider::getPosition()
{

  //return slideMotor->GetSelectedSensorPosition();
}

bool Slider::atPosition()
{
  return true;
}

void Slider::ManualControl(float power){
  sliderMotor->Set(power);
}