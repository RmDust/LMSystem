
// File Encoding: UTF-8

#include <conio.h>
#include <errno.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <direct.h>
#include <string.h>
#include <windows.h>

#include "com.rmdust.Account.h"
#include "com.rmdust.Stream.h"


static const char* FILENAME = "Account.c";

static char Name[128];
static char Password[128];

extern struct ACCOUNT Account() {
  struct ACCOUNT Copy = {
    .SignIn = &SignIn,
    .IsExist = &IsExist,
    .SetName = &SetName,
    .GetName = &GetName,
    .SetPassword = &SetPassword,
    .GetPassword = &GetPassword,
    .PrintInfoAll = &PrintInfoAll,
  };

  return Copy;
}

//extern struct ACCOUNTLIST AccountList() {
//}


static bool SignIn() {
  FILE* Path = NULL;
  
  errno_t Error = fopen_s(&Path, "save/AccountList.txt", "a+,ccs=UTF-8");
  if (Error != 0) {
    if (_mkdir("save")) {
    }
    return -1;
  }

  if(Path){
    Error = fprintf_s(Path, "%s\n", Name);
    if (Error != 0) {
      return -1;
    }
  }

  if(Path){
    Error = fclose(Path);
    if (Error == 0) {
      return -1;
    }
  }
  return true;
}

static bool IsExist() { return true; }

static void SetName() {
  char ch;

  for (int Index = 0; Index < 128; Index += 1) {
    ch = (char)getchar();

    if (ch == '\n') {
      break;
    }

    Name[Index] = ch;
  }
}

static char* GetName() { return Name; }

static void SetPassword() {
  char ch;

  for (int Index = 0; Index < 128; Index += 1) {
    ch = (char)getchar();

    if (ch == '\n') {
      break;
    }

    Password[Index] = ch;
  }
}

static char* GetPassword() { return Password; }

static void PrintInfoAll() {
  printf(
      "from user.c and com.rmdust.LMSystem.User.h\n\
		\tAccount\n\
		\t\tName:%s\n\
		\t\tPassword:%s",
      Name, Password);
}