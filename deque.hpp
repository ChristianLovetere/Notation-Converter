#ifndef DEQUE_H
#define DEQUE_H

#include <string>
#include <iostream>
#include "doublyLinkedList.hpp"

class LinkedDeque { // deque as doubly linked list
friend class NotationConverter;
public:
    LinkedDeque(); // constructor
    int size() const; // number of items in the deque
    bool empty() const; // is the deque empty?
    const char& front(); // first element
    const char& back(); // last element
    void insertFront(const char& e); // insert new first element !
    void insertBack(const char& e); // insert new last element !
    char removeFront(); // remove first element !
    char removeBack(); // remove last element !
private:
    DLinkedList DLList; // doubly linked list of elements
    int n; // number of elements
    void printDeque();
};

#endif