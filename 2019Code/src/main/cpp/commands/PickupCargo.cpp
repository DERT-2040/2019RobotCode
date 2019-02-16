/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/PickupCargo.h"
#include "Robot.h"

PickupCargo::PickupCargo() {
  // Use Requires() here to declare subsystem dependencies
  // eg. Requires(Robot::chassis.get());
  Requires(&Robot::m_intake);
}

// Called just before this Command runs the first time
void PickupCargo::Initialize() {
}

// Called repeatedly when this Command is scheduled to run
void PickupCargo::Execute() {
    Robot::m_intake.SetState(true);
    Robot::m_intake.SetWheelSpeed(1);
}

// Make this return true when this Command no longer needs to run execute()
bool PickupCargo::IsFinished() { 
  return (!Robot::m_oi.gamepad->GetRawButton(5));
  
}

// Called once after isFinished returns true
void PickupCargo::End() {
  Robot::m_intake.SetState(false);
  Robot::m_intake.SetWheelSpeed(0);
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void PickupCargo::Interrupted() {
  Robot::m_intake.SetState(false);
  Robot::m_intake.SetWheelSpeed(0);
  }
