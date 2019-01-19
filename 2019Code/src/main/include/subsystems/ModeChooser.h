/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc/commands/Subsystem.h>
#include "commands/TeleOp.h"
#include "commands/Auto.h"
class ModeChooser : public frc::Subsystem {
 private:
  int mode;
  int newMode;
	frc::Command* commandToRun = nullptr;
  // It's desirable that everything possible under private except
  // for methods that implement subsystem capabilities

 public:
  ModeChooser();
  void Periodic() override;
  void InitDefaultCommand() override;
};
