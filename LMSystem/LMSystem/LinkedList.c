
// File Encoding: UTF-8

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "com.rmdust.LinkedList.h"

static const char* FILENAME = "ArrayList.c";

extern struct LINKEDLIST* LinkedList() {
  struct LINKEDLIST* Source = malloc(sizeof(struct LINKEDLIST));

  if (Source == NULL) {
    return NULL;
  }

  memset(Source, 0, sizeof(struct LINKEDLIST));

  Source->Next = NULL;

  return Source;
}

extern struct CONTAINER Container() {
  struct CONTAINER Copy = {
      .Put = &Put,
      .Insert = &Insert,
      .PrintInfoAll = &PrintInfoAll,
      .IsExist = &IsExist,
      .IndexOf = &IndexOf,
      .GetByIndex = &GetByIndex,
  };

  return Copy;
}

static void Put(struct LINKEDLIST* Source, char Value[]) {
  while (Source->Next != NULL) {
    Source = Source->Next;
  }

  Source->Next = LinkedList();
  strcpy_s(Source->Value, 128, Value);
}

static void Insert(struct LINKEDLIST* Source, struct LINKEDLIST* New) {
  while (Source->Next != NULL) {
    Source = Source->Next;
  }

  Source->Next = New;
}

static void PrintInfoAll(struct LINKEDLIST* Source) {
  while (Source->Next != NULL) {
    printf("%s", Source->Value);
    Source = Source->Next;
  }

  printf("%s", Source->Value);
}

static bool IsExist(struct LINKEDLIST* Source, char* Str) {
  while (Source->Next != NULL) {
    if (strcmp(Source->Value, Str) == 0) {
      return true;
    }

    Source = Source->Next;
  }

  return false;
}

static int IndexOf(struct LINKEDLIST* Source, char* Value) {
  for (int Index = 0; Source->Next != NULL; Index++, Source = Source->Next) {
    if (strcmp(Source->Value, Value) == 0) {
      return Index;
    }
  }

  return -1;
}

static char* GetByIndex(struct LINKEDLIST* Source, int Index) {
  if (Index == -1) {
    return "";
  }

  for (size_t Count = 0; Source->Next != NULL; Count ++) {
    if (Index == Count) {
      return Source->Value; 
    }
    
    if (Index < Count) {
      return "";
    }

    Source = Source->Next;
  }

  
  return "";
}