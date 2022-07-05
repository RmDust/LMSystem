
// File Encoding: UTF-8

#include <conio.h>
#include <direct.h>
#include <process.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <windows.h>

#include "com.rmdust.Cmd.h"

extern struct CMD Cmd() {
  struct CMD Copy = {
    .SetWindowColor = &SetWindowColor,
    .SetWindowSize = &SetWindowSize,
    .SetConsolePos = &SetConsolePos
  };

  return Copy;
}

static void SetWindowColor() { system("color f4"); }

static void SetWindowSize(int Width, int Height) {
  char stCmd[32 + 1];

  sprintf_s(stCmd, 32, "mode con cols=%d lines=%d", Height, Width);

  system(stCmd);
}

static void SetConsolePos(SHORT X, SHORT Y) {
  COORD point;
  point.X = X;
  point.Y = Y;

  HANDLE HOutput = GetStdHandle(STD_OUTPUT_HANDLE);
  SetConsoleCursorPosition(HOutput, point);
}