/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/DriveTrain.h"
#include "Robot.h"
#include "commands/DriveWithJoySticks.h"
#include <iostream>

DriveTrain::DriveTrain() : frc::Subsystem("DriveTrain")
{
  secondLeftMotor = new WPI_TalonSRX(kSecondLeftMotorPort);
  secondRightMotor = new WPI_TalonSRX(kSecondRightMotorPort);
  masterLeftMotor = new WPI_TalonSRX(kMasterLeftMotorPort);
  masterRightMotor = new WPI_TalonSRX(kMasterRightMotorPort);

  secondLeftMotor->ConfigPeakCurrentLimit(35);
  secondRightMotor->ConfigPeakCurrentLimit(35);
  masterLeftMotor->ConfigPeakCurrentLimit(35);
  masterRightMotor->ConfigPeakCurrentLimit(35);
  
  secondLeftMotor->ConfigOpenloopRamp(0.15);
  secondRightMotor->ConfigOpenloopRamp(0.15);
  masterLeftMotor->ConfigOpenloopRamp(0.15);
  masterRightMotor->ConfigOpenloopRamp(0.15);

  secondLeftMotor->SetInverted(true);

  leftSide = new frc::SpeedControllerGroup(*secondLeftMotor, *masterLeftMotor);
  rightSide = new frc::SpeedControllerGroup(*secondRightMotor, *masterRightMotor);

  leftSide -> SetInverted(false);
  rightSide -> SetInverted(true);
  
  drive = new frc::DifferentialDrive(*leftSide, *rightSide);

  compressor = new frc::Compressor(kCompressor);

	compressor->SetClosedLoopControl(true);
  driveSolenoid = new frc::DoubleSolenoid(1,kForwardDriveSolenoid,kReverseDriveSolenoid);
  
  masterLeftMotor->GetSensorCollection().SetQuadraturePosition(0);
  masterRightMotor->GetSensorCollection().SetQuadraturePosition(0);

}

void DriveTrain::InitDefaultCommand() 
{

}

void DriveTrain::Periodic()
{

}

void DriveTrain::CurveDrive()
{

  float forwardSpeed = -1*Robot::m_oi.joystickR->GetRawAxis(1);
  float turnSpeed = Robot::m_oi.joystickL->GetRawAxis(0);
  forwardSpeed*= abs(-1*Robot::m_oi.joystickR->GetRawAxis(1));
  turnSpeed *= abs(Robot::m_oi.joystickL->GetRawAxis(0));
  drive->CurvatureDrive(forwardSpeed,turnSpeed,true);
}

void DriveTrain::DriveSpeed(float speed){
  //drive->CurvatureDrive(0.5,0,false);
}

void DriveTrain::ShiftGear(int _gear){
  if (gear != _gear){
    gear = _gear;
    if(gear == 1){
      driveSolenoid->Set(frc::DoubleSolenoid::Value::kReverse);
    }
    else if (gear == 0){
      driveSolenoid->Set(frc::DoubleSolenoid::Value::kForward);
    }
  }
}

void DriveTrain::velDrive()
{
  float rightSpeed;
  float leftSpeed;

  float turnValue = Robot::m_oi.joystickL->GetRawAxis(0);
  float forwardValue = Robot::m_oi.joystickR->GetRawAxis(1);

  if(turnValue < 0.025)
  {
    turnValue = 0;
  }

  if(forwardValue < 0.025)
  {
    turnValue = 0;
  }

  rightSpeed = forwardValue * maxSpeed - turnValue * maxSpeed;
  leftSpeed = forwardValue * maxSpeed + turnValue * maxSpeed;

  masterLeftMotor->Set(ControlMode::Velocity, leftSpeed);
  masterRightMotor->Set(ControlMode::Velocity, rightSpeed);
}
