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

class Slider : public frc::Subsystem 
{

 private:

  //None of the motion/PIDF values are tuned
  const int slotIdx = 0;
  const int kPIDLoopIdx = 0;
  double kP, kI, kD, kF;
  const int timeoutMs = 30;
  double cruiseVelocity = 1000;
  double motionAccel = 500;

  double position;
  double previousPosition = 0;
  const double inchToTickRatio = 0.0;
  double tickPosition;
  frc::AnalogInput * rawHallSensorInput;
  frc::AnalogTrigger * rawHallSensorTrigger;
  frc::Counter * distanceTraveled;
  frc::DigitalInput * reCenterer;
  WPI_TalonSRX * sliderMotor;
  
 public:

  Slider();
  void Periodic() override;
  void InitDefaultCommand() override;
  void ManualControl(float speed);
  void setPosition(double _position);
  double getPosition();
  bool atPosition();
  void setSpeed(float speed);

};
