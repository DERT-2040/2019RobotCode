/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/setFourBarAngle.h"
#include "Robot.h"
setFourBarAngle::setFourBarAngle(double _angle) {
  // Use Requires() here to declare subsystem dependencies
  // eg. Requires(Robot::chassis.get());
  Requires(&Robot::m_lift);
  angle = _angle;
}

// Called just before this Command runs the first time
void setFourBarAngle::Initialize() 
{
  previousError = 0;
  integral = 0;
}

// Called repeatedly when this Command is scheduled to run
void setFourBarAngle::Execute() 
{
  //Robot::m_lift.setFourBarAngle(angle);
  double resultant;
  
  error = angle - Robot::m_lift.getFourBarAngle();
  deriv = (error - previousError)/0.02;
  integral += error*0.02;

  resultant = error*1 + deriv*0.0 + integral*0.0;
  Robot::m_lift.fourbarManualControl(resultant);

}

// Make this return true when this Command no longer needs to run execute()
bool setFourBarAngle::IsFinished() { return false; }

// Called once after isFinished returns true
void setFourBarAngle::End() {}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void setFourBarAngle::Interrupted() {}
