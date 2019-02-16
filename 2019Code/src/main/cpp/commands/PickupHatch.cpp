/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/PickupHatch.h"
#include "Robot.h"

PickupHatch::PickupHatch() {
  // Use Requires() here to declare subsystem dependencies
  // eg. Requires(Robot::chassis.get());
  Requires(&Robot::m_intake);
}

// Called just before this Command runs the first time
void PickupHatch::Initialize() {
}

// Called repeatedly when this Command is scheduled to run
void PickupHatch::Execute() {
    Robot::m_intake.SetState(false);
}

// Make this return true when this Command no longer needs to run execute()
bool PickupHatch::IsFinished() { 
  return (!Robot::m_oi.gamepad->GetRawButton(6));
  
}

// Called once after isFinished returns true
void PickupHatch::End() {
  Robot::m_intake.SetState(true);
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void PickupHatch::Interrupted() {
  Robot::m_intake.SetState(true);
  }
