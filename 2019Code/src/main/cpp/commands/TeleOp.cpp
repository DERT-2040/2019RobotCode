/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/TeleOp.h"
#include <iostream>
#include "Robot.h"

TeleOp::TeleOp() 
{

  AddParallel(new DriveWithJoySticks());

  if(Robot::m_oi.gamepad->GetRawButton(1))
  {
    //Hatch pickup and low rocket
    AddParallel(new SetLiftHeight(21, -38));
    //AddParallel(new setFourBarAngle(-45));
  }
  else if(Robot::m_oi.gamepad->GetRawButton(2))
  {
    //Middle rocket
    AddParallel(new SetLiftHeight(34, 30));
    //AddParallel(new setFourBarAngle(0));
  } 
  else if(Robot::m_oi.gamepad->GetRawButton(4))
  {
    //High rocket
    AddParallel(new SetLiftHeight(55, 30));
    //AddParallel(new setFourBarAngle(45));
  }
  else if(Robot::m_oi.gamepad->GetRawButton(3))
  {

    //low ball
  }
  else if(Robot::m_oi.gamepad->GetPOV(0) == 180)
  {
    AddParallel(new manualSpatula(-1));
    //ground hatch pickup up 
  }
  else if(Robot::m_oi.gamepad->GetPOV(0) == 0)
  {
    AddParallel(new manualSpatula(1));
    //ground hatch pickup up 
  }
  else if(Robot::m_oi.gamepad->GetPOV(0) == 90)
  {
    //high ball
  }
  else if(Robot::m_oi.gamepad->GetPOV(0)==270)
  {
    //Ground ball pickup
    AddParallel(new SetLiftHeight(5.5, -15));
  }
  else
  {
    AddParallel(new manualLift());
    AddParallel(new manualSlider());
  }

  if(fabs(Robot::m_oi.gamepad->GetRawAxis(2)) > 0.75)
  {
    AddParallel(new DeployGamePiece());
  }

  if(Robot::m_oi.gamepad->GetRawButton(9) && Robot::m_oi.gamepad->GetRawButton(10)){
    frc::Scheduler::GetInstance()->RemoveAll();
  }
 if(Robot::m_oi.gamepad->GetPOV(0)!=0 && Robot::m_oi.gamepad->GetPOV(0) != 180){
    AddParallel(new manualSpatula(0));
 }
}
