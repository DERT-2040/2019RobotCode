/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc/commands/CommandGroup.h>
#include "commands/DriveWithJoySticks.h"
#include "commands/SetLiftState.h"
#include "frc/WPILib.h"
#include "commands/DeliverGamePiece.h"
#include "commands/manualLift.h"
#include "commands/DeployGamePiece.h"
#include "commands/SetLiftHeight.h"
#include "commands/PickupCargo.h"
#include "commands/PickupHatch.h"
#include "commands/ManualSlider.h"
#include "commands/setFourBarAngle.h"
#include "commands/manualSpatula.h"

class TeleOp : public frc::CommandGroup {
 private:
 public:
  TeleOp();
};
