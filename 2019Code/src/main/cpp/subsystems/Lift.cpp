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
  masterLiftMotor->SetSelectedSensorPosition(0, kPIDLoopIdx, talonTimeoutMs);
  masterLiftMotor->ConfigNominalOutputReverse(0, talonTimeoutMs);
  masterLiftMotor->ConfigNominalOutputForward(0, talonTimeoutMs);
  masterLiftMotor->ConfigPeakOutputForward(1, talonTimeoutMs);
  masterLiftMotor->ConfigPeakOutputReverse(-1, talonTimeoutMs);

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
  masterLiftMotor->GetSensorCollection().SetQuadraturePosition(0, talonTimeoutMs);
  masterLiftMotor->ConfigVoltageCompSaturation(12, talonTimeoutMs);
  masterLiftMotor->EnableVoltageCompensation(false);
  masterLiftMotor->ConfigForwardSoftLimitEnable(false);

  secondLiftMotor = new WPI_TalonSRX(kSecondLiftMotorPort);
  secondLiftMotor->SetInverted(true);
  secondLiftMotor->Follow(*masterLiftMotor);
  secondLiftMotor->ConfigNominalOutputReverse(0, talonTimeoutMs);
  secondLiftMotor->ConfigNominalOutputForward(0, talonTimeoutMs);
  secondLiftMotor->ConfigPeakOutputForward(1, talonTimeoutMs);
  secondLiftMotor->ConfigPeakOutputReverse(-1, talonTimeoutMs);
  secondLiftMotor->ConfigForwardSoftLimitEnable(false);

  fourBarMotor = new WPI_TalonSRX(kFourBarMotorPort);
  fourBarMotor->SetInverted(true);
  fourBarMotor->ConfigSelectedFeedbackSensor(FeedbackDevice::Analog, kPIDLoopIdx, talonTimeoutMs);
  fourBarMotor->SetSensorPhase(true);
  fourBarMotor->ConfigPeakOutputForward(1, talonTimeoutMs);
  fourBarMotor->ConfigPeakOutputReverse(-0.5, talonTimeoutMs);
  fourBarMotor->ConfigNominalOutputForward(0, talonTimeoutMs);
  fourBarMotor->ConfigNominalOutputReverse(0, talonTimeoutMs);
  fourBarMotor->ConfigVoltageCompSaturation(fourbarVoltageScale, talonTimeoutMs);
  fourBarMotor->EnableVoltageCompensation(true);

  fourBarMotor->Config_kP(kFourBarMotionSlotIdx, motionMagicFourBarkP, talonTimeoutMs);
  fourBarMotor->Config_kI(kFourBarMotionSlotIdx, motionMagicFourBarkI, talonTimeoutMs);
  fourBarMotor->Config_kD(kFourBarMotionSlotIdx, motionMagicFourBarkD, talonTimeoutMs);
  fourBarMotor->Config_kF(kFourBarMotionSlotIdx, motionMagicFourBarkF, talonTimeoutMs);

  fourBarMotor->Config_kP(kFourBarVelocitySlotIdx, vFourBarkP, talonTimeoutMs);
  fourBarMotor->Config_kI(kFourBarVelocitySlotIdx, vFourBarkI, talonTimeoutMs);
  fourBarMotor->Config_kD(kFourBarVelocitySlotIdx, vFourBarkD, talonTimeoutMs);
  fourBarMotor->Config_kF(kFourBarVelocitySlotIdx, vFourBarkF, talonTimeoutMs);

  fourBarMotor->ConfigMotionCruiseVelocity(fourBarCruiseVelocity);
  fourBarMotor->ConfigMotionAcceleration(fourBarAcceleration);
  fourBarMotor->ConfigAllowableClosedloopError(kFourBarMotionSlotIdx, fourBarPIDError, talonTimeoutMs);
  
  masterLiftMotor->ConfigPeakCurrentLimit(35);
  secondLiftMotor->ConfigPeakCurrentLimit(35);
  fourBarMotor->ConfigPeakCurrentLimit(35);

  masterLiftMotor->EnableCurrentLimit(false);
  secondLiftMotor->EnableCurrentLimit(false);
  fourBarMotor->EnableCurrentLimit(false);
}

void Lift::Periodic()
{ 
  fbFeedForward = fabs(horizontalHoldingPercent *cos(getFourBarAngle() * M_PI / 180));
  if(fabs(getFourBarAngle()) < 20)
  {
    fbFeedForward = fbFeedForward;
  }
  else if(getFourBarAngle() > 40)
  {
    fbFeedForward = fbFeedForward*0.7;
    //fbFeedForward = fabs(horizontalHoldingPercent *cos(getFourBarAngle() * M_PI / 180))*0;
  }
  //std::cout << "fourbar angle: " << getFourBarAngle() << std::endl;

  //std::cout << "Elevator pos inches: " << masterLiftMotor->GetSelectedSensorPosition()/ticksPerRotation*inchesPerRotationElevator << std::endl;
  //std::cout << "Elevator ticks: " << masterLiftMotor->GetSelectedSensorPosition() << std::endl;
  //std::cout << "fourbar feedforward \n" << fbFeedForward << std::endl;
}

double Lift::getFourBarAngle()
{
  return (fourBarMotor->GetSensorCollection().GetAnalogInRaw()/ticksPerVolt-startingInclinomterVolatage)/voltsPerDegree - 90;
}

