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

# define M_PI 3.14159265358979323846

class Lift : public frc::Subsystem 
{
 
 private:

  WPI_TalonSRX * masterLiftMotor;
  WPI_TalonSRX * secondLiftMotor;
  WPI_TalonSRX * fourBarMotor;

  double talonTimeoutMs;
  double liftkP, liftkI, liftkD, liftkF;
  double fbkP, fbkI, fbkD, fbkF;
  double liftCruiseVelocity, liftAcceleration;
  double fourBarCruiseVelocity, fourBarAcceleration;

  double elevatorHeightTarget = 0;
  double fbHeightTarget = 0;
  //constants
  const int kPIDLoopIdx = 0;
  const int kSlotIdx = 0;
  const double heightToTickRatio = 0;
  const double angleToUnitRatio = 0;
  const double fourBarLength = 0;

  float calculateAggregateSpeedCapLift();
  float calculateAggregateSpeedCapFourBar();
  float calculateCombinedSpeedCap();
  float calculateFourBarSpeedCap();
  float calculateElevatorSpeedCap();

  float multiplier = 1;
  const float slowdownDistanceIn = 8;
  const float slowdownDistanceOut = 5.5;
  const float minDistIn = 0;
  const float minDistOut = -2.5;
  const float slowDownAngle = 50;
  const float limitAngle = 73;
  const float slowDownBottomElevator = 7;
  const float slowDownTopElevator = 25;
  const float limitBottomElevator = 32;
  const float limitTopElevator = 0;
 public:

  Lift();
  void InitDefaultCommand() override;
  void setElevatorHeight(double height);
  void setFourBarHeight(double height);
  void setLiftHeight(double height,double distance);
  bool atElevatorHeight();
  bool atFourBarHeight();
  float getFourBarDistance(); //Without Implement
  float getTotalHeight();
  float getElevatorHeight();

};
