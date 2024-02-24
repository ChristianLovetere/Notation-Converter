#ifndef NOTATIONCONVERTER_H
#define NOTATIONCONVERTER_H

#include "NotationConverterInterface.hpp"
#include "deque.hpp"

class NotationConverter
{
  friend class LinkedDeque;
public:
    NotationConverter();
  std::string postfixToInfix(std::string inStr);
  std::string postfixToPrefix(std::string inStr);

  std::string infixToPostfix(std::string inStr);
  std::string infixToPrefix(std::string inStr);

  std::string prefixToInfix(std::string inStr);
  std::string prefixToPostfix(std::string inStr);

  void printAll();
  void validate_char(char a);
private:
  LinkedDeque deque;

};


#endif