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
 private:
  float xDist;
 public:
  SetLiftState(int level, bool onApproach);// 0 for ground ball pickup, 1 for hatch pickup
                          // 2 for starting position, 3 for ground level, 4 for 1st level, 5 for second level
                          // If on Approach, four bar  will be extended out ready to place 
};
