
// File Encoding: UTF-8

#include <direct.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "com.rmdust.Stream.h"

#define ERROR_NOT_CREATE_IT "Not create such a file"
#define ERROR_NOT_FOUND_IT "Not found such a file"
#define ERROR_NOT_CLOSE_IT "Not close such a file"
#define ERROR_HAVE_IT_ALREADY "Already have such a file"


static const char* FILENAME = "Stream.c"; 


extern struct STREAM Stream() {
  struct STREAM Copy = {
      .CreateFile = &CreateFileWW,
      .CreateFolder = &CreateFolder, 
      .ReadAllLine = &ReadAllLine,
  };

  return Copy;
}

static void CreateFileWW(char* FileName) {
  FILE* Path = NULL;
  
  errno_t Error = fopen_s(&Path, FileName, "r");
  if (Error != 0) {
    printf("%s: %s :%s, but the program tries to create", FILENAME, ERROR_NOT_FOUND_IT, FileName);

    Error = fopen_s(&Path, FileName, "a");
    if (Error != 0) {
      printf("%s: %s :%s", FILENAME, ERROR_NOT_CREATE_IT, FileName);
      return;
    }
  } else {
    printf("%s: %s :%s", FILENAME, ERROR_HAVE_IT_ALREADY, FileName);
  }

  if(Path){
    Error = fclose(Path);
    if (Error != 0) {
      printf("%s: %s :%s", FILENAME, ERROR_NOT_CLOSE_IT, FileName);
      return;
    }
  }
}

static void CreateFolder(char* FolderName) {
  if (_mkdir(FolderName) != 0) {
    printf("%s: %s :%s", FILENAME, ERROR_NOT_CREATE_IT, FolderName);
  }
}

static char* ReadAllLine(char* refSource, char* FileName) {
  FILE* Path = NULL;
  errno_t Error = fopen_s(&Path, FileName, "r+");
  if (Error != 0) {
    printf("%s: %s :%s", FILENAME, ERROR_NOT_FOUND_IT, FileName);
    return "";
  }

  if(Path){
    size_t Index = 0;

    refSource[Index] = (char)fgetc(Path);
    while (refSource[Index] != EOF) {
      Index++;
      refSource[Index] = (char)fgetc(Path);
    }

    Error = fclose(Path);
    if (Error != 0) {
      printf("%s: %s :%s", FILENAME, ERROR_NOT_CLOSE_IT, FileName);
      return "";
    }
  }

  return refSource;
}