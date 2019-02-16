/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/DeployGamePiece.h"
#include "Robot.h"
#include <iostream>
DeployGamePiece::DeployGamePiece() {
  // Use Requires() here to declare subsystem dependencies
  // eg. Requires(Robot::chassis.get());
  Requires(&Robot::m_intake);
  //SetInterruptible(false);
  closed = false;
  
}

// Called just before this Command runs the first time
void DeployGamePiece::Initialize() {
  if(Robot::m_intake.IsClosed()){ 
    closed = true;
  }
  std::cout << "initialized" << std::endl;
}

// Called repeatedly when this Command is scheduled to run
void DeployGamePiece::Execute() {
    if(!closed){
      Robot::m_intake.DeployCargo();
    }
    else{
      Robot::m_intake.DeployHatch();
    }
}

// Make this return true when this Command no longer needs to run execute()
bool DeployGamePiece::IsFinished() { return Robot::m_oi.gamepad->GetRawAxis(2)<0.75; }

// Called once after isFinished returns true
void DeployGamePiece::End() {
  Robot::m_intake.SetWheelSpeed(0);
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void DeployGamePiece::Interrupted() {}
