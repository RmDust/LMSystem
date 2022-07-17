
// File Encoding: UTF-8

#pragma once

#include <windows.h>

#ifndef _INC_COM_RMDUST_CONSOLE_MENU
#define _INC_COM_RMDUST_CONSOLE_MENU

struct MENU {
  int* Index;
  int* Count;
  void (*SetIndex)(int);
  void (*SetCount)(int);
};

extern struct MENU Menu();
void SetIndex(int Value);
void SetCount(int Value);


#endif