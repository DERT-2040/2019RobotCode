/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/PlacePiece.h"

PlacePiece::PlacePiece(int level) {
  if (Robot::m_intake.IsClosed() == true){//If it has the ball it will be closed
    level = level+3;//The level now stretches between 0 to 5 to signify whether the intake has a hatch or cargo
  }
  switch (level)
  {
    case 0://Hatch Low Goal (Rocket and Cargo Ship)
      AddParallel(new SetElevatorHeight(5));//Replace with height
    case 1://Hatch Medium Goal (Rocket)
      AddParallel(new SetElevatorHeight(5));//Replace with height
    case 2://Hatch Tall Goal (Rocket)
      AddParallel(new SetElevatorHeight(5));//Replace with height
    case 3:// Cargo Low Goal (Rocket)
      AddParallel(new SetElevatorHeight(5));//Replace with height
    case 4:// Cargo Medium Goal (Rocket and Cargo Ship)
      AddParallel(new SetElevatorHeight(5));//Replace with height
    case 5:// Cargo Tall Goal (Rocket)
      AddParallel(new SetElevatorHeight(5));//Replace with height
  }
}
