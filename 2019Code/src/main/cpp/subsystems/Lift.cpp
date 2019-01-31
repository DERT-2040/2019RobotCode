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
  fourBarCruiseVelocity = 10000;
  fourBarAcceleration = 5000;

  mLiftkP = 0;
  mLiftkI = 0;
  mLiftkD = 0;
  mLiftkF = 0;

  vLiftkP = 0;
  vLiftkI = 0;
  vLiftkD = 0;
  vLiftkF = 0;

  mFourBarkP = 0;
  mFourBarkI = 0;
  mFourBarkD = 0;
  mFourBarkP = 0;

  vFourBarkP = 0;
  vFourBarkI = 0;
  vFourBarkD = 0;
  vFourBarkF = 0;

  masterLiftMotor = new WPI_TalonSRX(kMasterLiftMotorPort);
  masterLiftMotor->SetInverted(false);

  //What type of encoder is it
  masterLiftMotor->ConfigSelectedFeedbackSensor(FeedbackDevice::CTRE_MagEncoder_Relative, kPIDLoopIdx, talonTimeoutMs);
  masterLiftMotor->SetSensorPhase(true);
  masterLiftMotor->SetSelectedSensorPosition(0, kPIDLoopIdx, talonTimeoutMs);

  masterLiftMotor->Config_kP(kElevatorMotionSlotIdx, mLiftkP, talonTimeoutMs);
  masterLiftMotor->Config_kI(kElevatorMotionSlotIdx, mLiftkI, talonTimeoutMs);
  masterLiftMotor->Config_kD(kElevatorMotionSlotIdx, mLiftkD, talonTimeoutMs);
  masterLiftMotor->Config_kF(kElevatorMotionSlotIdx, mLiftkF, talonTimeoutMs);

  masterLiftMotor->Config_kP(kElevatorVelocitySlotIdx, vLiftkP, talonTimeoutMs);
  masterLiftMotor->Config_kI(kElevatorVelocitySlotIdx, vLiftkI, talonTimeoutMs);
  masterLiftMotor->Config_kD(kElevatorVelocitySlotIdx, vLiftkD, talonTimeoutMs);
  masterLiftMotor->Config_kF(kElevatorVelocitySlotIdx, vLiftkF, talonTimeoutMs);

  masterLiftMotor->ConfigMotionCruiseVelocity(liftCruiseVelocity);
  masterLiftMotor->ConfigMotionCruiseVelocity(liftAcceleration);
  masterLiftMotor->ConfigAllowableClosedloopError(kElevatorMotionSlotIdx, liftPIDError, talonTimeoutMs);

  secondLiftMotor = new WPI_TalonSRX(kSecondLiftMotorPort);
  secondLiftMotor->SetInverted(false);
  secondLiftMotor->Follow(*masterLiftMotor);

  fourBarMotor = new WPI_TalonSRX(kFourBarMotorPort);
  fourBarMotor->SetInverted(false);
  fourBarMotor->ConfigSelectedFeedbackSensor(FeedbackDevice::Analog, kPIDLoopIdx, talonTimeoutMs);
  
  fourBarMotor->Config_kP(kFourBarMotionSlotIdx, mFourBarkP, talonTimeoutMs);
  fourBarMotor->Config_kI(kFourBarMotionSlotIdx, mFourBarkI, talonTimeoutMs);
  fourBarMotor->Config_kD(kFourBarMotionSlotIdx, mFourBarkD, talonTimeoutMs);
  fourBarMotor->Config_kF(kFourBarMotionSlotIdx, mFourBarkF, talonTimeoutMs);

  fourBarMotor->Config_kP(kFourBarVelocitySlotIdx, vFourBarkP, talonTimeoutMs);
  fourBarMotor->Config_kI(kFourBarVelocitySlotIdx, vFourBarkI, talonTimeoutMs);
  fourBarMotor->Config_kD(kFourBarVelocitySlotIdx, vFourBarkD, talonTimeoutMs);
  fourBarMotor->Config_kF(kFourBarVelocitySlotIdx, vFourBarkF, talonTimeoutMs);

  fourBarMotor->ConfigMotionCruiseVelocity(fourBarCruiseVelocity);
  fourBarMotor->ConfigMotionAcceleration(fourBarAcceleration);
  fourBarMotor->ConfigAllowableClosedloopError(kFourBarMotionSlotIdx, fourBarPIDError, talonTimeoutMs);
  
}

void Lift::InitDefaultCommand() 
{
  //SetDefaultCommand(new MySpecialCommand());
}

void Lift::setElevatorHeight(double height)
{
  masterLiftMotor->SelectProfileSlot(kElevatorMotionSlotIdx, kPIDLoopIdx);
  masterLiftMotor->Set(ControlMode::MotionMagic, height*heightToTickRatio);
}

void Lift::setFourBarHeight(double height)
{
  double angle = asin(height/fourBarLength) * 180 / M_PI;
}

void Lift::joystickElevatorControl(double speed)
{
  masterLiftMotor->SelectProfileSlot(kElevatorVelocitySlotIdx, kPIDLoopIdx);
  masterLiftMotor->Set(ControlMode::Velocity, speed*maxLiftSpeed);
}



