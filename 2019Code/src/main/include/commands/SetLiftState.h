/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc/commands/CommandGroup.h>
#include "commands/SetLiftHeight.h"
#include "frc/WPILib.h"
#include "Robot.h"
class SetLiftState : public frc::CommandGroup {
 public:
  SetLiftState(int level);// 0 for ground ball pickup, 1 for hatch pickup
                          // 2 for ground level, 3 for 1st level, 4 for second level 
};
