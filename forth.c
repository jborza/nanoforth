#include "platform.h"
#include <stddef.h>
#include "string_util.h"

char* inputString;
//String inputString = "";         // a String to hold incoming data
int gParserPosition = 0;




int stack[128];
int stackPtr = 0;

void push(int number) {
    stack[stackPtr++] = number;
    if(stackPtr)
    {
        //stack overflow
    }
}

int pop() {
    if(stackPtr == 0){
        //stack underflow
    }
    return stack[--stackPtr];
}

char* getNextDelimitedWord(char delimiter) {
    //String token = "";

    //skip leading spaces
    while (inputString[gParserPosition] == ' ')
        gParserPosition++;

    int wordStart = gParserPosition;

    //consume word until next space
    int inputLength = strlen(inputString);
    while (inputString[gParserPosition] != delimiter && gParserPosition < inputLength) {
        //token += inputString.charAt(gParserPosition);
        gParserPosition++;
    }
    return strndup(inputString+wordStart, gParserPosition - wordStart);
}

void printStack() {
    print_char('<');
    print_int(stackPtr);
    print_char('>');
    print_char(' ');
    for (int i = 0; i < stackPtr; i++) {
        print_int(stack[i]);
        print_char(' ');
    }
}

void evaluateToken(char *tok) {
    //char* tok = token.c_str();
    if (strcmp(tok, "+") == 0) {
        push(pop() + pop());
    }
    else if (strcmp(tok, "-") == 0) {
        int b = pop();
        int a = pop();
        push(a - b);
    }
    else if (strcmp(tok, "*") == 0) {
        push(pop() * pop());

    }
    else if (strcmp(tok, "/") == 0) {
        int b = pop();
        int a = pop();
        push(a / b);
    }
    else if (strcmp(tok, "emit") == 0) {
        char c = (char)pop();
        print_char(c);
    }
    else if (strcmp(tok, ".") == 0) {
        print_int(pop());
    }
    else if (strcmp(tok, ".s") == 0) {
        printStack();
    }
    else {
        int number = atoi(tok);
        push(number);
    }
}

void print_ok() {
    print_char(' ');
    print_char('o');
    println_char('k');
}

void repl() {
    int inputLength = strlen(inputString);
    str_replace_char(inputString, '\n', ' ');
    while (gParserPosition < inputLength) {
        char * token = getNextDelimitedWord(' ');
        evaluateToken(token);
        free(token);
    }
    gParserPosition = 0;
    print_ok();
}
