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
  masterLiftMotor = new WPI_TalonSRX(kMasterLiftMotorPort);
  masterLiftMotor->SetInverted(true);

  //What type of encoder is it
  masterLiftMotor->ConfigSelectedFeedbackSensor(FeedbackDevice::QuadEncoder, kPIDLoopIdx, talonTimeoutMs);
  masterLiftMotor->SetSensorPhase(true);
  masterLiftMotor->SetSelectedSensorPosition(liftStartingHeight, kPIDLoopIdx, talonTimeoutMs);

  masterLiftMotor->Config_kP(kElevatorMotionSlotIdx, mLiftkP, talonTimeoutMs);
  masterLiftMotor->Config_kI(kElevatorMotionSlotIdx, mLiftkI, talonTimeoutMs);
  masterLiftMotor->Config_kD(kElevatorMotionSlotIdx, mLiftkD, talonTimeoutMs);
  masterLiftMotor->Config_kF(kElevatorMotionSlotIdx, mLiftkF, talonTimeoutMs);

  masterLiftMotor->Config_kP(kElevatorVelocitySlotIdx, vLiftkP, talonTimeoutMs);
  masterLiftMotor->Config_kI(kElevatorVelocitySlotIdx, vLiftkI, talonTimeoutMs);
  masterLiftMotor->Config_kD(kElevatorVelocitySlotIdx, vLiftkD, talonTimeoutMs);
  masterLiftMotor->Config_kF(kElevatorVelocitySlotIdx, vLiftkF, talonTimeoutMs);

  masterLiftMotor->Config_kP(kElevatorPositionSlotIdx, pLiftkP, talonTimeoutMs);
  masterLiftMotor->Config_kI(kElevatorPositionSlotIdx, pLiftkI, talonTimeoutMs);
  masterLiftMotor->Config_kD(kElevatorPositionSlotIdx, pLiftkD, talonTimeoutMs);
  masterLiftMotor->Config_kF(kElevatorPositionSlotIdx, pLiftkF, talonTimeoutMs);

  masterLiftMotor->ConfigMotionCruiseVelocity(liftCruiseVelocity);
  masterLiftMotor->ConfigMotionAcceleration(liftAcceleration);
  masterLiftMotor->ConfigAllowableClosedloopError(kElevatorMotionSlotIdx, liftPIDError, talonTimeoutMs);
  //masterLiftMotor->GetSensorCollection().SetQuadraturePosition(0, talonTimeoutMs);

  secondLiftMotor = new WPI_TalonSRX(kSecondLiftMotorPort);
  secondLiftMotor->SetInverted(true);
  secondLiftMotor->Follow(*masterLiftMotor);

  fourBarMotor = new WPI_TalonSRX(kFourBarMotorPort);
  fourBarMotor->SetInverted(false);
  fourBarMotor->ConfigSelectedFeedbackSensor(FeedbackDevice::Analog, kPIDLoopIdx, talonTimeoutMs);
  
  fourBarMotor->Config_kP(kFourBarMotionSlotIdx, mFourBarkP, talonTimeoutMs);
  fourBarMotor->Config_kI(kFourBarMotionSlotIdx, mFourBarkI, talonTimeoutMs);
  fourBarMotor->Config_kD(kFourBarMotionSlotIdx, mFourBarkD, talonTimeoutMs);
  fourBarMotor->Config_kF(kFourBarMotionSlotIdx, mFourBarkF, talonTimeoutMs);

  fourBarMotor->Config_kP(kFourBarVelocitySlotIdx, vFourBarkP, talonTimeoutMs);
  fourBarMotor->Config_kI(kFourBarVelocitySlotIdx, vFourBarkI, talonTimeoutMs);
  fourBarMotor->Config_kD(kFourBarVelocitySlotIdx, vFourBarkD, talonTimeoutMs);
  fourBarMotor->Config_kF(kFourBarVelocitySlotIdx, vFourBarkF, talonTimeoutMs);

  fourBarMotor->ConfigMotionCruiseVelocity(fourBarCruiseVelocity);
  fourBarMotor->ConfigMotionAcceleration(fourBarAcceleration);
  fourBarMotor->ConfigAllowableClosedloopError(kFourBarMotionSlotIdx, fourBarPIDError, talonTimeoutMs);
  
}

