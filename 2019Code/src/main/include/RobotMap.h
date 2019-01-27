/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

/**
 * The RobotMap is a mapping from the ports sensors and actuators are wired into
 * to a variable name. This provides flexibility changing wiring, makes checking
 * the wiring easier and significantly reduces the number of magic numbers
 * floating around.
 */

// For example to map the left and right motors, you could define the
// following variables to use with your drivetrain subsystem.
// constexpr int kLeftMotor = 1;
// constexpr int kRightMotor = 2;

// If you are using multiple modules, make sure to define both the port
// number and the module. For example you with a rangefinder:
// constexpr int kRangeFinderPort = 1;
// constexpr int kRangeFinderModule = 1;

//Talons
    //DriveTrain
        constexpr int kFrontLeftMotorPort = 1;
        constexpr int kFrontRightMotorPort = 2;
        constexpr int kBackLeftMotorPort = 3;
        constexpr int kBackRightMotorPort = 4;
    //Intake
        constexpr int kRightIntakeWheel = 5;
        constexpr int kLeftIntakeWheel = 6;
    //Hatch Pickup
        constexpr int kHatchIntake = 7;
    //Slider
        constexpr int kSliderMotorPort = 8;


//Analog Inputs
constexpr int kLightSensorPort = 0;

//Digital Inputs
constexpr int kPickupUprightSwitch = 0;
constexpr int kPickupRetractedSwitch = 1;
constexpr int kPickupDeployedSwitch = 2;

//Pneumatics
constexpr int kForwardDriveSolenoid = 6;
constexpr int kReverseDriveSolenoid = 7;
constexpr int kForwardIntakeSolenoid = 1;
constexpr int kReverseIntakeSolenoid = 1;
constexpr int kCompressor = 0;

