/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc/commands/CommandGroup.h>
#include "commands/SetElevatorHeight.h"
#include "frc/WPILib.h"
#include "Robot.h"
class PlacePiece : public frc::CommandGroup {
 public:
  PlacePiece(int level);// 0 for ground, 1 for 1st level, 2 for second level 
};
