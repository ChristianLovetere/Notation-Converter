#ifndef DOUBLYLINKEDLIST_H
#define DOUBLYLINKEDLIST_H

#include <string>
#include <iostream>

class DNode { // doubly linked list node
private:
char contents;
DNode* prev; // previous node in list
DNode* next; // next node in list
friend class DLinkedList; // allow
friend class LinkedDeque;
friend class NotationConverter;
};

class DLinkedList {
    friend class LinkedDeque;
    friend class NotationConverter;
public:
    DLinkedList(); // constructor
    ~DLinkedList(); // destructor
    bool empty() const; // is list empty?
    const char& front() const; // get front element
    const char& back() const; // get back element
    void addFront(const char& e); // add to front of list
    void addBack(const char& e); // add to back of list
    char removeFront(); // remove from front
    char removeBack(); // remove from back
private: // local type definitions
    DNode* header; // list sentinels
    DNode* trailer;
protected: // local utilities
    void add(DNode* v, const char& e); //insert new node before v
    char remove(DNode* v); // remove node v   
};

#endif