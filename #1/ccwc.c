#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>
#include <sys/stat.h>

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

int main(int argc, char *argv[])
{
  bool cFlag = false;

  // parse args
  int opt = getopt(argc, argv, "c");
  while (opt != -1)
  {
    switch (opt)
    {
    case 'c':
      cFlag = true;
      break;
    case '?':
      printf("Try '%s --help' for more information.\n", argv[0]);
      exit(1);
    }
    opt = getopt(argc, argv, "c");
  }

  // process args
  if (cFlag)
  {
    if (optind == argc)
    {
      fprintf(stderr, "%s: Expecting a filename to be given as the first positional argument\n", argv[0]);
      exit(2);
    }

    char *filename = argv[optind];
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

  exit(0);
}
