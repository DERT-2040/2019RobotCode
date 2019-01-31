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
  masterRightMotor->Config_kP(kSlotIdx, kP, 30);
  masterRightMotor->Config_kI(kSlotIdx, kI, 30);
  masterRightMotor->Config_kD(kSlotIdx, kD, 30);
  masterRightMotor->Config_kF(kSlotIdx, kF, 30);

  masterLeftMotor->Config_kP(kSlotIdx, kP, 30);
  masterLeftMotor->Config_kI(kSlotIdx, kI, 30);
  masterLeftMotor->Config_kD(kSlotIdx, kD, 30);
  masterLeftMotor->Config_kF(kSlotIdx, kF, 30);

  masterLeftMotor->ConfigMotionCruiseVelocity(cruiseVelocity);
  masterLeftMotor->ConfigMotionAcceleration(acceleration);
  masterLeftMotor->ConfigAllowableClosedloopError(kSlotIdx, .50, 30);

  masterRightMotor->ConfigMotionCruiseVelocity(cruiseVelocity);
  masterRightMotor->ConfigMotionAcceleration(acceleration);
  masterRightMotor->ConfigAllowableClosedloopError(kSlotIdx, .50, 30);

  masterLeftMotor->ConfigSelectedFeedbackSensor(CTRE_MagEncoder_Relative, kPIDSlotIdx, 30);
  masterLeftMotor->SetSelectedSensorPosition(0, kPIDSlotIdx, 30);

  masterRightMotor->ConfigSelectedFeedbackSensor(CTRE_MagEncoder_Relative, kPIDSlotIdx, 30);
  masterRightMotor->SetSelectedSensorPosition(0, kPIDSlotIdx, 30);

  secondLeftMotor = new WPI_TalonSRX(kSecondLeftMotorPort);
  secondRightMotor = new WPI_TalonSRX(kSecondRightMotorPort);
  masterLeftMotor = new WPI_TalonSRX(kMasterLeftMotorPort);
  masterRightMotor = new WPI_TalonSRX(kMasterRightMotorPort);

  secondLeftMotor->SetInverted(true);

  secondLeftMotor->Follow(*masterLeftMotor);
  secondRightMotor->Follow(*masterRightMotor);

  /*
  leftSide = new frc::SpeedControllerGroup(*secondLeftMotor, *masterLeftMotor);
  rightSide = new frc::SpeedControllerGroup(*secondRightMotor, *masterRightMotor);
  leftSide -> SetInverted(true);
  rightSide -> SetInverted(true);
  */

  masterLeftMotor->SetInverted(true);
  masterRightMotor->SetInverted(true);

  //drive = new  frc::DifferentialDrive(*leftSide, *rightSide);
  drive = new frc::DifferentialDrive(*masterLeftMotor, *masterRightMotor);

  compressor = new frc::Compressor(kCompressor);

	compressor->SetClosedLoopControl(true);
  driveSolenoid = new frc::DoubleSolenoid(kForwardDriveSolenoid,kReverseDriveSolenoid);

}

void DriveTrain::InitDefaultCommand() {
  // Set the default command for a subsystem here.
  // SetDefaultCommand(new MySpecialCommand());
  //SetDefaultCommand(new DriveWithJoySticks);
  //std::cout << "started" << std::endl;
  masterLeftMotor->GetSensorCollection().SetQuadraturePosition(0);
  masterRightMotor->GetSensorCollection().SetQuadraturePosition(0);
}

void DriveTrain::Periodic()
{
  //std::cout << lightSensor->GetVoltage() << std::endl;
  std::cout << masterLeftMotor->GetSensorCollection().GetQuadraturePosition() << std::endl;
  std::cout << masterRightMotor->GetSensorCollection().GetQuadraturePosition() << std::endl;
  std::cout << "" << std::endl;
}

void DriveTrain::CurveDrive()
{
  drive->CurvatureDrive(-1*Robot::m_oi.gamepad->GetRawAxis(5),Robot::m_oi.gamepad->GetRawAxis(0)*.45, true);
}

void DriveTrain::DriveSpeed(float speed)
{
  drive->CurvatureDrive(0.5,0,false);
}

void DriveTrain::ShiftGear(int _gear)
{
  if (gear != _gear){
    gear = _gear;
    if(gear == 1){
      driveSolenoid->Set(frc::DoubleSolenoid::Value::kForward);
    }
    else if (gear == 0){
      driveSolenoid->Set(frc::DoubleSolenoid::Value::kReverse);
    }
  }
}

void DriveTrain::driveFeet(float feet)
{

}


