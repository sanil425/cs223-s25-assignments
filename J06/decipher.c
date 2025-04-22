#include <stdio.h>

int main(int argc, char* argv[]) // change to accept command line args
{
  if (argc != 2) {
    // no filename
    fprintf(stderr, "%s file not recognized", argv[0]);
    return 1;
  }
  FILE* fp = fopen(argv[1], "r");

  char c = fgetc(fp);
  while (c != EOF)
  {
    char decrypt = (c >> 1) & 0x7F; // shift c to the right and 8 bit mask to clear most sig bit as suggested in requirement 
    printf("%c", decrypt); // printout decrypted letter
    c = fgetc(fp); // mvoe on to next letter
  }
  fclose(fp);
  return 0;
}
