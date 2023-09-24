#include <windows.h>
#include <iostream>
#include <string>

#include "list.h"
#include "arraylist.h"
#include "stack.h"

class Application {
	private:
		void hideCursor();

	public:
		Application();

		void station();
		void exec();
		int charToInt(char ch);
};