void Lift::Periodic()
{ 
  //std::cout << masterLiftMotor->GetSensorCollection().GetQuadraturePosition() << std::endl;
  //std::cout << getFourBarAngle()<< std::endl;
  std::cout << calculateAggregateSpeedCapLift() << std::endl;
  std::cout << calculateAggregateSpeedCapFourBar() << std::endl;
  

}

void Lift::InitDefaultCommand() 
{
  //SetDefaultCommand(new MySpecialCommand());
}

double Lift::getFourBarAngle()
{
  return (fourBarMotor->GetSensorCollection().GetAnalogInRaw()/ticksPerVolt-startingInclinomterVolatage)/voltsPerDegree - 90;
}

void Lift::setElevatorHeight(double height)
{
  eMotionMagicActive = true;
  height = height/2;
  double ticks = height/inchesPerRotationElevator*ticksPerRotation;
  if(ticks < maxElevatorTickHeight && ticks > minElevatorTickHeight)
  {
    masterLiftMotor->SelectProfileSlot(kElevatorMotionSlotIdx, kPIDLoopIdx);
    masterLiftMotor->Set(ControlMode::MotionMagic, ticks);
  }
}

void Lift::elevatorManualControl(double output)
{
  float slowDown = .75;
  double maxTicks = maxSlowDownHeight/inchesPerRotationElevator*ticksPerRotation;
  double minTicks = minSlowDownHeight/inchesPerRotationElevator*ticksPerRotation;
  if(output < 0 && masterLiftMotor->GetSensorCollection().GetQuadraturePosition()<minTicks){
    std::cout << "min" << std::endl;
    slowDown = 0.09;
  }
  if(output > 0 && masterLiftMotor->GetSensorCollection().GetQuadraturePosition()>maxTicks){
    slowDown = slowDownConstant;
  }
  if(!eMotionMagicActive || (eMotionMagicActive && fabs(output)> 0.025)){
    masterLiftMotor->Set(ControlMode::PercentOutput, output*slowDown +kFeedforwardElevator);
    eMotionMagicActive = false;
  }
}

void Lift::fourbarManualControl(double output)
{
  float feedForward = fabs(.28 *cos(getFourBarAngle() * M_PI / 180));
  if(fabs(getFourBarAngle()) > 70)
  {
    feedForward = 0;
  } 
  float slowDown = 1;
  if(output > 0 && getFourBarAngle()<-45){
    slowDown = 0.04;
  }
  else if(output < 0 && getFourBarAngle()>45){
    slowDown = 0.04;
  }
  /*if(!eMotionMagicActive || (eMotionMagicActive && abs(output)> 0.025)){
    masterLiftMotor->Set(ControlMode::PercentOutput, output*slowDown +kFeedforwardElevator);
    eMotionMagicActive = false;
  }*/
  std::cout << fourBarMotor->GetSensorCollection().GetAnalogInRaw() << std::endl;
  std::cout << -feedForward << std::endl;
  fourBarMotor->Set(ControlMode::PercentOutput, slowDown*output-feedForward);
}

void Lift::velocityElevatorControl(double speed)
{
  if(fabs(speed) > 0.025)
  {
    masterLiftMotor->SelectProfileSlot(kElevatorVelocitySlotIdx, kPIDLoopIdx);
    masterLiftMotor->Set(ControlMode::Velocity, speed*maxLiftSpeed);
  }
  else
  {
    masterLiftMotor->SelectProfileSlot(kElevatorPositionSlotIdx, kPIDLoopIdx);
    masterLiftMotor->Set(ControlMode::Velocity, 0);
  }
}

