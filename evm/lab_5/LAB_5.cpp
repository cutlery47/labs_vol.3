#include <dos.h>
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void interrupt (*old16)(...);

char randChar() {
 unsigned char val = rand() % 255;
 return val;
}

void interrupt far new16(...)
{
 unsigned char num = randChar();
 printf("%c", num);
 _chain_intr(old16);
}

void main()
{
  clrscr();
  srand(time(NULL));
  old16=_dos_getvect(0x16);

  _dos_setvect(0x16, new16);

 while(getch() != 13){};

  _dos_setvect(0x16,old16);

  exit(0);
}