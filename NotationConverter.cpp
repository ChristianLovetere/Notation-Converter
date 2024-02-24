//Christian Lovetere U46489387
//A set of source files and headers that altogether allow the user to convert between infix, postfix, and prefix freely. Uses a deque of chars to store operands or operators...
//...(depending on the method) and assign them in the proper order. Some methods require a flag for order assignment, while most use the size of the deque.
//...compile with: g++ -Wall -std=c++11 NotationConverter.cpp deque.cpp doublyLinkedList.cpp PP2Test.cpp (so as to define the functions for the doublylinkedlist and deque...
//from the other source files.


#include "NotationConverter.hpp"
#include "deque.hpp"
#include "doublyLinkedList.hpp"
#include "catch.hpp"


NotationConverter::NotationConverter() : deque() { } //constructor

void NotationConverter::printAll(){// print method for debugging purposes
    deque.printDeque();
}

std::string NotationConverter::postfixToInfix(std::string inStr) { //go from postfix to infix
    
    std::string input_string = inStr; //copy input string to new string
    std::string result_string = "";   //initialize empty resulting string

    for(int i = 0; i < (int) input_string.length();++i){ //for loop that analyzes each char from the input string, one at a time.
        char current = input_string.at(i);
        validate_char(current);                    //ensure the string is legal
        if (current != ' '){                       //ignore spaces
            if (isalpha(current) == 0) { //if the item here is an operator,

                if (deque.size() == 2) {        //AND the deque currently holds 2 operands,

                    result_string += '(';                   //print open parenthesis
                    result_string += deque.removeFront();   //print first operand from deque
                    result_string += ' ';                   //print space
                    result_string += current;               //print operator at current for loop iteration
                    result_string += ' ';                   //print space
                    result_string += deque.removeFront();   //print second operand from deque
                    result_string += ')';                   //print closing parenthesis
                }                                           //altogether, an example result is: (A + B)

                else if (deque.size() == 1) {   //AND the deque currently holds 1 operand,

                    result_string += ' ';                   //print space
                    result_string += current;               //print operator at current for loop iteration
                    result_string += ' ';                   //print space
                    result_string += deque.removeFront();   //print operand from deque
                    std::string temp_string(1,'(');         //create a temp string that just holds '('
                    result_string.insert(0, temp_string);   //insert this temp string at the very beginning of the result string
                    result_string += ')';                   //print ')'
                }                                           //altogether, an example result is: ((A + B) + C)

                else if (deque.empty()) {       //AND the deque is currently empty,

                    for(int j = result_string.length()-1; j != 0; j--) {    //seek result string from back to front...
                        char j_current = result_string.at(j);                   
                        char j_previous = result_string.at(j-1);
                        if (j_current == '(' && j_previous == ')') {        //until finding the first spot in the result string where there are two adjacent parentheses like this: ")("

                            std::string string_current(1,current);          //once found, create a string that holds just the current operator
                            result_string.insert(j, " ");                   //insert a space between the two adjacent parentheses
                            result_string.insert(j, string_current);        //insert the current operator between the two adjacent parentheses
                            result_string.insert(j, " ");                   //insert a space between the two adjacent parentheses

                            std::string string_open_bracket(1,'(');         //create a string with just the open bracket
                            result_string.insert(0, string_open_bracket);   //insert the open parenthesis at the beginning of the result string
                            result_string += ')';                           //add a closing parenthesis to the back of the string
                        }                                                   //altogether, an example before and after is:
                    }                                                       //before: (A + B)(C + D)
                }                                                           //after:  ((A + B)/(C + D))
            }
            else if (isalpha(current) != 0) { //if the item here is an operand,
                deque.insertBack(current);        //add it to the back of the deque
            }
        }
    }
    return result_string;
}

std::string NotationConverter::postfixToPrefix(std::string inStr) { //go from postfix to prefix

    std::string input_string = inStr; //copy input string to new string
    std::string result_string = "";   //initialize empty resulting string

    for(int i = 0; i < (int) input_string.length();++i){  //for loop that analyzes each char from the input string, one at a time.
        char current = input_string.at(i);
        validate_char(current);                     //ensure the string is legal
        if (current != ' '){                        //ignore spaces
            if (isalpha(current) == 0 && deque.size() == 2) { //if the current char is an operator and the deque holds 2 operands,

                result_string += current;                 //print the operator
                result_string += ' ';                      
                result_string += deque.removeFront();     //print first operand from deque
                result_string += ' ';
                result_string += deque.removeFront();     //print second operand from deque
                result_string += ' ';
                
            }                                             //example: - A B
            else if (isalpha(current) == 0 && deque.size() == 1) { //if the current char is an operator and the deque holds 1 operand,
                
                result_string += deque.removeFront();          //print the operand from the deque

                std::string temp_string(1, current);           //create temp string with current operator in it
                result_string.insert(0, " ");                  //insert space at the beginning of the result string
                result_string.insert(0, temp_string);          //insert the string at the beginning of the result string
            }                                                  //example: + - A B C

            else if (isalpha(current) == 0 && deque.empty()) { //if the current char is an operator and the deque is empty,

                std::string temp_string(1, current);           //create temp string with current operator in it
                result_string.insert(0, " ");                  //insert space at the beginning of the result string
                result_string.insert(0, temp_string);          //insert the string at the beginning of the result string
                                                               //example - / + A B + X Y R
            }                                                  
            else if (isalpha(current) != 0) {                  //if the current char is an operand

                deque.insertBack(current);                     //add it to the back of the deque
            }
        }
    }
    return result_string;
}

