
// File Encoding: UTF-8

#pragma once

#include <stdbool.h>
#include <stdarg.h>
#include <windows.h>

#ifndef _INC_COM_RMDUST_LINKEDLIST
#define _INC_COM_RMDUST_LINKEDLIST

struct LINKEDLIST {
  char Value[128];
  struct LINKEDLIST* Next;
};

struct CONTAINER {
  void (*Put)(struct LINKEDLIST*, char[]);
  void (*Insert)(struct LINKEDLIST*, struct LINKEDLIST*);
  void (*PrintInfoAll)(struct LINKEDLIST*);
  bool (*IsExist)(struct LINKEDLIST*, char*);
  int (*IndexOf)(struct LINKEDLIST*, char*);
  char* (*GetByIndex)(struct LINKEDLIST*, int);
};

extern struct LINKEDLIST* LinkedList();
extern struct CONTAINER Container();

static void Put(struct LINKEDLIST* Source, char Value[]);
static void Insert(struct LINKEDLIST* Source, struct LINKEDLIST* New);
static void PrintInfoAll(struct LINKEDLIST* Source);
static bool IsExist(struct LINKEDLIST* Source, char* Str);
static int IndexOf(struct LINKEDLIST* Source, char* Value);
static char* GetByIndex(struct LINKEDLIST* Source, int Index);

#endif