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

class Lift : public frc::Subsystem 
{
 
 private:

  WPI_TalonSRX * masterLiftMotor;
  WPI_TalonSRX * secondLiftMotor;
  WPI_TalonSRX * fourBarMotor;

  double talonTimeoutMs;
  double liftkP, liftkI, liftkD, liftkF;
  double liftCruiseVelocity, liftAcceleration;

  //constants
  const int kPIDLoopIdx = 0;
  const int kSlotIdx = 0;
  const double heightToTickRatio = 0;

 public:

  Lift();
  void InitDefaultCommand() override;
  void setElevatorHeight(double height);

};
