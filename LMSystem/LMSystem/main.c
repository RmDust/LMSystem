
// File Encoding: UTF-8

#include <stdio.h>

#include "com.rmdust.Cmd.h"
#include "com.rmdust.Account.h"
#include "com.rmdust.Stream.h"
#include "com.rmdust.ArrayList.h"


int main(void) {


  // 初始化窗口大小、颜色
  struct CMD Window = Cmd();
  Window.SetWindowColor();
  Window.SetWindowSize(20, 60);




  // 控制台中显示登入提示
  printf("Account :\nPassword:\n");
  



  // 获取本地文件中已有的账户信息成用户列表
  struct ARRAYLIST* AccountList = ArrayList();
  struct CONTAINER AccountListContainer = Container();

  FILE* AccountListFile = NULL;
  fopen_s(&AccountListFile, "save/AccountList.txt", "r+");
  
  if (AccountListFile == NULL) {
    return -1;
  }

  char Text[128] = "", ch = (char)fgetc(AccountListFile);
  // 此处读取文件时省去了回车符
  for (size_t Index = 0; ch != EOF; Index++, ch = (char)fgetc(AccountListFile)) {
    if (ch == '\n') {
      Text[Index] = '\0';
      Index = 0;
      AccountListContainer.Put(AccountList, Text);
      memset(Text, 0, sizeof(Text));
      ch = (char)fgetc(AccountListFile);
    }

    Text[Index] = ch;
  }

  fclose(AccountListFile);


  // 显示用户列表
  printf("------------------\n");
  AccountListContainer.PrintInfoAll(AccountList);
  printf("\n------------------\n\n");

  



  // 初始化用户并接受键盘上的账户信息
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