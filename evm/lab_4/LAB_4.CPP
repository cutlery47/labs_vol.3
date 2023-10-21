#include <dos.h>
#include <bios.h>
#include <iostream.h>
#include <conio.h>

#define x_l 15
#define y_l 12
#define x_r 65
#define y_r 23

typedef char byte;

struct Key {
	byte ascii;
	byte scan;
};

void get(Key *key) {
	int button = bioskey(0);
	key->ascii = button & 255;
	button = button >> 8;
	key->scan = button & 255;
}

void drawBorders() {

	for (int x = 0; x <= x_r - x_l; ++x) {
		gotoxy(x, 1);
		cputs("#");
		gotoxy(x, y_r - y_l);
		cputs("#");
	}

	for (int y = 1; y < y_r - y_l; ++y) {
		gotoxy(1, y);
		cputs("#");
		gotoxy(x_r - x_l, y);
		cputs("#");
	}

}

void clear(int x, int y) {
	gotoxy(x, y);
	cputs(" ");
}

void put(int x, int y) {
	gotoxy(x, y);
	cputs("*");
}

int main() {
	int quit = 0;
	int x = 2;
	int y = 2;

	Key key;

	clrscr();
	window(15, 12, 65, 23);
	drawBorders();

	gotoxy(x, y);
	cputs("*");

	while (quit == 0) {
		get(&key);
		clear(x, y);

		if (key.scan == 1) {
			return 0;
		} else if (key.scan == 75) {
			x -= 1;
		} else if (key.scan == 77) {
			x += 1;
		}

		if (x <= 1) {
			y -= 1;
			x = x_r - x_l - 1;
		} else if (x >= x_r - x_l) {
			y += 1;
			x = 2;
		}

		if (y <= 1) {
			y = y_r - y_l - 1;
		}  else if (y >= y_r - y_l) {
			y = 2;
		}

		put(x, y);
	}

	return 0;
}