//works and is tuned
void Lift::setElevatorHeight(double height)
{
  eMotionMagicActive = true;
  height = height/2;
  double ticks = height/inchesPerRotationElevator*ticksPerRotation;
  if(ticks < maxElevatorTickHeight && ticks > minElevatorTickHeight)
  {
    masterLiftMotor->SelectProfileSlot(kElevatorMotionSlotIdx, kPIDLoopIdx);
    masterLiftMotor->Set(ControlMode::MotionMagic, ticks, DemandType_ArbitraryFeedForward, kFeedforwardElevator);
  }
}

//works
void Lift::elevatorManualControl(double output)
{
  float slowDown = 1;
  if(!eMotionMagicActive || fabs(output) > 0.07)
  {
    eMotionMagicActive = false;
    double maxTicks = maxSlowDownHeight/inchesPerRotationElevator*ticksPerRotation;
    double minTicks = minSlowDownHeight/inchesPerRotationElevator*ticksPerRotation;
    if(output < 0 && masterLiftMotor->GetSensorCollection().GetQuadraturePosition()<minTicks){
      //slowDown = 0.09;
    }
    if(output > 0 && masterLiftMotor->GetSensorCollection().GetQuadraturePosition()>maxTicks){
      //slowDown = slowDownConstant;
    }
    if(!eMotionMagicActive || (eMotionMagicActive && fabs(output)> 0.025)){
      masterLiftMotor->Set(ControlMode::PercentOutput, slowDown*output+kFeedforwardElevator);
      eMotionMagicActive = false;
      //std::cout << "Motor out: " << masterLiftMotor->GetMotorOutputPercent() << std::endl;
      //std::cout << "Output " << slowDown*output << std::endl;
    }
  }
}

//works
void Lift::fourbarManualControl(double output)
{
  float slowDown = 1;
  float feedForward = fbFeedForward;
  if(fbMotionMagicActive == false || fabs(output) > 0.1)
  {
    fbMotionMagicActive = false;
    if(fabs(getFourBarAngle()) > 70)
    {
      feedForward = 0;
    } 
    if(output > 0 && getFourBarAngle()<-45){
      //slowDown = 0.04;
    }
    else if(output < 0 && getFourBarAngle()>45){
      //slowDown = 0.04;
    }

    fourBarMotor->Set(ControlMode::PercentOutput, output, DemandType_ArbitraryFeedForward, feedForward);
  }
}

//not tuned, I believe is is possible to tune with the Argos method
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

//not tuned
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
    fourBarMotor->Set(ControlMode::Velocity, 0);
  }
}


//untested
void Lift::setFourBarHeight(double height)
{
  fbHeightTarget = height;
  double angle = asin(height/fourBarLength) * 180 / M_PI;
  angle += 90; 
  double volts = angle*voltsPerDegree+startingInclinomterVolatage;
  double ticks = volts*ticksPerVolt;
  fourBarMotor->SelectProfileSlot(kFourBarMotionSlotIdx, talonTimeoutMs);
  fourBarMotor->Set(ControlMode::MotionMagic, ticks);
}

//tune enough its not very good
void Lift::setFourBarAngle(double angle)
{
  fbMotionMagicActive = true;
  if(angle > getFourBarAngle())
  {
    fourBarMotor->Config_kP(kFourBarMotionSlotIdx, upMMFourBarkP, talonTimeoutMs);
    fourBarMotor->Config_kI(kFourBarMotionSlotIdx, upMMFourBarkI, talonTimeoutMs);
    fourBarMotor->Config_kD(kFourBarMotionSlotIdx, upMMFourBarkD, talonTimeoutMs);
    fourBarMotor->Config_kF(kFourBarMotionSlotIdx, upMMFourBarkF, talonTimeoutMs);
  }
  else if(angle <= getFourBarAngle())
  {
    fourBarMotor  ->Config_kP(kFourBarMotionSlotIdx, downMMFourBarkP, talonTimeoutMs);
    fourBarMotor->Config_kI(kFourBarMotionSlotIdx, downMMFourBarkI, talonTimeoutMs);
    fourBarMotor->Config_kD(kFourBarMotionSlotIdx, downMMFourBarkD, talonTimeoutMs);
    fourBarMotor->Config_kF(kFourBarMotionSlotIdx, downMMFourBarkF, talonTimeoutMs);
  }
  angle += 90;
  float ticks = (angle * voltsPerDegree + startingInclinomterVolatage) * ticksPerVolt;
  fourBarMotor->SelectProfileSlot(kFourBarMotionSlotIdx, kPIDLoopIdx);
  
  fourBarMotor->Set(ControlMode::MotionMagic, ticks, DemandType_ArbitraryFeedForward, fbFeedForward);
}

//not tested
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
      setFourBarAngle(angle);
    }
    else
    {
      setFourBarAngle(inverseAngle);
    }
  }
}

//not tested
void Lift::constantHeightLift(float totalHeight, float fourBarXLength)
{
  double angle;
  double elevatorHeight;
  fourBarXLength = fourBarXLength - lengthOfImplement;
  angle = acos(fourBarXLength/fourBarLength) * 180 / M_PI - 90;

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

void Lift::setLiftState(double height, double angle)
{
  setFourBarAngle(angle);
  setElevatorHeight(height);
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
