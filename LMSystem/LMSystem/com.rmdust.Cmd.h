
// File Encoding: UTF-8

#pragma once

#include <windows.h>

#ifndef _INC_COM_RMDUST_CMD
#define _INC_COM_RMDUST_CMD


struct CMD {
  void (*SetWindowColor)();
  void (*SetWindowSize)(int, int);
  void (*SetConsolePos)();
};

/// 初始化结构体
extern struct CMD Cmd();


static void SetWindowColor();
static void SetWindowSize(int Width, int Height);
static void SetConsolePos(SHORT X, SHORT Y);

#endif