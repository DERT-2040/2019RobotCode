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

  WPI_TalonSRX *frontLeftDrive;
  WPI_TalonSRX *frontRightDrive;
  WPI_TalonSRX *backLeftDrive;
  WPI_TalonSRX *backRightDrive;

  frc::SpeedControllerGroup *leftSide;
  frc::SpeedControllerGroup *rightSide;

  frc::DifferentialDrive *drive;

 public:

  DriveTrain();
  void Periodic() override;
  void InitDefaultCommand() override;
};
