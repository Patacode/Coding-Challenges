#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>
#include <sys/stat.h>
#include <bits/getopt_core.h>
#include <string.h>
#include <stdarg.h>

int countDigits(int number)
{
  int counter = 1;
  while (number > 9)
  {
    number /= 10;
    counter++;
  }
  return counter;
}

int isFile(const char *path)
{
  struct stat path_stat;
  stat(path, &path_stat);
  return S_ISREG(path_stat.st_mode);
}

int countBytes(const char *str)
{
  int counter = 0;
  while (str[counter] != '\0')
  {
    counter++;
  }
  return counter;
}

int countBytesInFile(const char *filename)
{
  FILE *fptr = fopen(filename, "r");

  if (fptr == NULL)
  {
    return -1;
  }

  if (!isFile(filename))
  {
    return -2;
  }

  char buffer[1000];
  int bytesQty = 0;
  while (fgets(buffer, 1000, fptr))
  {
    bytesQty += countBytes(buffer);
  }

  fclose(fptr);
  return bytesQty;
}

int countLinesInFile(const char *filename)
{
  FILE *fptr = fopen(filename, "r");

  if (fptr == NULL)
  {
    return -1;
  }

  if (!isFile(filename))
  {
    return -2;
  }

  char buffer[1000];
  int linesQty = 0;
  while (fgets(buffer, 1000, fptr))
  {
    linesQty++;
  }

  fclose(fptr);
  return linesQty;
}

char *intToString(int number, char *res)
{
  sprintf(res, "%d", number);
  return res;
}

char *concatStrings(char *res, int qty, ...)
{
  va_list ptr;
  va_start(ptr, qty);

  for (int i = 0; i < qty; i++) {
    const char *arg = va_arg(ptr, char*);
    strcat(res, arg);
  }

  va_end(ptr);
  return res;
}

int main(int argc, char *argv[])
{
  bool cFlag = false;
  bool lFlag = false;

  // parse args
  int opt = getopt(argc, argv, "cl");
  while (opt != -1)
  {
    switch (opt)
    {
    case 'c':
      cFlag = true;
      break;
    case 'l':
      lFlag = true;
      break;
    case '?':
      printf("Try '%s --help' for more information.\n", argv[0]);
      exit(1);
    }
    opt = getopt(argc, argv, "cl");
  }

  // process args
  if (cFlag || lFlag)
  {
    if (optind == argc)
    {
      fprintf(stderr, "%s: Expecting a filename to be given as the first positional argument\n", argv[0]);
      exit(2);
    }

    char *filename = argv[optind];
    if (cFlag && lFlag)
    {
      const int bytesQty = countBytesInFile(filename);
      const int linesQty = countLinesInFile(filename);
      const int digitsQtyOfBytesQty = countDigits(bytesQty);
      const int digitsQtyOfLinesQty = countDigits(linesQty);
      const int maxDigitsQty = digitsQtyOfBytesQty > digitsQtyOfLinesQty ? digitsQtyOfBytesQty : digitsQtyOfLinesQty;
      char maxDigitsQtyStrBuffer[20];
      intToString(maxDigitsQty, maxDigitsQtyStrBuffer);

      char pattern[20];
      concatStrings(pattern, 5, "%", maxDigitsQtyStrBuffer, "d %", maxDigitsQtyStrBuffer, "d %s\n");
      printf(pattern, linesQty, bytesQty, filename);
    }
    else if (cFlag)
    {
      const int bytesQty = countBytesInFile(filename);
      switch (bytesQty)
      {
      case -1:
        fprintf(stderr, "%s: %s: No such file\n", argv[0], filename);
        exit(3);
      case -2:
        fprintf(stderr, "%s: %s: Is a directory\n", argv[0], filename);
        exit(4);
      default:
        printf("%d %s\n", bytesQty, filename);
      }
    }
    else if (lFlag)
    {
      const int linesQty = countLinesInFile(filename);
      switch (linesQty)
      {
      case -1:
        fprintf(stderr, "%s: %s: No such file\n", argv[0], filename);
        exit(3);
      case -2:
        fprintf(stderr, "%s: %s: Is a directory\n", argv[0], filename);
        exit(4);
      default:
        printf("%d %s\n", linesQty, filename);
      }
    }
  }

  exit(0);
}
