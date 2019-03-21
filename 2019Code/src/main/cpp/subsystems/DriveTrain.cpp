/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/DriveTrain.h"
#include "Robot.h"
#include "commands/DriveWithJoySticks.h"
#include <iostream>

DriveTrain::DriveTrain() : frc::Subsystem("DriveTrain")
{
  secondLeftMotor = new WPI_TalonSRX(kSecondLeftMotorPort);
  secondRightMotor = new WPI_TalonSRX(kSecondRightMotorPort);
  masterLeftMotor = new WPI_TalonSRX(kMasterLeftMotorPort);
  masterRightMotor = new WPI_TalonSRX(kMasterRightMotorPort);

  secondLeftMotor->ConfigPeakCurrentLimit(35);
  secondRightMotor->ConfigPeakCurrentLimit(35);
  masterLeftMotor->ConfigPeakCurrentLimit(35);
  masterRightMotor->ConfigPeakCurrentLimit(35);
  
  secondLeftMotor->EnableCurrentLimit(false);
  secondRightMotor->EnableCurrentLimit(false);
  masterLeftMotor->EnableCurrentLimit(false);
  masterRightMotor->EnableCurrentLimit(false);
  
  secondLeftMotor->ConfigOpenloopRamp(0.15);
  secondRightMotor->ConfigOpenloopRamp(0.15);
  masterLeftMotor->ConfigOpenloopRamp(0.15);
  masterRightMotor->ConfigOpenloopRamp(0.15);

  secondLeftMotor->SetNeutralMode(ctre::phoenix::motorcontrol::Coast);
  secondRightMotor->SetNeutralMode(ctre::phoenix::motorcontrol::Coast);
  masterLeftMotor->SetNeutralMode(ctre::phoenix::motorcontrol::Coast);
  masterRightMotor->SetNeutralMode(ctre::phoenix::motorcontrol::Coast);
  
  secondLeftMotor->Follow(*masterLeftMotor);
  secondRightMotor->Follow(*masterRightMotor);

  secondLeftMotor->SetInverted(false);
  secondRightMotor->SetInverted(true);


  leftSide = new frc::SpeedControllerGroup(*secondLeftMotor, *masterLeftMotor);
  rightSide = new frc::SpeedControllerGroup(*secondRightMotor, *masterRightMotor);

  leftSide -> SetInverted(true);
  rightSide -> SetInverted(false);
  
  //drive = new frc::DifferentialDrive(*leftSide, *rightSide);

  compressor = new frc::Compressor(kCompressor);

	compressor->SetClosedLoopControl(true);
  driveSolenoid = new frc::DoubleSolenoid(1,kForwardDriveSolenoid,kReverseDriveSolenoid);
  
  climbSolenoid = new frc::DoubleSolenoid(0,0,2);
  masterLeftMotor->GetSensorCollection().SetQuadraturePosition(0);
  masterRightMotor->GetSensorCollection().SetQuadraturePosition(0);

  masterLeftMotor->ConfigSelectedFeedbackSensor(FeedbackDevice::QuadEncoder, 0, 30);
  masterRightMotor->ConfigSelectedFeedbackSensor(FeedbackDevice::QuadEncoder, 0, 30);

  masterLeftMotor->ConfigClosedloopRamp(.15);
  masterRightMotor->ConfigClosedloopRamp(.15);

  masterLeftMotor->Config_kP(0, 0.002, 30);
  masterLeftMotor->Config_kI(0, 0, 30);
  masterLeftMotor->Config_kD(0, 0, 30);
  masterLeftMotor->Config_kF(0, 0.0786, 30);

  masterLeftMotor->SetSensorPhase(false);
  masterRightMotor->SetSensorPhase(true);

  masterRightMotor->Config_kP(0, 0.007, 30);
  masterRightMotor->Config_kI(0, 0, 30);
  masterRightMotor->Config_kD(0, 0, 30);
  masterRightMotor->Config_kF(0, 0.0786, 30);

}

void DriveTrain::InitDefaultCommand() 
{
  masterLeftMotor->GetSensorCollection().SetQuadraturePosition(0);
  masterRightMotor->GetSensorCollection().SetQuadraturePosition(0);
}

void DriveTrain::Periodic()
{
  std::cout << masterLeftMotor->GetSelectedSensorVelocity() << std::endl;
  std::cout << masterRightMotor->GetSelectedSensorVelocity() << std::endl;
}

