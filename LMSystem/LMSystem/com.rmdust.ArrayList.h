
// File Encoding: UTF-8

#pragma once

#include <stdbool.h>
#include <stdarg.h>
#include <windows.h>

#ifndef _INC_COM_RMDUST_ARRAYLIST
#define _INC_COM_RMDUST_ARRAYLIST

struct ARRAYLIST {
  char Value[128];
  struct ARRAYLIST* Next;
};

struct CONTAINER {
  void (*Put)(struct ARRAYLIST*, char[]);
  void (*Insert)(struct ARRAYLIST*, struct ARRAYLIST*);
  void (*PrintInfoAll)(struct ARRAYLIST*);
  bool (*IsExist)(struct ARRAYLIST*, char*);
};

extern struct ARRAYLIST* ArrayList();
extern struct CONTAINER Container();

static void Put(struct ARRAYLIST* Source, char Value[]);
static void Insert(struct ARRAYLIST* Source, struct ARRAYLIST* New);
static void PrintInfoAll(struct ARRAYLIST* Source);
static bool IsExist(struct ARRAYLIST* Source, char* Str);


#endif