
// File Encoding: UTF-8

#include <conio.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "com.rmdust.Account.h"
#include "com.rmdust.Console.Menu.h"
#include "com.rmdust.Console.h"
#include "com.rmdust.LinkedList.h"
#include "com.rmdust.Stream.h"

static const char* FILENAME = "main.c";

struct CONSOLE Window;
// 用于LinkList相关
static struct CONTAINER ListContainer;
// 用于文件读写
static struct STREAM File;

// 图书信息
struct LIBRARY {
  struct LINKEDLIST* Name;
  struct LINKEDLIST* Auth;
  struct LINKEDLIST* Pric;
  struct LINKEDLIST* Time;

  char AllLine[512];
} Book;

void ReadLibrary() { 
  File.ReadAllLine(Book.AllLine, "resources/Library.txt");

  char Line[128] = "";
  memset(Line, 0, 128 * sizeof(char));

  for (int Index = 0, Count = 0; Index < strlen(Book.AllLine); Index++) {
    if (Book.AllLine[Index] != '\n') {
      Line[Count] = Book.AllLine[Index];
      Count++;
    } else if (Book.AllLine[Index] == '\n') {
      char Name[128] = "", Auth[128] = "", Pric[128] = "", Time[128] = "";
      for (int i = 0, c = 0, v = 0; i < strlen(Line); i++) {
        if (Line[i] == ',') {
          c++;
          v = 0;
          continue;
        }

        if (c == 4) {
          break;
        }

        if (c == 0) {
          Name[v] = Line[i];
        } else if (c == 1) {
          Auth[v] = Line[i];
        } else if (c == 2) {
          Pric[v] = Line[i];
        } else if (c == 3) {
          Time[v] = Line[i];
        }
        v++;
      }

      ListContainer.Put(Book.Name, Name);
      ListContainer.Put(Book.Auth, Auth);
      ListContainer.Put(Book.Pric, Pric);
      ListContainer.Put(Book.Time, Time);

      memset(Line, 0, 128 * sizeof(char));
      Count = 0;
    }
  }
}
void WriteLibrary() {
  File.Clear("resources/Library.txt");
  
  for (int Index = 0; Index < ListContainer.Count(Book.Name); Index ++) {
    File.Write(ListContainer.GetByIndex(Book.Name, Index), "resources/Library.txt");
    File.Write(",", "resources/Library.txt");

    File.Write(ListContainer.GetByIndex(Book.Auth, Index), "resources/Library.txt");
    File.Write(",", "resources/Library.txt");

    File.Write(ListContainer.GetByIndex(Book.Pric, Index), "resources/Library.txt");
    File.Write(",", "resources/Library.txt");

    File.Write(ListContainer.GetByIndex(Book.Time, Index), "resources/Library.txt");
    File.Write(",\n", "resources/Library.txt");
  }
}

void InitLibrary() {
  memset(Book.AllLine, 0, 512 * sizeof(char));
  Book.Name = LinkedList();
  Book.Auth = LinkedList();
  Book.Pric = LinkedList();
  Book.Time = LinkedList();
}

void PutLibrary(struct LIBRARY Source) {
  ListContainer.Put(Book.Name, Source.Name->Value);
  ListContainer.Put(Book.Auth, Source.Auth->Value);
  ListContainer.Put(Book.Pric, Source.Pric->Value);
  ListContainer.Put(Book.Time, Source.Time->Value);
}

void DeleteLibrary(struct LIBRARY Source) {

  int Index = ListContainer.IndexOf(Book.Name, Source.Name->Value);

  if (Index == -1) {
    printf("Info may be inconsistent.");
    return;
  }

  if (strcmp(ListContainer.GetByIndex(Book.Auth, Index), Source.Auth->Value) !=
          0 ||
      strcmp(ListContainer.GetByIndex(Book.Pric, Index), Source.Pric->Value) !=
          0 ||
      strcmp(ListContainer.GetByIndex(Book.Time, Index), Source.Time->Value) !=
          0) {
    printf("Info may be inconsistent.");
    return;
  }

  ListContainer.Delete(Book.Name, Source.Name->Value);
  ListContainer.Delete(Book.Auth, Source.Auth->Value);
  ListContainer.Delete(Book.Pric, Source.Pric->Value);
  ListContainer.Delete(Book.Time, Source.Time->Value);
}

