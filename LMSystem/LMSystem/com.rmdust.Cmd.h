
// File Encoding: UTF-8

#pragma once

#include <windows.h>

#ifndef _INC_COM_RMDUST_CMD
#define _INC_COM_RMDUST_CMD

#define COLOR_BLACK 48
#define COLOR_BLUE 49
#define COLOR_GREEN 50
#define COLOR_AQUA 51
#define COLOR_RED 52
#define COLOR_PURPLE 53
#define COLOR_YELLO 54
#define COLOR_WHITE 55
#define COLOR_GRAY 56
#define COLOR_LIGHTBLUE 57
#define COLOR_LIGHTGREEN 65
#define COLOR_LIGHTAQUA 66
#define COLOR_LIGHTRED 67
#define COLOR_LIGHTPURPLE 68
#define COLOR_LIGHTYELLOW 69
#define COLOR_BRIGHTWHITE 70

struct CMD {
  void (*SetWindowColor)(int, int);
  void (*SetWindowSize)(int, int);
  void (*SetConsolePos)();
};

enum COLORINFO {
  Black = 48,
  Blue,
  Green,
  Aqua,
  Red,
  Purple,
  Yellow,
  White,
  Gray,
  LightBlue,
  LightGreen = 65,
  LightAqua,
  LightRed,
  LightPurple,
  LightYellow,
  BrightWhite
};

/// 初始化结构体
extern struct CMD Cmd();

static void SetWindowColor(int Background, int Frontground);
static void SetWindowSize(int Width, int Height);
static void SetConsolePos(SHORT X, SHORT Y);

#endif