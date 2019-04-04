/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/DeliverGamePiece.h"
#include "commands/WaitForButtonPress.h"
#include "commands/SetLiftHeight.h"
#include "commands/SliderLineTracker.h"
#include "commands/ResetSlider.h"
#include "commands/DeployGamePiece.h"

DeliverGamePiece::DeliverGamePiece(int level) {
  //AddSequential(new SetLiftState(level + 2,false));
  //AddSequential(new WaitForButtonPress(2,false));// CHANGE TO READY BUTTON POSITION
  //AddSequential(new SetLiftState(level + 1,true));
  //AddSequential(new SliderLineTracker());
  //AddSequential(new WaitForButtonPress(3,false));// CHANGE TO DEPLOY BUTTON POSITION
  //AddSequential(new DeployGamePiece());
  //AddSequential(new WaitForButtonPress(3,true));// CHANGE TO RESET BUTTON POSITION
  //AddParallel(new SetLiftState(2, false));
  //AddSequential(new ResetSlider());

  // Add Commands here:
  // e.g. AddSequential(new Command1());
  //      AddSequential(new Command2());
  // these will run in order.

  // To run multiple commands at the same time,
  // use AddParallel()
  // e.g. AddParallel(new Command1());
  //      AddSequential(new Command2());
  // Command1 and Command2 will run in parallel.

  // A command group will require all of the subsystems that each member
  // would require.
  // e.g. if Command1 requires chassis, and Command2 requires arm,
  // a CommandGroup containing them would require both the chassis and the
  // arm.
}
