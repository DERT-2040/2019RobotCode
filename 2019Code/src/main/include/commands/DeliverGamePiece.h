/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc/commands/CommandGroup.h>
#include "commands/SetLiftState.h"
#include "frc/WPILib.h"
#include "Robot.h"

class DeliverGamePiece : public frc::CommandGroup {
 public:
  DeliverGamePiece(int level);//1 for first level, 2 for second level, 3 for third level
};
