#pragma once
#include <iostream>

class Stack {
private:
	char** stack = NULL;
	
	int length = 0;

	void insert(int index, char val);
	char remove(int index);

	void expand();
public:
	int size = 0;

	Stack(int size);

	void print();
	char top();

	void push(char val);
	char pop();

	
};