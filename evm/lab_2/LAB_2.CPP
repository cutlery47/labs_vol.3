#include <iostream.h>
#include <conio.h>
#include <dos.h>

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
}





void print(int txtcol, int bgcol, int spaces) {
	const char* txtname = colname(txtcol, 0);
	const char* bgname = colname(bgcol, 1);
	//deleting both lines from the top, to perform down scroll
	gotoxy(1, 1);
	for (int i = 0; i <= spaces; ++i) {
		delline();
	}
	textcolor(txtcol);
	textbackground(bgcol);
	gotoxy(1, 8);
	//when scrolled, add new data to the bottom
	for (int j = 0; j <= spaces; ++j) {
		insline();
	}
	gotoxy(1, 8);
	cprintf("Text: %s, Background: %s", txtname, bgname);
}

int main() {
	int left_x = 15, left_y = 12;
	int right_x = 65, right_y = 23;
	int T = 400;
	int S = 2;
	int max_colors = 16;
	int max_backgrounds = 8;
	textbackground(BLACK);
	textcolor(WHITE);
	clrscr();
	window(left_x, left_y, right_x, right_y);
	for (int i = 0; i < max_backgrounds; ++i) {
		for (int j = 0; j < max_colors; ++j)  {
			print(j, i, S);

			if (kbhit()) {
				return 0;
			}

			delay(T);
		}
	}
	getch();
	return 0;
}























