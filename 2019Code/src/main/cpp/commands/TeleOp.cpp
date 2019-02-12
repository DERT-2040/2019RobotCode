/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/TeleOp.h"
#include "Robot.h"

TeleOp::TeleOp() {
  AddParallel(new DriveWithJoySticks());
  ///*
  if(Robot::m_oi.gamepad->GetRawButton(1)){
    AddParallel(new DeliverGamePiece(1));
  }
  else if(Robot::m_oi.gamepad->GetRawButton(2)){
    AddParallel(new DeliverGamePiece(2));
  }
  else if(Robot::m_oi.gamepad->GetRawButton(4)){
    AddParallel(new DeliverGamePiece(4));
  }
  else if(Robot::m_oi.gamepad->GetPOV(0)==180){
    AddParallel(new SetLiftState(0,false));
  }
  if(Robot::m_oi.gamepad->GetRawButton(9) && Robot::m_oi.gamepad->GetRawButton(10)){
    frc::Scheduler::GetInstance()->RemoveAll();
  }
  //*/
  frc::SmartDashboard::PutString("Mode", "TeleOp");
}
