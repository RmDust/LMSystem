
// File Encoding: UTF-8

#pragma once

#include <stdbool.h>

#ifndef _INC_COM_RMDUST_STREAM
#define _INC_COM_RMDUST_STREAM

struct STREAM {
  void (* CreateFile)();
  void (* CreateFolder)();
};

/// 初始化结构体
extern struct STREAM Stream();

static void CreateFileWW(char* FileName);
static void CreateFolder(char* FolderName);


#endif
