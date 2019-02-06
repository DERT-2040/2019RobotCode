/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/SetLiftState.h"

SetLiftState::SetLiftState(int level) {
  if (Robot::m_intake.IsClosed() == true && level>1){//If it has the ball it will be closed
    level = level+3;//The level now stretches between 0 to 5 to signify whether the intake has a hatch or cargo
  }
  if (level==1){
    level = 2;
  }
  switch (level)
  {
    case 0://Ground Ball Pickup
      AddSequential(new SetLiftHeight(5,6),4);
    case 2://Hatch Low Goal (Rocket and Cargo Ship) and pickup
      AddSequential(new SetLiftHeight(5,6),4);//Replace with height and distance
    case 3://Hatch Medium Goal (Rocket)
      AddSequential(new SetLiftHeight(5,6),4);//Replace with height and distance
    case 4://Hatch Tall Goal (Rocket)
      AddSequential(new SetLiftHeight(5,6),4);//Replace with height and distance
    case 5:// Cargo Low Goal (Rocket)
      AddSequential(new SetLiftHeight(5,6),4);//Replace with height and distance
    case 6:// Cargo Medium Goal (Rocket and Cargo Ship)
      AddSequential(new SetLiftHeight(5,6),4);//Replace with height and distance
    case 7:// Cargo Tall Goal (Rocket)
      AddSequential(new SetLiftHeight(5,6),4);//Replace with height and distance
  }
}
