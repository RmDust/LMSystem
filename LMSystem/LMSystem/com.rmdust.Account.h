
// File Encoding: UTF-8

#pragma once

#include <stdbool.h>


#ifndef _INC_COM_RMDUST_USER
#define _INC_COM_RMDUST_USER

struct ACCOUNT {
  bool (*SignIn)();
  bool (* IsExist)();
	void (* SetName)();
	char* (* GetName)();
	void (* SetPassword)();
	char* (* GetPassword)();
	void (* PrintInfoAll)();
};



/// 初始化结构体
extern struct ACCOUNT Account();


static bool SignIn();
static bool IsExist();
static void SetName();
static char* GetName();
static void SetPassword();
static char* GetPassword();

static void PrintInfoAll();

#endif