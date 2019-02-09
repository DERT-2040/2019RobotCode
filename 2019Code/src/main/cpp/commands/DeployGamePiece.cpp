/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/DeployGamePiece.h"
#include "Robot.h"
DeployGamePiece::DeployGamePiece() {
  // Use Requires() here to declare subsystem dependencies
  // eg. Requires(Robot::chassis.get());
  Requires(&Robot::m_intake);
}

// Called just before this Command runs the first time
void DeployGamePiece::Initialize() {
  if(Robot::m_intake.IsClosed()){ 
    SetTimeout(1);
  }
  else{
    SetTimeout(4);
  }
}

// Called repeatedly when this Command is scheduled to run
void DeployGamePiece::Execute() {
  if(Robot::m_slider.atPosition()){
    if(Robot::m_intake.IsClosed()){
      Robot::m_intake.SetWheelSpeed(-0.6);
    }
    else{
      Robot::m_intake.SetState(true);
      complete = true;  
    }
  }
}

// Make this return true when this Command no longer needs to run execute()
bool DeployGamePiece::IsFinished() { return complete; }

// Called once after isFinished returns true
void DeployGamePiece::End() {}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void DeployGamePiece::Interrupted() {}
