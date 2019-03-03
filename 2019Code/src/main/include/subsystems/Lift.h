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
  Faults * elevatorFaults = new Faults();
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
      
      double mLiftkP = .5;
      double mLiftkI = 0;
      double mLiftkD = 50;
      double mLiftkF = 0;

      double vLiftkP = .5;
      double vLiftkI = 0.0015;
      double vLiftkD = 0;
      double vLiftkF = 0;

      double pLiftkP = 0;
      double pLiftkI = 0;
      double pLiftkD = 0;
      double pLiftkF = 0;

      double liftCruiseVelocity = 2500;
      double liftAcceleration = 1100;

    const double maxLiftSpeed = 2000;
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
      const double fourBarPIDError = 1;
      const int kFourBarMotionSlotIdx = 0;
      const int kFourBarVelocitySlotIdx = 1;
      double mFourBarkP = .5;
      double mFourBarkI = 0;
      double mFourBarkD = 0;
      double mFourBarkF = 0;
      double vFourBarkP = 15;
      double vFourBarkI = 0;
      double vFourBarkD = 0;
      double vFourBarkF = 15;
      double fourBarCruiseVelocity = 100;
      double fourBarAcceleration = 50;

    const double maxFourBarVelocity = 100;
    const float distanceToFourBarRotation = 6;
    const float fourBarLength = 13;
    const float lengthOfImplement = 20;


  float calculateAggregateSpeedCapLift();
  float calculateAggregateSpeedCapFourBar();
  float calculateCombinedSpeedCap();
  float calculateFourBarSpeedCap();
  float calculateElevatorSpeedCap();

  float elevatorMultiplier = 1;
  const float slowdownDistanceIn = 20;
  const float slowdownDistanceOut=  60;
  const float minDistIn = 0;
  const float minDistOut = -10;
  const float slowDownAngle = 50; 
  const float limitAngle = 73;
  const float slowDownBottomElevator = 7;
  const float slowDownTopElevator = 40;
  const float limitBottomElevator = 0;
  const float limitTopElevator = 64;
 public:

  Lift();
  void Periodic() override;
  void InitDefaultCommand() override;
  void setElevatorHeight(double height);
  void setFourBarHeight(double height);
  void setLiftHeight(double height,double distance);
  bool atElevatorHeight();
  bool atFourBarHeight();
  float getFourBarDistance(); //Without Implement
  float getTotalHeight();
  float getElevatorHeight();

  void velocityElevatorControl(double speed);
  void setFourBarX(double x); 
  void setFourBarAngle(double angle);
  void constantHeightLift(float totalHeight, float fourBarXLength);
  void elevatorManualControl(double output);
  void velocityFourBarControl(double speed);
  void fourbarManualControl(double output);
  double getFourBarAngle();

};
