#include <string>
#include <iostream>
#include "doublyLinkedList.hpp"

DLinkedList::DLinkedList() { // constructor
header = new DNode; // create sentinels
trailer = new DNode;
header->next = trailer; // have them point to each other
trailer->prev = header;
}
DLinkedList::~DLinkedList() { // destructor
    while (!empty()) removeFront(); // remove all but sentinels
    delete header; // remove the sentinels
    delete trailer;
}
bool DLinkedList::empty() const {
    return (header->next == trailer);
}
const char& DLinkedList::front() const {
    return header->next->contents;
}
const char& DLinkedList::back() const {
    return trailer->prev->contents;
}

// insert new node before v
void DLinkedList::add(DNode* v, const char& e) {
    DNode* u = new DNode; 
    u->contents = e; //create new node for e
    u->next = v; // link u in between v
    u->prev = v->prev; // ...and v->prev
    v->prev->next = u;
    u->next->prev = u;
}
// add to front of list
void DLinkedList::addFront(const char& e) {
    add(header->next, e);
}
// add to back of list
void DLinkedList::addBack(const char& e) {
    add(trailer, e);
}

char DLinkedList::remove(DNode* v) { // remove node v
DNode* u = v->prev; // predecessor
DNode* w = v->next; // successor
u->next = w; // unlink v from list
w->prev = u;
char temp = v->contents;
delete v;
return temp;
}
// remove from font
char DLinkedList::removeFront() {
return remove(header->next);
}
// remove from back
char DLinkedList::removeBack() {
return remove(trailer->prev);
}