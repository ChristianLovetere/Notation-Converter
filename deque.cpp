#include <string>
#include <iostream>
#include "deque.hpp"

LinkedDeque::LinkedDeque() : DLList(), n(0) { }

// number of items in the queue
int LinkedDeque::size() const {
return n;
}
// is the queue empty?
bool LinkedDeque::empty() const {
return n == 0;
}
// insert new first element
void LinkedDeque::insertFront(const char& e) {
DLList.addFront(e); n++;
}
// insert new last element
void LinkedDeque::insertBack(const char& e) {
DLList.addBack(e); n++;
}
// remove first element
char LinkedDeque::removeFront() {
if (empty()) { throw("empty deque"); }
n--;
return DLList.removeFront(); 
}
// remove last element
char LinkedDeque::removeBack() {
if (empty()) { throw("empty deque"); }
n--;
return DLList.removeBack();
}

void LinkedDeque::printDeque(){

    for (DNode *p = DLList.header->next ; p != DLList.trailer ; p = p->next){
        std::cout << p->contents;
    }
}