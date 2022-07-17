
// File Encoding: UTF-8

#include "com.rmdust.Console.Menu.h"

static int Index = 0;
static int Count = 0;

extern struct MENU Menu() {
  struct MENU Copy = {
      .Index = &Index,
      .Count = &Count,
      .SetIndex = &SetIndex, 
      .SetCount = &SetCount,
  };

  return Copy;
}

void SetIndex(int Value) {
  if (Value <= 0) {
    Index = 0;
    return;
  }
  if (Value >= Count) {
    Index = Count - 1;
    return;
  }

  Index = Value;
}

void SetCount(int Value) { 
  Count = Value;
}
