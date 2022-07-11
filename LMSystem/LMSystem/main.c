
// File Encoding: UTF-8

#include <stdio.h>
#include <stdarg.h>

#include "com.rmdust.Account.h"
#include "com.rmdust.LinkedList.h"
#include "com.rmdust.Cmd.h"
#include "com.rmdust.Stream.h"

static const char* FILENAME = "main.c";

int main(void) {
  // 初始化窗口大小、颜色
  struct CMD Window = Cmd();
  Window.SetWindowColor(COLOR_BRIGHTWHITE, COLOR_BLACK);
  Window.SetWindowSize(120, 20);
  
  // 读取用户信息
  // 获取本地文件中已有的账户信息成用户列表
  struct LINKEDLIST* AccountList = LinkedList();
  struct LINKEDLIST* PasswordList = LinkedList();

  // 用于获取用户信息
  struct CONTAINER ListContainer = Container();
  struct STREAM ListStream = Stream();

  struct { 
    char Account[128];
    char Password[128];
  } List;
  memset(List.Account, 0, 128 * sizeof(char));
  memset(List.Password, 0, 128 * sizeof(char));

  ListStream.ReadAllLine(List.Account, "save/AccountList.txt");
  ListStream.ReadAllLine(List.Password, "save/PasswordList.txt");

  // 将获取到的用户列表信息格式化
  for (char Line[128] = "", Index = 0, Count = 0; Index < strlen(List.Account); Index++) {
    if (List.Account[Index] != '\n') {
      Line[(int)Count] = List.Account[(int)Index];
      Count++;
    } else if (List.Account[Index] == '\n') {
      ListContainer.Put(AccountList, Line);
      memset(Line, 0, sizeof(Line));
      Count = 0;
    }
  }
  for (char Line[128] = "", Index = 0, Count = 0; Index < strlen(List.Password); Index ++) {
    if (List.Password[Index] != '\n') {
      Line[(int)Count] = List.Password[(int)Index];
      Count++;
    } else if (List.Password[Index] == '\n') {
      ListContainer.Put(PasswordList, Line);
      memset(Line, 0, sizeof(Line));
      Count = 0;
    }
  }

  // 控制台中显示登入提示和用户列表
  printf("Account :\nPassword:\n------------------\n%s------------------\n%s", List.Account, List.Password);

  // 初始化用户并接受键盘上的账户信息，分别是名称，密码
  struct ACCOUNT User = Account();
  Window.SetConsolePos(10, 0);
  User.SetName();
  Window.SetConsolePos(10, 1);
  User.SetPassword();

  // 判断输入的账户是否存在
  if (ListContainer.IsExist(AccountList, User.GetName())) {
    // 得到用户名所在的行数，密码列表同行数的值与输入的密码相同则通过
    if (strcmp(ListContainer.GetByIndex(PasswordList, ListContainer.IndexOf(AccountList, User.GetName())), User.GetPassword()) == 0) {
      printf("Password pass.");
    } else {
      printf("Password error.");
    }
  } else {
    // 尝试将新用户写入到用户文件中
    User.SignIn();
  }
  // 释放用户列表
  free(AccountList);

  system("pause");




  return 0;
}

