/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/HatchPickup.h"
float speedModifier = 1;
HatchPickup::HatchPickup() : Subsystem("ExampleSubsystem") {
  hatchIntake = new WPI_TalonSRX(kHatchIntake);
  uprightSwitch = new frc::DigitalInput(kPickupUprightSwitch);
  retractedSwitch = new frc::DigitalInput(kPickupRetractedSwitch);
  deployedSwitch = new frc::DigitalInput(kPickupDeployedSwitch);
  }
void HatchPickup::InitDefaultCommand() {
  // Set the default command for a subsystem here.
  // SetDefaultCommand(new MySpecialCommand());
}
void HatchPickup::Periodic(){
  /*if (retractedSwitch->Get()){
    state = 0;
    previousState = 0;
  }
  else if (uprightSwitch->Get()){
    state = 1;
    previousState = 1;
  }
  else if (deployedSwitch->Get()){
    state = 2;
    previousState = 2;
  }
  else {
    previousState = state;
    state = 3; //Somewhere in the middle
  }*/
}

void HatchPickup::SetSpeed(){
  /*if(desiredState == state){
    motorOutput = 0;
  }
  hatchIntake->Set(motorOutput);*/
}
void HatchPickup::SetState(int _state){
  if (_state != state){
    if (_state > previousState){
      motorOutput = speedModifier;
    }
    else if (_state < previousState){
      motorOutput = -1*speedModifier;
    }
    else {
      if (_state >desiredState){
        motorOutput = -1*speedModifier;
      }
      else if (_state < desiredState){
        motorOutput = speedModifier;
      }
      else{
        motorOutput = 0;
      }
    }
    desiredState = _state;
  }
  else{
    desiredState = state;
    motorOutput = 0;
  }
}


// Put methods for controlling this subsystem
// here. Call these from Commands.
