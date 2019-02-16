/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/Lift.h"
#include <iostream>

Lift::Lift() : Subsystem("Lift") 
{

  talonTimeoutMs = 30;
  liftCruiseVelocity = 10000;
  liftAcceleration = 5000;
  liftkP = 0;
  liftkI = 0;
  liftkD = 0;
  liftkF = 0;

  masterLiftMotor = new WPI_TalonSRX(kMasterLiftMotorPort);
  masterLiftMotor->SetInverted(true);

  //What type of encoder is it
  masterLiftMotor->ConfigSelectedFeedbackSensor(FeedbackDevice::CTRE_MagEncoder_Relative, kPIDLoopIdx, talonTimeoutMs);
  masterLiftMotor->SetSensorPhase(true);
  masterLiftMotor->SetSelectedSensorPosition(0, kPIDLoopIdx, talonTimeoutMs);

  masterLiftMotor->Config_kP(kSlotIdx, liftkP, talonTimeoutMs);
  masterLiftMotor->Config_kI(kSlotIdx, liftkI, talonTimeoutMs);
  masterLiftMotor->Config_kD(kSlotIdx, liftkD, talonTimeoutMs);
  masterLiftMotor->Config_kF(kSlotIdx, liftkF, talonTimeoutMs);
  masterLiftMotor->ConfigMotionCruiseVelocity(liftCruiseVelocity);
  masterLiftMotor->ConfigMotionCruiseVelocity(liftAcceleration);

  secondLiftMotor = new WPI_TalonSRX(kSecondLiftMotorPort);
  secondLiftMotor->SetInverted(false);
  secondLiftMotor->Follow(*masterLiftMotor);

  fourBarMotor = new WPI_TalonSRX(kFourBarMotorPort);
  fourBarMotor->SetInverted(false);
  fourBarMotor->ConfigSelectedFeedbackSensor(FeedbackDevice::Analog, kPIDLoopIdx, talonTimeoutMs);
  
  fourBarMotor->Config_kP(kSlotIdx, fbkP, talonTimeoutMs);
  fourBarMotor->Config_kI(kSlotIdx, fbkI, talonTimeoutMs);
  fourBarMotor->Config_kD(kSlotIdx, fbkD, talonTimeoutMs);
  fourBarMotor->Config_kF(kSlotIdx, fbkF, talonTimeoutMs);
  fourBarMotor->ConfigMotionCruiseVelocity(fourBarCruiseVelocity);
  fourBarMotor->ConfigMotionAcceleration(fourBarAcceleration);

}

  std::cout << calculateAggregateSpeedCapLift() << std::endl;
  std::cout << calculateAggregateSpeedCapFourBar() << std::endl;
  

void Lift::InitDefaultCommand() 
{
  // SetDefaultCommand(new MySpecialCommand());
}

void Lift::setElevatorHeight(double height)
{
  elevatorHeightTarget = height;
  masterLiftMotor->Set(ControlMode::MotionMagic, height*heightToTickRatio);
}

void Lift::setFourBarHeight(double height)
{
  fbHeightTarget = height;
  double angle = asin(height/fourBarLength) * 180 / M_PI;
}
void Lift::setLiftHeight(double height, double distance){
  
}
bool Lift::atElevatorHeight(){
 if(abs(secondLiftMotor->GetSelectedSensorPosition() - elevatorHeightTarget)<1000){//replace with tolerable error
    return true;
 }
 return false;
}
bool Lift::atFourBarHeight(){
 if(abs(masterLiftMotor->GetSelectedSensorPosition() - fbHeightTarget)<1000){//replace with tolerable error
    return true;
 }
 return false;
}

float Lift::calculateAggregateSpeedCapLift(){
  float modifierCombined = calculateCombinedSpeedCap();
  float modifierLift = calculateElevatorSpeedCap();
  if (modifierLift > modifierCombined){
    return modifierLift;
  }
  return modifierCombined;
}
float Lift::calculateAggregateSpeedCapFourBar(){
  float modifierCombined = calculateCombinedSpeedCap();
  float modifierFourbar = calculateFourBarSpeedCap();
  if (modifierFourbar > modifierCombined){
    return modifierFourbar;
  }
  return modifierCombined; 
}
float Lift::calculateCombinedSpeedCap(){
  float fourbarDistance = getFourBarDistance();
  float totalHeight = getTotalHeight();
  float currentTotalSlowdownDistance;
  float currentMinHeight;
  float modifier = 1;
  if(fourbarDistance < 7){
    currentTotalSlowdownDistance = slowdownDistanceIn;
    currentMinHeight = minDistIn;
  }
  else {
    currentTotalSlowdownDistance = slowdownDistanceOut;
    currentMinHeight = minDistOut;
  }
  if(totalHeight  < currentTotalSlowdownDistance){
    modifier = (currentMinHeight-totalHeight)/currentMinHeight;
  }
  return modifier;

}
float Lift::calculateFourBarSpeedCap(){
  float fourbarAngle = getFourBarAngle();
  float modifier = 1;
  if(fabs(fourbarAngle)>slowDownAngle){
    modifier = (limitAngle<fourbarAngle)/limitAngle;
  } 
  return modifier;
}
float Lift::calculateElevatorSpeedCap(){
  float elevatorHeight = getElevatorHeight();
  float modifier = 1;
  if(elevatorHeight>slowDownTopElevator){
    modifier = (limitTopElevator - elevatorHeight)/limitTopElevator;
  } 
  else if (elevatorHeight<slowDownBottomElevator){
    modifier = (limitBottomElevator - elevatorHeight)/ limitBottomElevator;
  }
  return fabs(modifier);
}
float Lift::getFourBarDistance(){
  return fourBarLength*sin(getFourBarAngle());
}
float Lift::getElevatorHeight(){
  return (masterLiftMotor->GetSensorCollection().GetQuadraturePosition()/ticksPerRotation)*inchesPerRotationElevator;
}
float Lift::getTotalHeight(){
  return getElevatorHeight() + fourBarLength*cos(getFourBarAngle());
}



