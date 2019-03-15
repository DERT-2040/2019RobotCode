/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/ModeChooser.h"
#include "Robot.h"
#include "commands/TeleOp.h"
#include "commands/Auto.h"
ModeChooser::ModeChooser() : Subsystem("ModeChooser") {
  firstRun = true;
}
void ModeChooser::Periodic() {
  commandToRun = new TeleOp();
      commandToRun->Start();
  /*if(mode != newMode){
    if(newMode == 0){s
    }
    if(newMode == 1){
    }
    mode = newMode;
  }
  if (firstRun){
      mode = 0;
      newMode = 0;
      frc::SmartDashboard::PutString("FirstRun", "Activated");
      commandToRun = new TeleOp();
      commandToRun->Start();
      firstRun = false;
  }*/
}
void ModeChooser::InitDefaultCommand() {
  // Set the default command for a subsystem here.
  // SetDefaultCommand(new MySpecialCommand());
}

// Put methods for controlling this subsystem
// here. Call these from Commands.
