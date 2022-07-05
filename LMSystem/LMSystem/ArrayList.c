
// File Encoding: UTF-8

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "com.rmdust.ArrayList.h"

extern struct ARRAYLIST* ArrayList() {
  struct ARRAYLIST* Source = malloc(sizeof(struct ARRAYLIST));

  if (Source == NULL) {
    return NULL;
  }

  memset(Source, 0, sizeof(struct ARRAYLIST));

  Source->Next = NULL;

  return Source;
}

extern struct CONTAINER Container() { 
  struct CONTAINER Copy = {
    .Put = &Put,
    .Insert = &Insert, 
    .PrintInfoAll = &PrintInfoAll, 
    .IsExist = &IsExist,
  }; 

  return Copy;
}

static void Put(struct ARRAYLIST* Source, char Value[]) {
  while (Source->Next != NULL) {
    Source = Source->Next;
  }

  Source->Next = ArrayList();
  strcpy_s(Source->Value, 128, Value);
}

static void Insert(struct ARRAYLIST* Source, struct ARRAYLIST* New) {
  while (Source->Next != NULL) {
    Source = Source->Next;
  }

  Source->Next = New;
}

static void PrintInfoAll(struct ARRAYLIST* Source) {
  while (Source->Next != NULL) {
    printf("%s\n", Source->Value);
    Source = Source->Next;
  }

  printf("%s", Source->Value);
}




static bool IsExist(struct ARRAYLIST* Source, char* Str) {
  while (Source->Next != NULL) {
    if (strcmp(Source->Value, Str) == 0) {      
      return true;
    }

    Source = Source->Next;
  }

  return false;
}