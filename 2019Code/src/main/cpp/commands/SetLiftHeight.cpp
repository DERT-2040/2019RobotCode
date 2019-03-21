/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/SetLiftHeight.h"
#include "Robot.h"

SetLiftHeight::SetLiftHeight(float _height, float _angle) {
  // Use Requires() here to declare subsystem dependencies
  // eg. Requires(Robot::chassis.get());
  height = _height;
  angle = _angle;
  Requires(&Robot::m_lift);
}

// Called just before this Command runs the first time
void SetLiftHeight::Initialize() {
  //Robot::m_lift.constantHeightLift(height,distance);
  Robot::m_lift.setLiftState(height, angle);
}

// Called repeatedly when this Command is scheduled to run
void SetLiftHeight::Execute() {}

// Make this return true when this Command no longer needs to run execute()
bool SetLiftHeight::IsFinished() { return  Robot::m_lift.atElevatorHeight() && Robot::m_lift.atFourBarHeight(); }

// Called once after isFinished returns true
void SetLiftHeight::End() {
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void SetLiftHeight::Interrupted() {}
