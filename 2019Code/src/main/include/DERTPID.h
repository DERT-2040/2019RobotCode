/*----------------------------------------------------------------------------*/
/* Copyright (c) 2018 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once
#include "frc/WPILib.h"

class DERTPID 
{

  private:

    float kP, kI, kD;
    float error;
    float setPoint;
    float currentValue;
    float output;
    float integral;
    float derivative;
    float previousError;
    float * input;
    float previousTime;
    float currentTime;
    float timeDelta;
    float tolerance;

    bool finished;

    frc::Timer timer;

    frc::SpeedController * controller;

  public:

    DERTPID(float _kP, float _kI, float _kD, float * _input, frc::SpeedController * _speedController);
    void setSetPoint(float _setPoint);
    void runPID();
    bool isOutputPositive();
    void setAcceptableTolerance(float _tolerance);
    bool isFinished();

    

};
