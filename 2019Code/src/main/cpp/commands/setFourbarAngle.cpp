/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/setFourbarAngle.h"
#include "Robot.h"

setFourbarAngle::setFourbarAngle(double _angle){
  // Use Requires() here to declare subsystem dependencies
  // eg. Requires(Robot::chassis.get());
  Requires(&Robot::m_lift);
  angle = _angle;
}

// Called just before this Command runs the first time
void setFourbarAngle::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void setFourbarAngle::Execute() 
{
  Robot::m_lift.setFourBarAngle(angle);
}

// Make this return true when this Command no longer needs to run execute()
bool setFourbarAngle::IsFinished() 
{
  if(fabs(Robot::m_lift.getFourBarAngle() - angle) < 5)
  {
    return true;
  }
  else
  {
    return true;
  }
}

// Called once after isFinished returns true
void setFourbarAngle::End() {}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void setFourbarAngle::Interrupted() {}
