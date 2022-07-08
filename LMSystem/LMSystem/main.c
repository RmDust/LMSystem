
// File Encoding: UTF-8

#include <stdio.h>
#include <stdarg.h>

#include "com.rmdust.Account.h"
#include "com.rmdust.ArrayList.h"
#include "com.rmdust.Cmd.h"
#include "com.rmdust.Stream.h"


static const char* FILENAME = "main.c";


int main(void) {
  // 初始化窗口大小、颜色
  struct CMD Window = Cmd();
  Window.SetWindowColor(COLOR_BRIGHTWHITE, COLOR_BLACK);
  Window.SetWindowSize(120, 20);

  // 获取本地文件中已有的账户信息成用户列表
  // 将获取到的用户列表信息格式化，并放入AccountList中
  struct ARRAYLIST* AccountList = ArrayList();
  struct CONTAINER AccountListContainer = Container();
  struct STREAM AccountListStream = Stream();

  char List[128] = "";
  AccountListStream.ReadAllLine(List, "save/AccountList.txt");

  for (char Line[128] = "", Index = 0, Count = 0; Index < strlen(List);Index++) {
    if (List[Index] != '\n') {
      Line[(int)Count] = List[(int)Index];
      Count++;
    } else if (List[Index] == '\n') {
      AccountListContainer.Put(AccountList, Line);
      memset(Line, 0, sizeof(Line));
      Count = 0;
    }
    
  }

  // 控制台中显示登入提示和用户列表
  printf("Account :\nPassword:\n------------------\n%s------------------\n", List);

  // 初始化用户并接受键盘上的账户信息，分别是名称，密码
  struct ACCOUNT User = Account();
  Window.SetConsolePos(10, 0);
  User.SetName();
  Window.SetConsolePos(10, 1);
  User.SetPassword();

  // 判断输入的账户是否存在
  if (AccountListContainer.IsExist(AccountList, User.GetName())) {
    // 验证密码

  } else {
    // 尝试将新用户写入到用户文件中
    User.SignIn();

    // 创建密码
  }

  // 释放用户列表
  free(AccountList);

  return 0;
}