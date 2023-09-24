#include <iostream>
#pragma once

class ListNode {
    public:
        ListNode(int data);

        int data;
        ListNode* prev;
        ListNode* next;        
};

class List {
    public:
        ListNode* head = NULL;
        int size = 0;
        
        List(int size);
        
        ListNode* find(short index);
        void create(short size);
        void print();
        void insert(int data, int index);
        void remove(int index);
};
