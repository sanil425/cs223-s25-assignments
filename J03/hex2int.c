#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int power(int b, int e) {
  int res = 1;

  for (int i = 0; i < e; i++) {
    res *= b;
  }
  return res;
}

int binaryToInt(char* input)
{
  char num[100];
  strncpy(num, input+2, strlen(input)-1); // remove 0b
  num[strlen(input)-1] = '\0'; //terminate string
  int len = strlen(num);

  int val = 0;
  for (int i = 0; i< len; i ++) {
    val += power(2,len-i-1) * (num[i]-'0');
  }
  return val;
}

int hexToInt(char* input) {
  char num[100];
  strncpy(num, input+2, strlen(input)-1); // remove 0x
  num[strlen(input)-1] = '\0'; //terminate string
  int len = strlen(num);
  int val =0;
  for (int i = 0; num[i]!='\0';i++) {
    char c = num[i];
    int bitval = 0;

    if ( c >= '0' && c <='9') bitval = c - '0';// if c is digit between 0 to 9 convert to int
    else if ( c>='A' && c<='F') bitval = c-'A'+10; // if c is letter A-F, convert to 10-15
    
    // shift val 4 bits left (one hex digit)
    val = val << 4;
    val = val | bitval; // combines values of bitval and value
  }
  return val;
}


int main(int argc, char *argv[])
{

  if (argc != 2)
  {
    fprintf(stderr, "Usage: %s\n", argv[0]);
    return 1;
  }

  int ret;
  if (argv[1][1] == 'b'){
    ret = binaryToInt(argv[1]);
  }
  if (argv[1][1] == 'x'){
    ret = hexToInt(argv[1]);
  }
  printf("%d\n", ret);

  return 0;
}
