/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/WaitForButtonPress.h"

WaitForButtonPress::WaitForButtonPress(int _buttonNum, bool _pressed) {
  // Use Requires() here to declare subsystem dependencies
  // eg. Requires(Robot::chassis.get());
  buttonNum = _buttonNum;
  pressed = _pressed;
  finished = false;
}

// Called just before this Command runs the first time
void WaitForButtonPress::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void WaitForButtonPress::Execute() {
  if (pressed){
    if(Robot::m_oi.gamepad->GetRawButton(buttonNum)){
      finished = true;
    }
  }
  else{
    if(!Robot::m_oi.gamepad->GetRawButton(buttonNum)){
      finished = true;
    }
  }
}

// Make this return true when this Command no longer needs to run execute()
bool WaitForButtonPress::IsFinished() { return finished; }

// Called once after isFinished returns true
void WaitForButtonPress::End() {}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void WaitForButtonPress::Interrupted() {}
