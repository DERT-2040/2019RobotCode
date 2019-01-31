/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc/commands/Subsystem.h>
#include "ctre/Phoenix.h"
#include "frc/WPILib.h"
#include "RobotMap.h"
class DriveTrain : public frc::Subsystem {
 
 private:

  WPI_TalonSRX *masterLeftMotor;
  WPI_TalonSRX *masterRightMotor;
  WPI_TalonSRX *secondLeftMotor;
  WPI_TalonSRX *secondRightMotor;
  
  frc::SpeedControllerGroup *leftSide;
  frc::SpeedControllerGroup *rightSide;
  frc::DifferentialDrive *drive;

  frc::Compressor *compressor;
  frc::DoubleSolenoid *driveSolenoid;
  int gear;

  double kP = 0;
  double kI = 0;
  double kD = 0;
  double kF = 0;
  double cruiseVelocity = 10000;
  double acceleration = 5000;
  const int kSlotIdx = 0;
  const int kPIDSlotIdx = 0;

 public:

  DriveTrain();
  void Periodic() override;
  void InitDefaultCommand() override;
  void CurveDrive();
  void DriveSpeed(float speed);
  void ShiftGear(int gear);// 0 = first gear, 1 = second gear
  void driveFeet(float feet);
};
