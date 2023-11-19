#include <dos.h>
#include <stdio.h>

void interrupt (*old) (...);


int main() {
	old = getvect(5);
	return 0;
}