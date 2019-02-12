/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/manualLift.h"

manualLift::manualLift() {
  // Use Requires() here to declare subsystem dependencies
  // eg. Requires(Robot::chassis.get());
  Requires(&Robot::m_lift);
}

// Called just before this Command runs the first time
void manualLift::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void manualLift::Execute() 
{
  Robot::m_lift.elevatorManualControl(Robot::m_oi.gamepad->GetRawAxis(5));
};

// Make this return true when this Command no longer needs to run execute()
bool manualLift::IsFinished() { return false; }

// Called once after isFinished returns true
void manualLift::End() {}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void manualLift::Interrupted() {}
