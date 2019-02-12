/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/Intake.h"

Intake::Intake() : frc::Subsystem("Intake") {
  leftIntake = new WPI_VictorSPX(kLeftIntakeWheel);
  rightIntake = new WPI_VictorSPX(kRightIntakeWheel);
  state = 0;
  leftIntake->SetInverted(true);
  intakeSolenoid = new frc::DoubleSolenoid(1,kForwardIntakeSolenoid,kReverseIntakeSolenoid);
}

void Intake::InitDefaultCommand() {
  // Set the default command for a subsystem here.
  // SetDefaultCommand(new MySpecialCommand());
}
void Intake::Periodic(){

}
void Intake::SetWheelSpeed(float speed){
  leftIntake->Set(speed);
  rightIntake->Set(speed);
}
void Intake::SetState(bool _state){
  if(_state != state){
    state = _state;
    if(state == 0){
      intakeSolenoid->Set(frc::DoubleSolenoid::Value::kForward);
      frc::SmartDashboard::PutString("Status","Open");
    }
    else{
      intakeSolenoid->Set(frc::DoubleSolenoid::Value::kReverse);
      frc::SmartDashboard::PutString("Status","Closed");
    }
  }
}
bool Intake::IsClosed(){
  return state;
}
// Put methods for controlling this subsystem
// here. Call these from Commands.