std::string NotationConverter::infixToPostfix(std::string inStr) { //go from infix to postfix

    std::string input_string = inStr; //copy input string to new string
    std::string result_string = "";   //initialize empty resulting string
    
    for(int i = 0; i < (int) input_string.length();++i){ //for loop that analyzes each char from the input string, one at a time.
        char current = input_string.at(i);         
        validate_char(current);                    //ensure the string is legal
        if (current != ' ' && current != '('){     //ignore spaces and open parentheses, as only closing parentheses are needed to determine term positioning
            if (current == ')') {                  //if the current char is a closing parenthesis, drop the operator out of the deque and into the result string...
                                                   //... this condition must be checked before the second condition as '(' will satisfy that one too. (false positive)
                result_string += deque.removeBack();   
                result_string += ' ';              //print a space
            }
            else if (isalpha(current) == 0) {      //if the current char is an operator, add it to the back of the deque.
                deque.insertBack(current);
            }
            else if (isalpha(current) != 0) {      //if the current char is an operand, add it to the result string, with a space.
                result_string += current;          
                result_string += ' ';
            }

        }
    }
    return result_string;

}

std::string NotationConverter::infixToPrefix(std::string inStr) { //go from infix to prefix. This method is a composite of two others.
    std::string temp_string = infixToPostfix(inStr);
    return postfixToPrefix(temp_string); 
}

std::string NotationConverter::prefixToInfix(std::string inStr) { //go from prefix to infix. This method is a composite of two others.
    std::string temp_string = prefixToPostfix(inStr);
    return postfixToInfix(temp_string);
}

std::string NotationConverter::prefixToPostfix(std::string inStr) { //go from prefix to postfix

    std::string input_string = inStr;
    std::string result_string = "";
    int amt_printed = 0;                                     //this integer works as a flag to know how many operands have been printed. In other methods, we use the size of the...
                                                             //...deque to differentiate. However, we store operators, not operands, in the deque for this conversion. so a flag...
                                                             //...is needed.
    for(int i = 0; i < (int) input_string.length();++i){           
        char current = input_string.at(i);
        validate_char(current);
        if (current != ' '){
            if (isalpha(current) == 0 && amt_printed != 2) { //if the char here is an operator and we've printed less than 2 operands,

                deque.insertBack(current);                        //add the current operator to the back of the deque
            }
            else if (isalpha(current) == 0 && amt_printed == 2) { //if the char here is an operator and we've printed 2 operands,

                result_string += deque.removeBack();              //print the operator stored in the back of the deque
                result_string += ' ';                             //print a space  
                amt_printed = 0;                                  //reset amount printed to 0

                deque.insertBack(current);                        //insert the CURRENT operator into the back of the deque.
            }
            else if (isalpha(current) != 0 && amt_printed != 2) { //if the char here is an operand,

                result_string += current;                         //print it to the result string
                result_string += ' ';                             //with a space
                amt_printed += 1;                                 //increment amount printed

            }
            else if (isalpha(current) != 0 && amt_printed == 2) { //if the char here is an operand and we've already printed 2,

                    result_string += deque.removeBack();          //print the operator out of the back of the deque
                    result_string += ' ';                         //space
                    result_string += current;                     //print the current operand
                    result_string += ' ';                         //space
            }
            
        }
    }
    while (deque.empty() == false) { //while the deque still has contents,
        result_string += deque.removeBack();    //drop the rest of its contents out at the back of the result string
        if (deque.size() != 0) {                //and as long as were not in the last iteration of this while loop,
        result_string += ' ';                   //put a space too.
        }
    }
    return result_string;
}

void NotationConverter::validate_char(char a) { //ensure that each char is legal by making sure its either an operator or a letter.
    if (a != '(' && a != ')' && a != '-' && a != '+' && a != '-' && a != '*' && a != '/' && a != ' ' && isalpha(a) == 0){
        throw("Input Error\n"); //if not, throw an error.
    }
}