/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/DriveTrain.h"
#include "../Robot.h"

DriveTrain::DriveTrain() : frc::Subsystem("DriveTrain")
{
  frontLeftDrive = new WPI_TalonSRX(kFrontLeftMotorPort);
  frontRightDrive = new WPI_TalonSRX(kFrontRightMotorPort);
  backLeftDrive = new WPI_TalonSRX(kBackLeftMotorPort);
  backRightDrive = new WPI_TalonSRX(kBackRightMotorPort);

  leftSide = new frc::SpeedControllerGroup(*frontLeftDrive, *backLeftDrive);
  rightSide = new frc::SpeedControllerGroup(*frontRightDrive, *backRightDrive);

  drive = new  frc::DifferentialDrive(*leftSide, *rightSide);

}

void DriveTrain::InitDefaultCommand() {
  // Set the default command for a subsystem here.
  // SetDefaultCommand(new MySpecialCommand());
}

void DriveTrain::Periodic()
{

}

void DriveTrain::CurveDrive()
{
  drive->CurvatureDrive(Robot::m_oi.gamepad->GetRawAxis(0), Robot::m_oi.gamepad->GetRawAxis(1), false);
}
// Put methods for controlling this subsystem
// here. Call these from Commands.
