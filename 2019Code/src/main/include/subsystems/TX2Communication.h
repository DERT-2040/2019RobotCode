/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc/commands/Subsystem.h>
#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h> 
#include <string.h> 
#include <sys/types.h> 
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <netinet/in.h> 

#define PORT 2040
#define NUMOFVALUES 2

class TX2Communication : public frc::Subsystem 
{
 private:
  
  int sockfd;
  float buffer[NUMOFVALUES];
  struct sockaddr_in serveraddr, cliaddr;
  int recvlen;
  socklen_t cliaddrlen = sizeof(cliaddr);
 public:
  TX2Communication();
  void InitDefaultCommand() override;
  void Periodic() override;

};