int TargetManagementMenu(int Value) {
  char Name[128] = "", Auth[128] = "", Pric[128] = "", Time[128] = "";

  // 初始化图书信息
  InitLibrary();
  ReadLibrary();

  struct LIBRARY NewBook;
  NewBook.Name = LinkedList();
  NewBook.Auth = LinkedList();
  NewBook.Pric = LinkedList();
  NewBook.Time = LinkedList();

  switch (Value) {
    case 0:
      rewind(stdin);
      printf("Create Name:");
      scanf_s("%127s", Name, (unsigned)_countof(Name));
      printf("Create Auth:");
      scanf_s("%127s", Auth, (unsigned)_countof(Auth));
      printf("Create Pric:");
      scanf_s("%127s", Pric, (unsigned)_countof(Pric));
      printf("Create Time:");
      scanf_s("%127s", Time, (unsigned)_countof(Time));

      ListContainer.Put(NewBook.Name, Name);
      ListContainer.Put(NewBook.Auth, Auth);
      ListContainer.Put(NewBook.Pric, Pric);
      ListContainer.Put(NewBook.Time, Time);

      PutLibrary(NewBook);
      WriteLibrary();

      free(NewBook.Name);
      free(NewBook.Auth);
      free(NewBook.Pric);
      free(NewBook.Time);
      break;
    case 1:
      
      rewind(stdin);
      printf("Create Name:");
      scanf_s("%127s", Name, (unsigned)_countof(Name));
      printf("Create Auth:");
      scanf_s("%127s", Auth, (unsigned)_countof(Auth));
      printf("Create Pric:");
      scanf_s("%127s", Pric, (unsigned)_countof(Pric));
      printf("Create Time:");
      scanf_s("%127s", Time, (unsigned)_countof(Time));

      ListContainer.Put(NewBook.Name, Name);
      ListContainer.Put(NewBook.Auth, Auth);
      ListContainer.Put(NewBook.Pric, Pric);
      ListContainer.Put(NewBook.Time, Time);

      DeleteLibrary(NewBook);
      system("pause");
      WriteLibrary();

      free(NewBook.Name);
      free(NewBook.Auth);
      free(NewBook.Pric);
      free(NewBook.Time);
      
      break;
    case 2:
      free(NewBook.Name);
      free(NewBook.Auth);
      free(NewBook.Pric);
      free(NewBook.Time);

      return 0;
  }

  free(Book.Name);
  free(Book.Auth);
  free(Book.Pric);
  free(Book.Time);

  return 1;
}

int ManagementMenu(void) {
  // 创建次级菜单
  struct MENU MainMenu = Menu();
  struct LINKEDLIST* MainMenuList = LinkedList();

  ListContainer.Put(MainMenuList, "Create a new book\n");
  ListContainer.Put(MainMenuList, "Delete a book\n");
  ListContainer.Put(MainMenuList, "Back\n");

  MainMenu.SetCount((int)ListContainer.Count(MainMenuList));

  // 1.输出菜单  2.等待输入并根据键入反应
  while (true) {
    

    system("cls");

    for (int Index = 0; Index < ListContainer.Count(MainMenuList); Index++) {
      printf("%s%s", *MainMenu.Index == Index ? " -->" : "    ", ListContainer.GetByIndex(MainMenuList, Index));
    }

    switch (_getch()) {
      case 'w': case 'W':
        MainMenu.SetIndex(--*MainMenu.Index);
        break;
      case 's': case 'S':
        MainMenu.SetIndex(++*MainMenu.Index);
        break;
      case ' ':
        if (TargetManagementMenu(*MainMenu.Index) == 0) {
          return 0;
        }
        break;
    }
  }
}

int TargetMainMenu(int Value) {
  switch (Value) {
    case 0:
      
      system("pause");
      return 1;
    case 1:
      ManagementMenu();
      return 1;
    case 2:
      return 0;
  }

  return 1;
}

