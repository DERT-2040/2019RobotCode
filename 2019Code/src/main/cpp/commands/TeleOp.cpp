/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/TeleOp.h"
#include <iostream>
#include "Robot.h"

TeleOp::TeleOp() {
  AddParallel(new manualLift());
  AddParallel(new manualSlider());
  AddParallel(new DriveWithJoySticks());

  if(Robot::m_oi.gamepad->GetRawButton(1)){
    //AddParallel(new setFourBarAngle(-45));
    AddParallel(new SetLiftHeight(24.8, -48));
  }
  else if(Robot::m_oi.gamepad->GetRawButton(2)){
    //AddParallel(new setFourBarAngle(0));
    AddParallel(new SetLiftHeight(48.98, -24.4));
  } 
  else if(Robot::m_oi.gamepad->GetRawButton(4)){
    //AddParallel(new setFourBarAngle(45));
    AddParallel(new SetLiftHeight(60.80, 60.0));
  }
  else if(Robot::m_oi.gamepad->GetPOV(0)==180){
    //AddParallel(new SetLiftState(0,false));
  }
  if(Robot::m_oi.gamepad->GetRawButton(9) && Robot::m_oi.gamepad->GetRawButton(10)){
    frc::Scheduler::GetInstance()->RemoveAll();
  }
  
  if(Robot::m_oi.gamepad->GetRawAxis(3)>0.75){
    AddParallel(new DeployGamePiece());
  }

  if(Robot::m_oi.gamepad->GetRawAxis(2)>0.75){
    AddParallel(new DeployGamePiece());
  }
  
  if(Robot::m_oi.gamepad->GetRawButton(3)){
    AddParallel(new SetLiftHeight(5.5, -15));
  }
  
  if(Robot::m_oi.gamepad->GetRawButton(6)){
    //AddParallel(new PickupHatch());
  }
  //*/
  frc::SmartDashboard::PutString("Mode", "TeleOp");
}
