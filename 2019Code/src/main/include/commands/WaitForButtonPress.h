/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc/commands/Command.h>
#include "frc/WPILib.h"
#include "Robot.h"

class WaitForButtonPress : public frc::Command {
 private:
  bool finished = false;
  int buttonNum;
  bool button;
 public:
  WaitForButtonPress(int buttonNum, bool _button);// if true then waiting for a button,
                                                  //if false waiting for axis specified in buttonNum (Used for triggers)
  void Initialize() override;
  void Execute() override;
  bool IsFinished() override;
  void End() override;
  void Interrupted() override;
};
