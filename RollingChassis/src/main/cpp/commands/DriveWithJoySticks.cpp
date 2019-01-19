/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/DriveWithJoySticks.h"
#include "Robot.h"
#include <iostream>
DriveWithJoySticks::DriveWithJoySticks() {
  // Use Requires() here to declare subsystem dependencies
  Requires(&Robot::m_driveTrain);
}

// Called just before this Command runs the first time
void DriveWithJoySticks::Initialize() {
  }

// Called repeatedly when this Command is scheduled to run
void DriveWithJoySticks::Execute() 
{
  Robot::m_driveTrain.CurveDrive();
}

// Make this return true when this Command no longer needs to run execute()
bool DriveWithJoySticks::IsFinished() { return true; }

// Called once after isFinished returns true
void DriveWithJoySticks::End() {}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void DriveWithJoySticks::Interrupted() {

}
