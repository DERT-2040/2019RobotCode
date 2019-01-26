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
class HatchPickup : public frc::Subsystem {
 private:
  WPI_TalonSRX *hatchIntake;
	frc::DigitalInput *uprightSwitch;
	frc::DigitalInput *retractedSwitch;
	frc::DigitalInput *deployedSwitch;
  int desiredState = 0;
  int state = 0;
  int previousState = 0;
  float motorOutput = 0;

  void SetSpeed();
  // It's desirable that everything possible under private except
  // for methods that implement subsystem capabilities

 public:
  HatchPickup();
  void Periodic() override;
  void InitDefaultCommand() override;
  void SetState(int _state);// 0 is fully retracted, 1 is upright, 2 is completely down
  int GetState();
};
