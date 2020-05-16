#include "platform.h"
#include <stddef.h>
#include "string_util.h"
#include <ctype.h>

char* inputString;
//String inputString = "";         // a String to hold incoming data
int gParserPosition = 0;

int stack[128];
int stackPtr = 0;

//TODO return stack functions >r r>
int returnStack[16];

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
    while (isspace(inputString[gParserPosition]))
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

int to_forth_bool(int c_bool) {
    return c_bool ? -1 : 0;
}

void evaluateToken(char *tok) {
    //skip empty string (probably whitespace at the end of the input)
    if (strlen(tok) == 0)
        return;
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
    else if (strcmp(tok, "mod") == 0) {
        int b = pop();
        int a = pop();
        push(a % b);
    }
    else if (strcmp(tok, "emit") == 0) {
        char c = (char)pop();
        print_char(c);
    }
    else if (strcmp(tok, "dup") == 0) {
        int a = pop();
        push(a);
        push(a);
    }
    else if (strcmp(tok, "drop") == 0) {
        pop();
    }
    else if (strcmp(tok, "swap") == 0) {
        int a = pop();
        int b = pop();
        push(a);
        push(b);
    }
    else if (strcmp(tok, ".") == 0) {
        print_int(pop());
    }
    else if (strcmp(tok, ".s") == 0) {
        printStack();
    }
    else if (strcmp(tok, "<") == 0) {
        int b = pop();
        int a = pop();
        push(to_forth_bool(a < b));
    }
    else if (strcmp(tok, ">") == 0) {
        int b = pop();
        int a = pop();
        push(to_forth_bool(a > b));
    }
    else if (strcmp(tok, "=") == 0) {
        int b = pop();
        int a = pop();
        push(to_forth_bool(a == b));
    }
    else if (strcmp(tok, "and") == 0) {
        int b = pop();
        int a = pop();
        push(to_forth_bool(a && b));
    }
    else if (strcmp(tok, "or") == 0) {
        int b = pop();
        int a = pop();
        push(to_forth_bool(a || b));
    }
    else if (strcmp(tok, "xor") == 0) {
        int b = pop();
        int a = pop();
        push(to_forth_bool(a ^ b));
    }
    else if (strcmp(tok, "invert") == 0) {
        int a = pop();
        push(~a);
    }
    else {
        errno = 0;
        char* endptr = NULL;
        long number = strtol(tok, &endptr, 10);
        if (errno != 0)
            return;
        if (endptr == tok) //invalid number, no digits read
            return;
        push((int)number);
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
