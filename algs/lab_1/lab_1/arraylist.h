#pragma once
#include <iostream>

class ArrayList {
private:
	int** array = NULL;
	int length = 0;

	void expand();
public:
	int size = 0;

	ArrayList(int size);

	void print();

	void insert(int index, int val);
	int remove(int index);

	void push(int val);
	int pop();

	void push_front(int val);
	int pop_front();

	
};