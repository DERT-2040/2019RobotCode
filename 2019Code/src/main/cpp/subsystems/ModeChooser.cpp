/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/ModeChooser.h"
#include "Robot.h"
ModeChooser::ModeChooser() : Subsystem("ModeChooser") {
  
}
void ModeChooser::Periodic() {
  if(Robot::m_oi.gamepad->GetRawButton(1)){
      commandToRun = new Auto();
      commandToRun->Start();
  }
  else {
      commandToRun = new TeleOp();
      commandToRun->Start();
  }
}
void ModeChooser::InitDefaultCommand() {
  // Set the default command for a subsystem here.
  // SetDefaultCommand(new MySpecialCommand());
}

// Put methods for controlling this subsystem
// here. Call these from Commands.
