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

 public:

  Lift();
  void InitDefaultCommand() override;
  void setElevatorHeight(double height);
  void setFourBarHeight(double height);
  bool atElevatorHeight();
  bool atFourBarHeight();
};
