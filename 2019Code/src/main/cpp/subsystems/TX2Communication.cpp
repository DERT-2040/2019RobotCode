/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/TX2Communication.h"
#include <iostream>
using namespace std;

TX2Communication::TX2Communication() : Subsystem("TX2Communication") 
{
  if((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
  {
    cout << "could not create socket" << endl;
  }

  serveraddr.sin_family = AF_INET;
  serveraddr.sin_addr.s_addr = INADDR_ANY;
  serveraddr.sin_port = htons(PORT);

  if(bind(sockfd, (const struct sockaddr *)&serveraddr, sizeof(serveraddr)) < 0)
  {
    cout << "failed to bind to port" << endl;
  }


}

void TX2Communication::InitDefaultCommand() 
{
  // Set the default command for a subsystem here.
  // SetDefaultCommand(new MySpecialCommand());
}

void TX2Communication::Periodic()
{
  recvlen = recvfrom(sockfd, buffer, sizeof(buffer), MSG_DONTWAIT, (struct sockaddr *)&cliaddr, &cliaddrlen);
  cout << buffer[0] << endl;
}

