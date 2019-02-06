/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "OI.h"

#include <frc/WPILib.h>
#include "commands/PickupCargo.h"
#include "commands/PickupHatch.h"

OI::OI() {
  // Process operator interface input here.
  gamepad = new frc::Joystick(0);
  BButton = new frc::JoystickButton(gamepad,3);
  AButton = new frc::JoystickButton(gamepad,2);

  BButton->WhenPressed(new PickupCargo());
  AButton->WhenPressed(new PickupHatch());
}
