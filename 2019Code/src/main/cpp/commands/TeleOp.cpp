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
    //AddParallel(new SetLiftHeight(1, 0));
    //Test Command
    AddParallel(new setFourBarAngle(-45));
    //AddParallel(new SetLiftState(3));
  }
  else if(Robot::m_oi.gamepad->GetRawButton(2))
  {
    //Middle rocket
    //AddParallel(new SetLiftHeight(35, 0));
    //Test Commands
    AddParallel(new setFourBarAngle(0));
    //AddParallel(new SetLiftHeight(30, 0));

    //AddParallel(new SetLiftState(4));
  } 
  else if(Robot::m_oi.gamepad->GetRawButton(4))
  {
    //High rocket
    //AddParallel(new SetLiftHeight(55, 45));
    //Test Commands
    AddParallel(new setFourBarAngle(45));
    //AddParallel(new SetLiftHeight(50, 0));
    //AddParallel(new SetLiftState(5));
  }
  else if(Robot::m_oi.gamepad->GetRawButton(10))
  {
    AddParallel(new ResetSlider());
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
    //AddParallel(new SetLiftState(1));
    //Low Hatch Pickup
  }
  else if(Robot::m_oi.gamepad->GetPOV(0)==270)
  {
    //Ground ball pickup
    //AddParallel(new SetLiftState(0));
    //AddParallel(new ResetSlider());
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
  if(Robot::m_oi.gamepad->GetPOV(0)!=0 && Robot::m_oi.gamepad->GetPOV(0) != 180){
      AddParallel(new manualSpatula(0));
  }
}
