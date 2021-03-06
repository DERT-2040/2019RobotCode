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
  joystickL = new frc::Joystick(0);
  joystickR = new frc::Joystick(1);
  gamepad = new frc::Joystick(2);
  LBButton = new frc::JoystickButton(gamepad,5);
  RBButton = new frc::JoystickButton(gamepad,6);
  LBButton->WhileHeld(new PickupCargo());
  RBButton->WhileHeld(new PickupHatch());
}