void Lift::velocityFourBarControl(double speed)
{
  if(fabs(speed) > 0.025)
  {
    fourBarMotor->SelectProfileSlot(kFourBarVelocitySlotIdx, kPIDLoopIdx);
    fourBarMotor->Set(ControlMode::Velocity, speed*maxFourBarVelocity);
    std::cout << fourBarMotor->GetClosedLoopError() << std::endl;
  }
  else
  {
    //fourBarMotor->Set(ControlMode::Velocity, 0);
  }
}

void Lift::setFourBarHeight(double height)
{
  fbHeightTarget = height;
  double angle = asin(height/fourBarLength) * 180 / M_PI;
  angle += 90; 
  double volts = angle*voltsPerDegree;
  double ticks = volts*ticksPerVolt;
  fourBarMotor->SelectProfileSlot(kFourBarMotionSlotIdx, talonTimeoutMs);
  fourBarMotor->Set(ControlMode::MotionMagic, ticks);
}

void Lift::setFourBarAngle(double angle)
{
  angle += 90;
  float ticks = angle * voltsPerDegree * ticksPerVolt;
  fourBarMotor->SelectProfileSlot(kFourBarMotionSlotIdx, talonTimeoutMs);
  fourBarMotor->Set(ControlMode::MotionMagic, ticks);
}

void Lift::setFourBarX(double x)
{ 
  double fbX = x - lengthOfImplement;
  double angle = acos(fbX/fourBarLength) * 180 / M_PI;
  double inverseAngle = -angle;
  double ticks;
  if(fabs(angle) < 90)
  {
    if(angle - (getFourBarAngle() - 90) < inverseAngle - (getFourBarAngle() - 90))
    {
      ticks = (angle*voltsPerDegree)*ticksPerVolt;
    }
    else
    {
      ticks = (inverseAngle*voltsPerDegree)*ticksPerVolt;
    }
    fourBarMotor->SelectProfileSlot(kFourBarMotionSlotIdx, talonTimeoutMs);
    fourBarMotor->Set(ControlMode::MotionMagic, ticks);
  }
}

void Lift::constantHeightLift(float totalHeight, float fourBarXLength)
{
  double angle;
  double elevatorHeight;
  fourBarXLength = fourBarXLength - lengthOfImplement;
  angle = acos(fourBarXLength/fourBarLength) * 180 / M_PI - 90;

  fourBarMotor->SelectProfileSlot(kFourBarMotionSlotIdx, talonTimeoutMs);
  masterLiftMotor->SelectProfileSlot(kElevatorMotionSlotIdx, talonTimeoutMs);

  if(fabs(angle) < 90)
  {

    float aElevatorHeight = totalHeight - fourBarLength*(sin(angle*M_PI/180));
    float iAElevatorHeight = totalHeight - fourBarLength*(sin(-1*angle*M_PI/180));

    if(aElevatorHeight < maxElevatorHeight && aElevatorHeight > minElevatorHeight 
      && iAElevatorHeight < maxElevatorHeight && iAElevatorHeight > minElevatorHeight)
    {
      if(angle - (getFourBarAngle() - 90) < -angle - (getFourBarAngle() - 90))
      {
        angle = angle;
      }
      else
      {
        angle = -angle;
      }
      setElevatorHeight(totalHeight - fourBarLength*(sin(angle*M_PI/180)));
      setFourBarAngle(angle);
    }
    else if(aElevatorHeight < maxElevatorHeight && aElevatorHeight > minElevatorHeight)
    {
      setElevatorHeight(aElevatorHeight);
      setFourBarAngle(angle);
    }
  }
}

bool Lift::atElevatorHeight()
{
 if(fabs(masterLiftMotor->GetSelectedSensorPosition() - elevatorHeightTarget)<1000){//replace with tolerable error
    return true;
 }
 return false;
}

bool Lift::atFourBarHeight(){
 if(fabs(fourBarMotor->GetSelectedSensorPosition() - fbHeightTarget)<1000){//replace with tolerable error
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
