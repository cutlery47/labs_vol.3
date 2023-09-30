#include "graphics.h"
#include "conio.h"
#include "math.h"
#include "stdio.h"

#define width 640
#define height 480
#define ratio 0.025
#define rev_ratio 40

void axis() {
	//x-axis
	line(0, height / 2, width, height / 2);

	//y-axis
	line(0, 0, 0, height);

	//value on the axis (stamp)
	char values[3];

	outtextxy(width - 208, 0, "f(x) = sin(x)^3 - cos(x)^3");

	//x-axis stamps
	for (int i = 0; i < width; ++i) {
		if (i % rev_ratio == 0) {
			sprintf(values, "%d", i / rev_ratio);

			putpixel(i, height / 2 + 1, 15);
			putpixel(i, height / 2 - 1, 15);

			if (i != 0) {
				outtextxy(i - textwidth(values) / 3, height / 2 + 4, values);
			}
		}
	}

	//y-axis stamps
	for (int j = 0; j < height; ++j) {
		if (j % rev_ratio == 0) {
			putpixel(1, j, 15);
			sprintf(values, "%d", 6 - j / rev_ratio);

			outtextxy(0 + 4, j, values);
		}
	}
}

void graph() {
	double start = 3.14 / 2;
	double f = 0;
	double max = 0;
	double min = 0;
	char faggies[30];

	for (double x = start * rev_ratio; x < width; ++x) {
		f = pow(cos((double)x * ratio), 3) + pow(sin((double)x * ratio), 3);

		if (x == start * rev_ratio) {
			min = f;
		}

		putpixel(x, height / 2 - (f * rev_ratio), 10);

		if (f > max) {
			max = f;
		} else if (f < min) {
			min = f;
		}
	}
	setcolor(12);
	line(start * rev_ratio, height / 2 - (max * rev_ratio) - 1, width, height / 2 - (max * rev_ratio) - 1);
	line(start * rev_ratio, height / 2 - (min * rev_ratio) + 1, width, height / 2 - (min * rev_ratio) + 1);

	setcolor(15);

	sprintf(faggies, "sup{f(x)} = %lf", ceil(max));
	outtextxy(start * rev_ratio, height / 2 - (max * rev_ratio) - 10, faggies);

	sprintf(faggies, "inf{f(x)} = %lf", floor(min));
	outtextxy(start * rev_ratio, height / 2 - (min * rev_ratio) + 5, faggies);



}

int main() {
	clrscr();
	int driver = DETECT;
	int mode;
	char* path = "c://turboc3//bgi";

	initgraph(&driver, &mode, path);
	axis();
	graph();


	getch();
	return 0;
}