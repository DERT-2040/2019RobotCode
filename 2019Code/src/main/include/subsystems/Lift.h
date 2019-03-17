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
#include <math.h>

# define M_PI 3.14159265358979323846

class Lift : public frc::Subsystem 
{
 
 private:

  WPI_TalonSRX * masterLiftMotor;
  WPI_TalonSRX * secondLiftMotor;
  WPI_TalonSRX * fourBarMotor;

  double talonTimeoutMs = 30;

  double elevatorHeightTarget = 0;
  double fbHeightTarget = 0;

  bool eMotionMagicActive = false;

  const int kPIDLoopIdx = 0;

  //Distances in inches
  
  //Elevator variables

    //Elevator ratios
      const float inchesPerRotationElevator = 2.635 * M_PI;
      const float ticksPerRotation = 4096;
    
    //Closed Loop variables
      const double liftPIDError = .01;
      const int kElevatorMotionSlotIdx = 0;
      const int kElevatorVelocitySlotIdx = 1;
      const int kElevatorPositionSlotIdx = 2;
      
      double mLiftkP = 4;
      double mLiftkI = 0;
      double mLiftkD = 0;
      double mLiftkF = .8;

      double dmLiftkP = 0;
      double dmLiftkI = 0;
      double dmLiftkD = 0;
      double dmLiftkF = 0;

      double vLiftkP = .25;
      double vLiftkI = 0.0;
      double vLiftkD = 0;
      double vLiftkF = 0.5;

      double pLiftkP = 0;
      double pLiftkI = 0;
      double pLiftkD = 0;
      double pLiftkF = 0;

      double liftCruiseVelocity = 1000;
      double liftAcceleration = 2000;

    const double maxLiftSpeed = 500;
    const double liftStartingHeight = 5.5;
    const float maxElevatorHeight =  32;
    const float minElevatorHeight = 0;
    const float maxElevatorTickHeight = maxElevatorHeight/inchesPerRotationElevator*ticksPerRotation;
    const float minElevatorTickHeight = 0;
    const float kFeedforwardElevator = 0.10;
    const float maxSlowDownHeight = 25;
    const float minSlowDownHeight = 10;
    const float slowDownConstant = 0.16;
    const double liftStartingTicks = liftStartingHeight/inchesPerRotationElevator*ticksPerRotation;


  //fourbar variables

    //inclinomter ratios
      const double voltsPerDegree = 0.01466667;
      const double ticksPerVolt = 310;
      const double startingInclinomterVolatage = 0.33;

    //Cloosed Loop variables
      const double fourBarPIDError = 5;
      const int kFourBarMotionSlotIdx = 0;
      const int kFourBarVelocitySlotIdx = 1;
      
      double motionMagicFourBarkP = 0;
      double motionMagicFourBarkI = 0;
      double motionMagicFourBarkD = 0;
      double motionMagicFourBarkF = 0;

      double upMMFourBarkP = 2;
      double upMMFourBarkI = 0.0;
      double upMMFourBarkD = 0;
      double upMMFourBarkF = 32;
      
      double downMMFourBarkP = 15;
      double downMMFourBarkI = 0;
      double downMMFourBarkD = 0;
      double downMMFourBarkF = 12;

      double vFourBarkP = 0;
      double vFourBarkI = 0;
      double vFourBarkD = 0;
      double vFourBarkF = 0;
      
      double fourBarCruiseVelocity = 60;
      double fourBarAcceleration = 60;

    double horizontalHoldingPercent = 0.15;
    double fbFeedForward = 0;
    const double maxFourBarVelocity = 100;
    const float distanceToFourBarRotation = 6;
    const float fourBarLength = 13;
    const float lengthOfImplement = 20;
    const double fourbarVoltageScale = 10.0;
    bool fbMotionMagicActive = false;


 public:

  Lift();
  void Periodic() override;
  void setElevatorHeight(double height);
  void setFourBarHeight(double height);
  void setLiftHeight(double height,double distance);
  bool atElevatorHeight();
  bool atFourBarHeight();
  void velocityElevatorControl(double speed);
  void setFourBarX(double x); 
  void setFourBarAngle(double angle);
  void constantHeightLift(float totalHeight, float fourBarXLength);
  void elevatorManualControl(double output);
  void velocityFourBarControl(double speed);
  void setLiftState(double height, double angle);
  void fourbarManualControl(double output);
  double getFourBarAngle();

};