void MainMenu() {
  struct MENU MainMenu = Menu();
  struct LINKEDLIST* MainMenuList = LinkedList();

  ListContainer.Put(MainMenuList, "Library\n");
  ListContainer.Put(MainMenuList, "ManagementMenu\n");
  ListContainer.Put(MainMenuList, "Exit\n");

  MainMenu.SetCount((int)ListContainer.Count(MainMenuList));

  // 1.输出菜单  2.等待输入并根据键入反应
  while (true) {
    system("cls");

    for (int Index = 0; Index < ListContainer.Count(MainMenuList); Index++) {
      printf("%s%s", *MainMenu.Index == Index ? " -->" : "    ", ListContainer.GetByIndex(MainMenuList, Index));
    }

    switch (_getch()) {
      case 'w':
      case 'W':
        MainMenu.SetIndex(--*MainMenu.Index);
        break;
      case 's':
      case 'S':
        MainMenu.SetIndex(++*MainMenu.Index);
        break;
      case ' ':
        // 按下空格后执行菜单对应的行为
        if (TargetMainMenu(*MainMenu.Index) == 0) {
          free(MainMenuList);
          return;
        }
        break;
    }
  }
}

int main(void) {
  
  
  Window = Console();
  ListContainer = Container();
  File = Stream();
  
  // 初始化窗口大小、颜色
  Window.SetWindowColor(COLOR_BRIGHTWHITE, COLOR_BLACK);
  Window.SetWindowSize(120, 20);

  
/*
  // 读取用户信息
  // 获取本地文件中已有的账户信息成用户列表
  struct LINKEDLIST* AccountList = LinkedList();
  struct LINKEDLIST* PasswordList = LinkedList();

  // 用于获取用户信息
  struct {
    char Account[128];
    char Password[128];
  } List;
  memset(List.Account, 0, 128 * sizeof(char));
  memset(List.Password, 0, 128 * sizeof(char));

  File.ReadAllLine(List.Account, "save/AccountList.txt");
  File.ReadAllLine(List.Password, "save/PasswordList.txt");
  
  // 用户列表信息格式化
  for (char Line[128] = "", Index = 0, Count = 0; Index < strlen(List.Account);
       Index++) {
    if (List.Account[Index] != '\n') {
      Line[(int)Count] = List.Account[(int)Index];
      Count++;
    } else if (List.Account[Index] == '\n') {
      ListContainer.Put(AccountList, Line);
      memset(Line, 0, 128 * sizeof(char));
      Count = 0;
    }
  }
  for (char Line[128] = "", Index = 0, Count = 0; Index < strlen(List.Password);
       Index++) {
    if (List.Password[Index] != '\n') {
      Line[(int)Count] = List.Password[(int)Index];
      Count++;
    } else if (List.Password[Index] == '\n') {
      ListContainer.Put(PasswordList, Line);
      memset(Line, 0, 128 * sizeof(char));
      Count = 0;
    }
  }

  // 控制台中显示登入提示和用户列表
  printf("Account :\nPassword:\n------------------\n%s------------------\n%s",
         List.Account, List.Password);
  
  // 初始化用户并接受键盘上的账户信息，分别是名称，密码
  struct ACCOUNT User = Account();
  Window.SetConsolePos(10, 0);
  User.SetName();
  fflush(stdin);
  Window.SetConsolePos(10, 1);
  User.SetPassword();
  fflush(stdin);

  // 判断输入的账户是否存在
  if (ListContainer.IsExist(AccountList, User.GetName())) {
    // 得到用户名所在的行数，密码列表同行数的值与输入的密码相同则通过
    if (strcmp(ListContainer.GetByIndex(
                   PasswordList,
                   ListContainer.IndexOf(AccountList, User.GetName())),
               User.GetPassword()) == 0) {
      printf("Password pass.");
    } else {
      printf("Password error.");
    }
  } else {
    // 尝试将新用户写入到用户文件中
    User.SignIn();
  }
  // 释放列表
  free(AccountList);
  free(PasswordList);

  system("pause");
  */
  // 创建主菜单
  MainMenu();

  return 0;
}