void DriveTrain::CurveDrive()
{ 

  float forwardSpeed = Robot::m_oi.joystickR->GetRawAxis(1);
  //float forwardSpeedL = -1*Robot::m_oi.joystickL->GetRawAxis(1);
  float turnSpeed = Robot::m_oi.joystickL->GetRawAxis(0);
  forwardSpeed*= abs(-1*Robot::m_oi.joystickR->GetRawAxis(1));
  turnSpeed *= abs(Robot::m_oi.joystickL->GetRawAxis(0));
   turnSpeed *= abs(Robot::m_oi.joystickL->GetRawAxis(0));
  drive->CurvatureDrive(-1*forwardSpeed,turnSpeed+ 0.02,true);
  turnI = 0;
}

void DriveTrain::assistDrive()
{
  
  float forwardSpeed = Robot::m_oi.joystickR->GetRawAxis(1);
  forwardSpeed = forwardSpeed * fabs(forwardSpeed);
  
  float turnError = 0 - Robot::m_TX2Communication.getAngle();
  float turnD = (turnError - previousError)/.02;
  turnI += turnError*.02;
  float turnSpeed;
  if(Robot::m_TX2Communication.getDistance() > 50  )
  {
    turnSpeed = turnError*0.05*(65/Robot::m_TX2Communication.getDistance()) + turnD * 0 + turnI * 0.0001;
  }
  else
  {
    turnSpeed = turnError*0.095 + turnD * 0 + turnI * 0.0001;
  }


  if(fabs(turnSpeed) > 0.6)
  {
    turnSpeed = 0.6*turnSpeed/fabs(turnSpeed);
    //std::cout << "limited" << std::endl;
  }

  //std::cout << "TurnSpeed: " << turnSpeed << std::endl;
  previousError = turnError;

  velDrive(forwardSpeed, -turnSpeed);

}

void DriveTrain::DriveSpeed(float speed){
  //drive->CurvatureDrive(0.5,0,false);
}

void DriveTrain::ShiftGear(int _gear){
  //std::cout << "gear in: " << _gear << std::endl;
  //std::cout << "gear: " << gear << std::endl;
  if (gear != _gear){
    gear = _gear;
    if(gear == 1){
      driveSolenoid->Set(frc::DoubleSolenoid::Value::kReverse);
    }
    else if (gear == 0){
      driveSolenoid->Set(frc::DoubleSolenoid::Value::kForward);
    }
  }
}

void DriveTrain::Climb(int _state){
  if (state != _state){
    state = _state;
    if(state == 1){
      climbSolenoid->Set(frc::DoubleSolenoid::Value::kReverse);
    }
    else if (state == 0){
      climbSolenoid->Set(frc::DoubleSolenoid::Value::kForward);
    }
    else if (state == 2){
      climbSolenoid->Set(frc::DoubleSolenoid::Value::kOff);
    }
  }
}

void DriveTrain::velDrive(float _forwardValue, float _turnValue)
{
  
  float rightSpeed;
  float leftSpeed;

  float turnValue = -1*_turnValue;
  float forwardValue = _forwardValue;

  turnValue = pow(turnValue, 3);

  if(fabs(turnValue) < 0.025)
  {
    turnValue = 0;
  }

  if(fabs(forwardValue) < 0.025)
  {
    forwardValue = 0;
  }

  std::cout << "encoderR: " << masterRightMotor->GetSensorCollection().GetQuadraturePosition() << std::endl;
  std::cout << "encoderL: " << masterLeftMotor->GetSensorCollection().GetQuadraturePosition() << std::endl;

  if(gear == 0)
  {
    rightSpeed = forwardValue * lowRight - turnValue * maxTurnSpeed;
    leftSpeed = forwardValue * lowLeft + turnValue * maxTurnSpeed;
  }
  else if(gear == 1)
  {
    rightSpeed = forwardValue * highRight - turnValue * maxTurnSpeed;
    leftSpeed = forwardValue * highLeft - turnValue * maxTurnSpeed;
  }

  masterLeftMotor->SelectProfileSlot(0,0);
  masterRightMotor->SelectProfileSlot(0,0);

  if(fabs(turnValue) > 0 || fabs(forwardValue) > 0)
  {
    masterLeftMotor->Set(ControlMode::Velocity, leftSpeed);
    masterRightMotor->Set(ControlMode::Velocity, rightSpeed);
  }
  else
  {
    masterLeftMotor->Set(ControlMode::PercentOutput, 0);
    masterRightMotor->Set(ControlMode::PercentOutput, 0);
  }

}
