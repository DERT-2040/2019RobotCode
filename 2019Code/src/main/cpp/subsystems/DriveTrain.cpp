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
  frontLeftDrive = new WPI_TalonSRX(kFrontLeftMotorPort);
  frontRightDrive = new WPI_TalonSRX(kFrontRightMotorPort);
  backLeftDrive = new WPI_TalonSRX(kBackLeftMotorPort);
  backRightDrive = new WPI_TalonSRX(kBackRightMotorPort);

  backRightDrive->SetInverted(true);

  leftSide = new frc::SpeedControllerGroup(*frontLeftDrive, *backLeftDrive);
  rightSide = new frc::SpeedControllerGroup(*frontRightDrive, *backRightDrive);

  drive = new  frc::DifferentialDrive(*leftSide, *rightSide);

  lightSensor = new frc::AnalogInput(kLightSensorPort);

}

void DriveTrain::InitDefaultCommand() {
  // Set the default command for a subsystem here.
  // SetDefaultCommand(new MySpecialCommand());
  SetDefaultCommand(new DriveWithJoySticks);
  std::cout << "started" << std::endl;
}

void DriveTrain::Periodic()
{
  std::cout << lightSensor->GetVoltage() << std::endl;
}

void DriveTrain::CurveDrive()
{
  drive->CurvatureDrive(Robot::m_oi.gamepad->GetRawAxis(5), -1*Robot::m_oi.gamepad->GetRawAxis(0), true);
}
// Put methods for controlling this subsystem
// here. Call these from Commands.
