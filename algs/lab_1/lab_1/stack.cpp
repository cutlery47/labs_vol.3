//completet redundancy 
//idgaf

#include "stack.h"

Stack::Stack(int size) {
	this->size = size;
	this->length = size * 2;
	this->stack = new char* [this->length];

	if (this->size >= this->length) {
		expand();
	}

	for (int i = 0; i < size; ++i) {
		char* ptr = new char(' ');
		this->stack[i] = ptr;
	}
}

void Stack::print() {
	std::cout << "[ ";

	for (int i = 0; i < this->size; ++i) {
		std::cout << *this->stack[i];

		if (i + 1 != this->size) {
			std::cout << " , ";
		}
	}

	std::cout << " ]";
}

void Stack::insert(int index, char val) {
	//ÑÄÂÈÃ ÂÑÅÕ ÝËÅÌÅÍÒÎÂ

	if (index > size || index < 0) {
		std::cout << "invalid index lol";
		return;
	}

	char* tmp = NULL;
	char* prev = this->stack[index];

	if (this->size + 1 >= this->length) {
		expand();
	}

	for (int i = 0; i < this->size - index; ++i) {
		tmp = this->stack[index + i + 1];
		this->stack[index + i + 1] = prev;
		prev = tmp;
	}

	// ÄÎÁÀÂËÅÍÈÅ ÝËÅÌÅÍÒÀ
	char* ptr = new char(val);
	this->stack[index] = ptr;

	this->size += 1;
}

char Stack::remove(int index) {
	if (index >= size || index < 0) {
		std::cout << "invalid index lol";
		return 0;
	}

	char* del = this->stack[index];
	int val = *del;

	for (int i = 0; i < this->size - index; ++i) {
		this->stack[index + i] = this->stack[index + i + 1];
	}

	delete del;

	this->size -= 1;
	return val;
}

void Stack::push(char val) {
	this->insert(this->size, val);
}

char Stack::pop() {
	return this->remove(this->size - 1);
}

char Stack::top() {
	return (this->size == 0) ? ' ' : *this->stack[size - 1];
}

void Stack::expand() {
	if (this->length == 0) {
		this->length += 1;
	}

	char** new_arr = new char* [this->length * 2];

	for (int i = 0; i < this->size; ++i) {
		new_arr[i] = this->stack[i];
	}

	stack = new_arr;
	this->length *= 2;
}