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
class Intake : public frc::Subsystem {
 private:
  // It's desirable that everything possible under private except
  // for methods that implement subsystem capabilities
  WPI_TalonSRX *leftIntake;
  WPI_TalonSRX *rightIntake;
  frc::DoubleSolenoid *intakeSolenoid;
  bool state;
  int deploy;
  bool deploying = false;
 public:
  Intake();
  void Periodic() override;
  void InitDefaultCommand() override;
  void DeployCargo();
  void DeployHatch();
  void SetWheelSpeed(float speed);
  void SetState(bool _state);// false is open and true is closed
  bool IsClosed();
  //void S
};