
// File Encoding: UTF-8

#include <conio.h>
#include <direct.h>
#include <errno.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

#include "com.rmdust.Account.h"

#define ERROR_NOT_CREATE_IT "Not create such a file"
#define ERROR_NOT_FOUND_IT "Not found such a file"
#define ERROR_NOT_CLOSE_IT "Not close such a file"
#define ERROR_HAVE_IT_ALREADY "Already have such a file"
#define ERROR_NOT_WRITTEN_IN "Not written in such a file"

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

static bool SignIn() {
  FILE* Path = NULL;

  errno_t Error = fopen_s(&Path, "save/AccountList.txt", "a+,ccs=UTF-8");
  if (Error != 0) {
    printf("%s: %s :%s", FILENAME, ERROR_NOT_FOUND_IT, "save/AccountList.txt");
  }

  if (Path) {
    Error = fprintf_s(Path, "%s\n", Name);
    if (Error != 0) {
      printf("%s: %s :%s", FILENAME, ERROR_NOT_WRITTEN_IN, "save/AccountList.txt");
      return false;
    }
    Error = fclose(Path);
    if (Error != 0) {
      printf("%s: %s :%s", FILENAME, ERROR_NOT_CLOSE_IT, "save/AccountList.txt");
      return false;
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