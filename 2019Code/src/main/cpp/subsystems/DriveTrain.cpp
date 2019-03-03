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
  
  secondLeftMotor->ConfigOpenloopRamp(0.3);
  secondRightMotor->ConfigOpenloopRamp(0.3);
  masterLeftMotor->ConfigOpenloopRamp(0.3);
  masterRightMotor->ConfigOpenloopRamp(0.3);
  
  secondLeftMotor->ConfigPeakCurrentLimit(35);
  secondRightMotor->ConfigPeakCurrentLimit(35);
  masterLeftMotor->ConfigPeakCurrentLimit(35);
  masterRightMotor->ConfigPeakCurrentLimit(35);

  secondLeftMotor->SetInverted(true);

  leftSide = new frc::SpeedControllerGroup(*secondLeftMotor, *masterLeftMotor);
  rightSide = new frc::SpeedControllerGroup(*secondRightMotor, *masterRightMotor);

  leftSide -> SetInverted(false);
  rightSide -> SetInverted(true);
  
  drive = new  frc::DifferentialDrive(*leftSide, *rightSide);

  compressor = new frc::Compressor(kCompressor);

	compressor->SetClosedLoopControl(true);
  driveSolenoid = new frc::DoubleSolenoid(1,kForwardDriveSolenoid,kReverseDriveSolenoid);

  masterLeftMotor->GetSensorCollection().SetQuadraturePosition(0);
  masterRightMotor->GetSensorCollection().SetQuadraturePosition(0);
  speedMultiplier = 1.0;
}

void DriveTrain::InitDefaultCommand() {
  // Set the default command for a subsystem here.
  // SetDefaultCommand(new MySpecialCommand());
  //SetDefaultCommand(new DriveWithJoySticks);
  //std::cout << "started" << std::endl;
}

void DriveTrain::Periodic()
{
  speedMultiplier = calcSpeedMultiplier(); 
}

void DriveTrain::CurveDrive()
{
  float vertSpeed = -1*Robot::m_oi.joystickR->GetRawAxis(1)*speedMultiplier;
  vertSpeed *= abs(vertSpeed);
  float turnSpeed = Robot::m_oi.joystickL->GetRawAxis(0)*speedMultiplier;
  turnSpeed *= abs(turnSpeed);
  drive->CurvatureDrive(vertSpeed,turnSpeed, true);
}
void DriveTrain::DriveSpeed(float speed){
  drive->CurvatureDrive(0.5,0,false);
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
float DriveTrain::calcSpeedMultiplier(){
  float liftHeight = Robot::m_lift.getTotalHeight();
  if (liftHeight > 50){
      secondLeftMotor->ConfigOpenloopRamp(0.7);
      secondRightMotor->ConfigOpenloopRamp(0.7);
      masterLeftMotor->ConfigOpenloopRamp(0.7);
      masterRightMotor->ConfigOpenloopRamp(0.7);
      return 0.5;
  }
  secondLeftMotor->ConfigOpenloopRamp(0.3);
  secondRightMotor->ConfigOpenloopRamp(0.3);
  masterLeftMotor->ConfigOpenloopRamp(0.3);
  masterRightMotor->ConfigOpenloopRamp(0.3);
  return 1;
}
