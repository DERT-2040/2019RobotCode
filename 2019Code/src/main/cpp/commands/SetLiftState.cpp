/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/SetLiftState.h"
#include <iostream>

SetLiftState::SetLiftState(int level) {

  if (!Robot::m_intake.IsClosed() == true && level>2){//If it has the ball it will be closed
    //level = level+3;//The level now stretches between 3 to 8 to signify whether the intake has a hatch or cargo
    std::cout << 'cargo' << std::endl;
  }
  
  if (level==1){//Low goal for hatch is the same as hatch pickup
    level = 3;
  }

  switch (level)
  {
    case 0://Ground Ball Pickup
      AddSequential(new SetLiftHeight(5,4));//Replace with height and distance
    case 2://Starting State
      AddSequential(new SetLiftHeight(5,4));//Replace with height and distance
    case 3://Hatch Low Goal (Rocket and Cargo Ship)
      AddSequential(new SetLiftHeight(1.5,0));//Replace with height
    case 4://Hatch Medium Goal (Rocket)
      AddSequential(new SetLiftHeight(40.25,0));//Replace with height
    case 5://Hatch Tall Goal (Rocket)
      AddSequential(new SetLiftHeight(50,0));//Replace with height
    case 6:// Cargo Low Goal (Rocket)
      AddSequential(new SetLiftHeight(20.75,0));//Replace with height
    case 7:// Cargo Medium Goal (Rocket and Cargo Ship)
      AddSequential(new SetLiftHeight(48.75,0));//Replace with height
    case 8:// Cargo Tall Goal (Rocket)
      AddSequential(new SetLiftHeight(50,0));//Replace with height
  }
}
