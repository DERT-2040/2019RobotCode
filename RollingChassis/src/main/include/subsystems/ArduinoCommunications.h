/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc/commands/Subsystem.h>
#include <frc/I2C.h>
#include "frc/WPILib.h"
class ArduinoCommunications : public frc::Subsystem {
 private:
  // It's desirable that everything possible under private except
  // for methods that implement subsystem capabilities
  float* inputArray;
  frc::I2C* wire;
 public:
  ArduinoCommunications();
  void InitDefaultCommand() override;
  void Periodic() override;
  float* getValues();
};
