
// File Encoding: UTF-8

#include <conio.h>
#include <direct.h>
#include <process.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <windows.h>

#include "com.rmdust.Console.h"

#define ERROR_COLOR_NOT_IN_RANGE "Color not in range"
#define ERROR_NUMS_IS_TOO_SMALL "The number is too small"
#define ERROR_NUMS_IS_TOO_BIG "The number is too big"

static const char* FILENAME = "Console.c";
static int WindowWidth;
static int WindowHeight;

extern struct CONSOLE Console() {
  struct CONSOLE Copy = {.SetWindowColor = &SetWindowColor,
                     .SetWindowSize = &SetWindowSize,
                     .SetConsolePos = &SetConsolePos};

  return Copy;
}

static void SetWindowColor(int Background, int Frontground) {
  if ((Background < 48 || Background > 57) &&
      (Background < 65 && Background > 70)) {
    printf("%s: %s :%c & %c", FILENAME, ERROR_COLOR_NOT_IN_RANGE,
           (char)Background, (char)Frontground);
    return;
  }

  char ColorCode[9];
  sprintf_s(ColorCode, 9, "%s%c%c", "color ", (char)Background,
            (char)Frontground);
  system(ColorCode);
}

static void SetWindowSize(int Width, int Height) {
  if (Width < 0 || Height < 0) {
    printf("%s: %s :%d & %d", FILENAME, ERROR_NUMS_IS_TOO_SMALL, Width, Height);
    return;
  }

  if (Width > 512 || Height > 362) {
    printf("%s: %s :%d & %d", FILENAME, ERROR_NUMS_IS_TOO_BIG, Width, Height);
    return;
  }

  WindowWidth = Width;
  WindowHeight = Height;

  char stCmd[32];
  sprintf_s(stCmd, 32, "mode con cols=%d lines=%d", Width, Height);
  system(stCmd);
}

static void SetConsolePos(SHORT X, SHORT Y) {

  if(X < 0 || Y < 0){
    printf("%s: %s :%d & %d", FILENAME, ERROR_NUMS_IS_TOO_SMALL, X, Y);
    return;
  }

  if (X > WindowWidth || Y > WindowHeight) {
    printf("%s: %s :%d & %d\nThe Window size:%d & %d", FILENAME,
           ERROR_NUMS_IS_TOO_BIG, X, Y, WindowWidth, WindowHeight);
    return;
  }

  COORD point;
  point.X = X;
  point.Y = Y;

  HANDLE HOutput = GetStdHandle(STD_OUTPUT_HANDLE);
  SetConsoleCursorPosition(HOutput, point);
}