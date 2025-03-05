#include <stdio.h>
#include <string.h>
#include <stdlib.h>
void printIntToBinary(int num)
{
  signed int integer = (num);
  unsigned int biMask = 0x80000000;
  int i = 0;
  printf("0b ");
  while (biMask > 0)
  {
    if (biMask & num)
    {
      printf("1");
      if (i == 3 || i == 7 || i == 11 || i == 15 || i == 19 || i == 23 || i == 27)
        printf(" ");
    }
    else
    {
      printf("0");
      if (i == 3 || i == 7 || i == 11 || i == 15 || i == 19 || i == 23 || i == 27)
        printf(" ");
    }
    biMask = biMask >> 1;
    i++;
  }
  printf("\n");
}
void printIntToHex(int num)
{
  signed int integer = (num);
  unsigned int hexMask = 0xf0000000;
  int i = 0;
  int j = 28;
  const char *hex = "0123456789ABCDEF";
  printf("0x ");
  while (hexMask > 0)
  {
    unsigned int aa = hexMask & num;
    if (aa)
    {
      unsigned val = (aa) >> j;
      printf("%c", hex[val]);
      if (i == 1 || i == 3 || i == 5)
        printf(" ");
    }
    else
    {
      printf("0");
      if (i == 1 || i == 3 || i == 5)
        printf(" ");
    }
    hexMask = hexMask >> 4;
    i++;
    j = j - 4;
  }
  printf("\n");
}
int main(int argc, char **argv)
{
  if (argc != 2)
  {
    fprintf(stderr, "Usage: %s\n", argv[0]);
    return 1;
  }
  printIntToBinary(atoi(argv[1]));
  printIntToHex(atoi(argv[1]));
  return 0;
}