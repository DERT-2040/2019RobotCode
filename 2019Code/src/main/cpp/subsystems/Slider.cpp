/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/Slider.h"

Slider::Slider() : Subsystem("Slider") 
{
  slideMotor = new WPI_TalonSRX(kSliderMotorPort);
  slideMotor->GetSensorCollection().SetQuadraturePosition(0);
  slideMotor->SetSensorPhase(true);
  slideMotor->SetInverted(false);

  kP, kI, kD, kF = 0;
  slideMotor->Config_kP(slotIdx, kP, timeoutMs);
  slideMotor->Config_kI(slotIdx, kI, timeoutMs);
  slideMotor->Config_kD(slotIdx, kD, timeoutMs);
  slideMotor->Config_kF(slotIdx, kF, timeoutMs);
  
  slideMotor->ConfigSelectedFeedbackSensor(FeedbackDevice::CTRE_MagEncoder_Relative, kPIDLoopIdx, timeoutMs);

  slideMotor->ConfigMotionCruiseVelocity(cruiseVelocity, timeoutMs);
  slideMotor->ConfigMotionAcceleration(motionAccel, timeoutMs);

  slideMotor->SetSelectedSensorPosition(0, kPIDLoopIdx, timeoutMs);
}

void Slider::InitDefaultCommand() {
  // Set the default command for a subsystem here.
  // SetDefaultCommand(new MySpecialCommand());
}

void Slider::setPosition(double _position)
{
  position = _position;
  tickPosition = position*inchToTickRatio;
  slideMotor->Set(ControlMode::MotionMagic, tickPosition);
}

double Slider::getPosition()
{
  return slideMotor->GetSelectedSensorPosition();
}

bool Slider::atPosition()
{
  return true;
}
