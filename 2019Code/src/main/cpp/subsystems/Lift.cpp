/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/Lift.h"

Lift::Lift() : Subsystem("Lift") 
{

  talonTimeoutMs = 30;
  liftCruiseVelocity = 10000;
  liftAcceleration = 5000;
  liftkP = 0;
  liftkI = 0;
  liftkD = 0;
  liftkF = 0;

  masterLiftMotor = new WPI_TalonSRX(kMasterLiftMotorPort);
  masterLiftMotor->SetInverted(false);

  //What type of encoder is it
  masterLiftMotor->ConfigSelectedFeedbackSensor(FeedbackDevice::CTRE_MagEncoder_Relative, kPIDLoopIdx, talonTimeoutMs);
  masterLiftMotor->SetSensorPhase(true);
  masterLiftMotor->SetSelectedSensorPosition(0, kPIDLoopIdx, talonTimeoutMs);

  masterLiftMotor->Config_kP(kSlotIdx, liftkP, talonTimeoutMs);
  masterLiftMotor->Config_kI(kSlotIdx, liftkI, talonTimeoutMs);
  masterLiftMotor->Config_kD(kSlotIdx, liftkD, talonTimeoutMs);
  masterLiftMotor->Config_kF(kSlotIdx, liftkF, talonTimeoutMs);
  masterLiftMotor->ConfigMotionCruiseVelocity(liftCruiseVelocity);
  masterLiftMotor->ConfigMotionCruiseVelocity(liftAcceleration);

  secondLiftMotor = new WPI_TalonSRX(kSecondLiftMotorPort);
  secondLiftMotor->SetInverted(false);
  secondLiftMotor->Follow(*masterLiftMotor);

  fourBarMotor = new WPI_TalonSRX(kFourBarMotorPort);
  fourBarMotor->ConfigSelectedFeedbackSensor(FeedbackDevice::Analog, kPIDLoopIdx, talonTimeoutMs);

}

void Lift::InitDefaultCommand() 
{
  // SetDefaultCommand(new MySpecialCommand());
}

void Lift::setElevatorHeight(double height)
{
  masterLiftMotor->Set(ControlMode::MotionMagic, height*heightToTickRatio);
}


