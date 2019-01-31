/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/SetElevatorHeight.h"
#include "Robot.h"

SetElevatorHeight::SetElevatorHeight(float _height) {
  // Use Requires() here to declare subsystem dependencies
  // eg. Requires(Robot::chassis.get());
  height = _height;
  Requires(&Robot::m_lift);
}

// Called just before this Command runs the first time
void SetElevatorHeight::Initialize() {
  Robot::m_lift.setElevatorHeight(height);
}

// Called repeatedly when this Command is scheduled to run
void SetElevatorHeight::Execute() {}

// Make this return true when this Command no longer needs to run execute()
bool SetElevatorHeight::IsFinished() { return false; }

// Called once after isFinished returns true
void SetElevatorHeight::End() {
      Robot::m_lift.atElevatorHeight();
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void SetElevatorHeight::Interrupted() {}
