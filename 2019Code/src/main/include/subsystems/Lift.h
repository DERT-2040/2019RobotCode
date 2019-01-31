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
  double mLiftkP, mLiftkI, mLiftkD, mLiftkF;
  double vLiftkP, vLiftkI, vLiftkD, vLiftkF;

  double mFourBarkP, mFourBarkI, mFourBarkD, mFourBarkF;
  double vFourBarkP, vFourBarkI, vFourBarkD, vFourBarkF;

  double liftCruiseVelocity, liftAcceleration;
  double fourBarCruiseVelocity, fourBarAcceleration;

  //constants
  const int kPIDLoopIdx = 0;

  const int kElevatorMotionSlotIdx = 0;
  const int kElevatorVelocitySlotIdx = 1;

  const int kFourBarMotionSlotIdx = 0;
  const int kFourBarVelocitySlotIdx = 1;

  const double heightToTickRatio = 0;
  const double angleToUnitRatio = 0;
  const double fourBarLength = 0;
  const double maxLiftSpeed = 10000;

  const double liftPIDError = .01;
  const double fourBarPIDError = .01;



 public:

  Lift();
  void InitDefaultCommand() override;
  void setElevatorHeight(double height);
  void setFourBarHeight(double height);
  void joystickElevatorControl(double speed);
};
