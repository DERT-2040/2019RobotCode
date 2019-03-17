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

  pixel = 0;
  angle = 0;
  distance = 0;

}

void TX2Communication::InitDefaultCommand() 
{
  // Set the default command for a subsystem here.
  // SetDefaultCommand(new MySpecialCommand());
}

void TX2Communication::Periodic()
{
  
  recvlen = recvfrom(sockfd, buffer, sizeof(buffer), MSG_DONTWAIT, (struct sockaddr *)&cliaddr, &cliaddrlen);
  int index = 2;
  if(recvlen > 0)
  {
    printf("Client: %s\n", buffer);
    for(int i = 0; i < 3; i++)
    {
      std::string value = "";
      while(buffer[index] != ',')
      {
        value += buffer[index];
        index++;
      }
      char cstr[value.size() + 1];
      strcpy(cstr, value.c_str());
      values[i] = (float)atof(cstr);
      index+=3;
    }
    
    for(int i = 0; i < 3; i++)
    {
      std::cout << values[i] << " ";
    }
    std::cout << " " << std::endl;

    pixel = values[0];
    angle = values[1];
    distance = values[2];
  }
}

float TX2Communication::getPixel()
{
  return pixel;
}

float TX2Communication::getDistance()
{
  return distance;
}

float TX2Communication::getAngle()
{
  return angle;
}

