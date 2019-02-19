/*!
  boldtemple Gaming ©, http://gaming.boldtemple.net
  OpenSource Project - Check Development, License & Readme Sections.

  BGE - boldtemple Cross Platform Game Engine
  /Core/sys.h
!*/

#ifndef SYS_H
#define	SYS_H

#include <string>
#include <stdio.h>

std::string int_to_str(int value);

inline
std::string int_to_str(int value){
    char buffer[21];
    sprintf(buffer, "%d", value);
    return std::string(buffer);
} 

#endif	/* SYS_H */

