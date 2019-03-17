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
  rawHallSensorTrigger->SetLimitsVoltage(3.0,3.75);
  distanceTraveled = new frc::Counter(*rawHallSensorTrigger);
  reCenterer = new frc::DigitalInput(kSliderLimitSwitch);
  /*distanceTraveled->SetUpSource(0);
  distanceTraveled->SetUpDownCounterMode();*/
  distanceTraveled->Reset();
  sliderMotor = new WPI_TalonSRX(kSliderMotorPort);
}

void Slider::InitDefaultCommand() {
  // Set the default command for a subsystem here.
  // SetDefaultCommand(new MySpecialCommand());
}
void Slider::Periodic(){
  //std::cout <<"Recenterer: " << reCenterer->Get() << std::endl;
  
  minPos = false;
  maxPos = false;
  if(sliderMotor->Get() > 0){
    position += distanceTraveled->Get() - previousPosition;
  }
  else if (sliderMotor->Get() < 0){
    position -= distanceTraveled->Get() - previousPosition;
  }
  if(position >= 80){
    position = 80;
    maxPos = true;
  }
  else if (position <= -80){
    position = -80;
    minPos = true;
  }
  if(!reCenterer->Get()){
    position = 0;
  }
  previousPosition =  distanceTraveled->Get();
  //frc::SmartDashboard::PutString("Position",std::to_string(distanceTraveled->Get()));
  //std::cout << reCenterer->Get() << std::endl;*/
  //std::cout << "Position: " << position << std::endl;
  if(autoSet){
    autoMove();
  }
}
void Slider::setPosition(int _position)
{
  autoSet = true;
  desiredPosition = _position;
}
void Slider::autoMove()
{
  if(desiredPosition - position!=0){
    if(desiredPosition > position ){
      sliderMotor->Set(1);
    }
    else{
      sliderMotor->Set(-1);
    }
  }
  else{
    sliderMotor->Set(0);
    autoSet = false;
  }

  
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
  //std::cout << "MaxPos: " << maxPos << std::endl;
  //std::cout << "MinPos: " << minPos << std::endl;
  if(fabs(power)< 0.2){
    power = 0;
  }
  else{
    autoSet = false;
  }
  if(maxPos == true && power > 0){
    sliderMotor->Set(0);
  }
  else if(minPos == true && power < 0){
    sliderMotor->Set(0);
  }
  else if (!autoSet){ 
    sliderMotor->Set(power);
  }
   
}