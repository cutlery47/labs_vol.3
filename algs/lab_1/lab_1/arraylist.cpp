#pragma once
#include "arraylist.h"

ArrayList::ArrayList(int size) {
	this->size = size;
	this->length = size * 2;
	this->array = new int*[this->length];

	if (this->size >= this->length) {
		expand();
	}

	for (int i = 0; i < size; ++i) {
		int* ptr = new int(i + 1);
		this->array[i] = ptr;
	}
}

void ArrayList::print() {
	std::cout << "[ ";

	for (int i = 0; i < this->size; ++i) {
		std::cout << *this->array[i]; 

		if (i + 1 != this->size) {
			std::cout << " , ";
		}
	}

	std::cout << " ]";
}

void ArrayList::insert(int index, int val) {
	//ÑÄÂÈÃ ÂÑÅÕ ÝËÅÌÅÍÒÎÂ

	int* tmp = NULL;
	int* prev = this->array[index];

	if (this->size + 1 >= this->length) {
		expand();
	}

	for (int i = 0; i < this->size - index; ++i) {
		tmp = this->array[index + i + 1];
		this->array[index + i + 1] = prev;
		prev = tmp;
	}

	// ÄÎÁÀÂËÅÍÈÅ ÝËÅÌÅÍÒÀ
	int* ptr = new int(val);
	this->array[index] = ptr;

	this->size += 1;
}

int ArrayList::remove(int index) {
	int* del = this->array[index];
	int val = *del;
	
	for (int i = 0; i < this->size - index; ++i) {
		this->array[index + i] = this->array[index + i + 1];
	}

	delete del;

	this->size -= 1;
	return val;
}

void ArrayList::push(int val) {
	this->insert(this->size, val);
}

int ArrayList::pop() {
	return this->remove(this->size - 1);
}

void ArrayList::push_front(int val) {
	this->insert(0, val);
}

int ArrayList::pop_front() {
	return this->remove(0);
}

void ArrayList::expand() {
	int** new_arr = new int* [this->length * 2];

	for (int i = 0; i < this->size; ++i) {
		new_arr[i] = this->array[i];
	}

	array = new_arr;
	this->length *= 2;
}


