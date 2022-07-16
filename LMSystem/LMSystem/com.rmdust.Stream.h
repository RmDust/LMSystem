
// File Encoding: UTF-8

#pragma once

#include <stdbool.h>

#ifndef _INC_COM_RMDUST_STREAM
#define _INC_COM_RMDUST_STREAM

struct STREAM {
  void (*CreateFile)(char*);
  void (*CreateFolder)(char*);
  char* (*ReadAllLine)(char*, char*);
  void (*Write)(char*, char*);
  void (*WriteLine)(char*, char*);
  void (*Clear)(char*);
};

/// 初始化结构体
extern struct STREAM Stream();

static void CreateFileWW(char* FileName);
static void CreateFolder(char* FolderName);
static char* ReadAllLine(char* refSource, char* FileName);
static void Write(char* Source, char* FileName);
static void WriteLine(char* Source, char* FileName);
static void Clear(char* FileName);

#endif
