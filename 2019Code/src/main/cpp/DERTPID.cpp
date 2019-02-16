/*----------------------------------------------------------------------------*/
/* Copyright (c) 2018 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "DERTPID.h"

DERTPID::DERTPID(float _kP, float _kI, float _kD, float * _input, frc::SpeedController * _speedController) 
{
    controller = _speedController;
    kP = _kP;
    kI = _kI;
    kD = _kD;
    input = _input;
    integral = 0;
    derivative = 0;
    timeDelta = 0;
    finished = true;
}

void DERTPID::setSetPoint(float _setPoint)
{
    setPoint = _setPoint;
    integral = 0;
    derivative = 0;
}

void DERTPID::runPID()
{
    error = setPoint - *input;

    if(abs(error) < tolerance)
    {
        currentTime = timer.GetFPGATimestamp();

        timeDelta = currentTime - previousTime;
        integral += error*timeDelta;
        derivative = (error - previousError) / timeDelta;
        output = kP*error + kI*integral + kD * derivative;
        previousError = error;
        previousTime = currentTime;

        controller->Set(output);
        finished = false;
    }
    else
    {
        finished = true;
    }
}

bool DERTPID::isOutputPositive()
{
    if(output > 0)
    {
        return true;
    }
    else{ return false; }
}

void DERTPID::setAcceptableTolerance(float _tolerance)
{
    tolerance = _tolerance;
}

bool DERTPID::isFinished()
{
    return finished;
}