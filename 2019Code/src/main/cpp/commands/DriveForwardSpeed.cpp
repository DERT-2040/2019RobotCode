/*----------------------------------------------------------------------------*/
/* Copyright (c) 2018 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/DriveForwardSpeed.h"
#include "Robot.h"

DriveForwardSpeed::DriveForwardSpeed(float _speed) {
  // Use Requires() here to declare subsystem dependencies
  Requires(&Robot::m_driveTrain);
 
  frc::SmartDashboard::PutString("Interrupted", "No");
  speed = _speed;
}

// Called just before this Command runs the first time
void DriveForwardSpeed::Initialize() {
}

// Called repeatedly when this Command is scheduled to run
void DriveForwardSpeed::Execute() 
{
  Robot::m_driveTrain.DriveSpeed(speed);
}

// Make this return true when this Command no longer needs to run execute()
bool DriveForwardSpeed::IsFinished() { return false; }

// Called once after isFinished returns true
void DriveForwardSpeed::End() {}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void DriveForwardSpeed::Interrupted() {
  
  frc::SmartDashboard::PutString("Interrupted", "Yes");
}
