/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc/TimedRobot.h>
#include <frc/commands/Command.h>
#include <frc/smartdashboard/SendableChooser.h>

#include "OI.h"
#include "subsystems/DriveTrain.h"
#include "subsystems/ArduinoCommunications.h"
#include "subsystems/ModeChooser.h"
#include "subsystems/HatchPickup.h"
#include "subsystems/Intake.h"
#include "subsystems/Lift.h"
#include "subsystems/Slider.h"
class Robot : public frc::TimedRobot {
 public:
  static OI m_oi;
  static DriveTrain m_driveTrain;
  static ModeChooser m_modeChooser;
  static ArduinoCommunications m_arduinoCommunications;
  static Intake m_intake;
  static Lift m_lift;
  static Slider m_slider;
  static HatchPickup m_hatchPickup;

  cs::UsbCamera camera1;
  cs::UsbCamera camera2;
  cs::VideoSink server;
  cs::CvSink * cvsink1;
  cs::CvSink * cvsink2;
  void RobotInit() override;
  void RobotPeriodic() override;
  void DisabledInit() override;
  void DisabledPeriodic() override;
  void AutonomousInit() override;
  void AutonomousPeriodic() override;
  void TeleopInit() override;
  void TeleopPeriodic() override;
  void TestPeriodic() override;

 private:
  // Have it null by default so that if testing teleop it
  // doesn't have undefined behavior and potentially crash.
  frc::Command* m_autonomousCommand = nullptr;
  frc::SendableChooser<frc::Command*> m_chooser;
};
