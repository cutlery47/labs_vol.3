#include <iostream.h>
#include <conio.h>
#include <dos.h>
#include <stdlib.h>
#include <limits.h>

#define SHORT 16

const char* colname(int color, int mode) {
	switch(color) {
		case(0):
			if (mode) {
				return "BLACK";
			} else {
				return "CHERNIY";
			}
		case(1):
			if (mode) {
				return "BLUE";
			} else {
				return "SINIY";
			}
		case(2):
			if (mode) {
				return "GREEEN";
			} else {
				return "ZELENIY";
			}
		case(3):
			if (mode) {
				return "CYAN";
			} else {
				return "GOLUBOY";
			}
		case(4):
			if (mode) {
				return "RED";
			} else {
				return "KRASNIY";
			}
		case(5):
			if (mode) {
				return "MAGNETA";
			} else {
				return "MAGNETA";
			}
		case(6):
			if (mode) {
				return "BROWN";
			} else {
				return "KORICHNEVIY";
			}
		case(7):
			if (mode) {
				return "LIGHTGRAY";
			} else {
				return "SVETLO-SERIY";
			}
		case(8):
			if (mode) {
				return "DARKGRAY";
			} else {
				return "TEMNO-SERIY";
			}
		case(9):
			if (mode) {
				return "LIGHTBLUE";
			} else {
				return "SVETLO-SINIY";
			}
		case(10):
			if (mode) {
				return "LIGHTGREEEN";
			} else {
				return "SVETLO-ZELENIY";
			}
		case(11):
			if (mode) {
				return "LIGHTCYAN";
			} else {
				return "SVETLO-GOLUBOY";
			}
		case(12):
			if (mode) {
				return "LIGHTRED";
			} else {
				return "SVETLO-KRASNIY";
			}
		case(13):
			if (mode) {
				return "LIGHTMAGNETA";
			} else {
				return "SVETLO-MAGNETA";
			}
		case(14):
			if (mode) {
				return "YELLOW";
			} else {
				return "ZHELTIY";
			}
		case(15):
			if (mode) {
				return "WHITE";
			} else {
				return "BELIY";
			}
	}
	return 0;
}


union binshort {
	short s;
	unsigned short u;
};

int* serializeShort(short number) {
	int* ser_arr = (int*)malloc(sizeof(int) * SHORT);
	int i = 0;

	for (int val = 16384; val > 0; val >>= 1) {

		if (number & val) {
			ser_arr[i] = 1;
		} else {
			ser_arr[i] = 0;
		}

		i += 1;
	}
	return ser_arr;
}

void printShort(int* arr, int size) {
	for (int i = 0; i < size - 1; ++i) {
		cprintf("%d", arr[i]);
	}
	return;
}

void print(int txtcol, int bgcol, int spaces, int* bits) {
	const char* txtname = colname(txtcol, 0);
	const char* bgname = colname(bgcol, 1);

	//deleting both lines from the top, to perform down scroll
	gotoxy(1, 1);
	for (int i = 0; i <= spaces; ++i) {
		delline();
	}

	//BLINK = 128;
	textattr(BLINK | bgcol * 16 | txtcol);
	gotoxy(1, 8);

	//when scrolled, add new data to the bottom
	for (int j = 0; j <= spaces; ++j) {
		insline();
	}
	gotoxy(1, 8);
	printShort(bits, SHORT);
	gotoxy(1, 9);

	cprintf("Text color: %s, Backgorund color: %s", txtname, bgname);
	return;
}

int main() {
	int left_x = 15, left_y = 12;
	int right_x = 65, right_y = 23;
	int T = 400;
	int S = 2;
	int max_colors = 16;
	int max_backgrounds = 8;

	int* arr;
	union binshort bsh;

	textbackground(BLACK);
	textcolor(WHITE);
	clrscr();

	cprintf("Enter a short int (-32768; 16384): ");

	cscanf("%d", &bsh.s);
	getch();

	arr = serializeShort(bsh.u);

	window(left_x, left_y, right_x, right_y);

	for (int i = 0; i < max_backgrounds; ++i) {
		for (int j = 0; j < max_colors; ++j)  {
			print(j, i, S, arr);
			if (kbhit()) {
				return 0;
			}

			delay(T);
		}
	}

	return 0;
}































