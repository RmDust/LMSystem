
// File Encoding: UTF-8

#include <direct.h>
#include <stdio.h>
#include <stdlib.h>

#include "com.rmdust.Stream.h"

extern struct STREAM Stream() {
  struct STREAM Copy = {
      .CreateFile = &CreateFileWW,
      .CreateFolder = &CreateFolder, 
  };

  return Copy;
}

static void CreateFileWW(char* FileName) {
  FILE* Path = NULL;
  fopen_s(&Path, FileName, "r");

  if (Path == NULL) {
    fopen_s(&Path, FileName, "a");
  }

  fclose(Path);
}

static void CreateFolder(char* FolderName) {
  if (_mkdir(FolderName)) {
  }
}

