/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc/commands/Subsystem.h>
#include <ctre/Phoenix.h>
#include "RobotMap.h"
#include "frc/WPILib.h"

# define M_PI 3.14159265358979323846

class Lift : public frc::Subsystem 
{
 
 private:

  WPI_TalonSRX * masterLiftMotor;
  WPI_TalonSRX * secondLiftMotor;
  WPI_TalonSRX * fourBarMotor;

  double talonTimeoutMs;
  double mLiftkP, mLiftkI, mLiftkD, mLiftkF;
  double vLiftkP, vLiftkI, vLiftkD, vLiftkF;

  double mFourBarkP, mFourBarkI, mFourBarkD, mFourBarkF;
  double vFourBarkP, vFourBarkI, vFourBarkD, vFourBarkF;

  double liftCruiseVelocity, liftAcceleration;
  double fourBarCruiseVelocity, fourBarAcceleration;

  double elevatorHeightTarget = 0;
  double fbHeightTarget = 0;

  bool eMotionMagicActive = false;
  //constants
  const int kPIDLoopIdx = 0;

  const int kElevatorMotionSlotIdx = 0;
  const int kElevatorVelocitySlotIdx = 1;

  const int kFourBarMotionSlotIdx = 0;
  const int kFourBarVelocitySlotIdx = 1;

  const double heightToTickRatio = 0;
  const double angleToUnitRatio = 0;
  const double maxLiftSpeed = 10000;
  const double liftPIDError = .01;
  const double fourBarPIDError = .01;
  const double liftStartingHeight = 5.5;
  const double liftStartingTicks = liftStartingHeight/inchesPerRotationElevator*ticksPerRotation;

  const double voltsPerDegree = 0.02222222;
  const double ticksPerVolt = 255.75;
  
  //In inches
  const float maxElevatorHeight =  32;
  const float minElevatorHeight = 0;
  const float distanceToFourBarRotation = 6;
  const float fourBarLength = 13;
  const float inchesPerRotationElevator = 2.635 * M_PI;
  const float ticksPerRotation = 4096;
  const float maxElevatorTickHeight = maxElevatorHeight/inchesPerRotationElevator*ticksPerRotation;
  const float minElevatorTickHeight = 0;

  const float kFeedforwardElevator = 0.10;

  const float maxSlowDownHeight = 23;
  const float minSlowDownHeight = 15;
  const float slowDownConstant = 0.16;
 public:

  Lift();
  void Periodic() override;
  void InitDefaultCommand() override;
  void setElevatorHeight(double height);
  void setFourBarHeight(double height);
  void setLiftHeight(double height,double distance);
  bool atElevatorHeight();
  bool atFourBarHeight();
  void joystickElevatorControl(double speed);
  void setFourBarX(double x); 
  void setFourBarAngle(double angle);
  void constantHeightLift(float totalHeight, float fourBarXLength);
  void elevatorManualControl(double output);
  void fourbarManualControl(double output);
  double getFourBarAngle();
};
