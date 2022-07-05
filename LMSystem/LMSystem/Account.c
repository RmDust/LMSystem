
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
  // 尝试打开文件
  FILE* Path = NULL;
  fopen_s(&Path, "save/AccountList.txt", "a+");

  // 若文件夹不存在
  if (Path == NULL) {
    if (_mkdir("save")) {
    }
    fopen_s(&Path, "save/AccountList.txt", "a+");
  }
  // 写入账户信息
  fprintf_s(Path, "%s\n", Name);

  fclose(Path);

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