#define LED0 LED_BUILTIN

//#define DEBUG_PARSER

#define INPUT_LENGTH 100

#define ARDUINO

#ifdef ARDUINO
#define print_char(c) Serial.print(c)
#define println_char(c) Serial.println(c)
#define print_int(c) Serial.print(c)
#define print_str(s) Serial.print(s)
#else
#define print_char(c) printf("%c",c)
#define println_char(c) printf("%c\n",c)
#define print_int(c) printf("%d",c)
#define print_str(s) printf("%s",c)
#define true 1
#define false 0
typedef int bool
#endif

String inputString = "";         // a String to hold incoming data
int gParserPosition = 0;
bool stringComplete = false;  // whether the string is complete

int stack[256];
int stackPtr = 0;

void setup() {
    Serial.begin(9600);
    // reserve N bytes for the inputString:
    inputString.reserve(INPUT_LENGTH);
    println_char('?');
}

String getNextDelimitedWord(char delimiter) {
    String token = "";

    //skip leading spaces
    while (inputString.charAt(gParserPosition) == ' ')
        gParserPosition++;

    //consume word until next space
    while (inputString.charAt(gParserPosition) != delimiter && gParserPosition < inputString.length()) {
        token += inputString.charAt(gParserPosition);
        gParserPosition++;
    }
    return token;
}

void push(int number) {
    stack[stackPtr++] = number;
}

int pop() {
    return stack[--stackPtr];
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

void evaluateToken(String token) {
    char* tok = token.c_str();
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
        int number = token.toInt();
        push(number);
    }
}

void repl() {
    while (gParserPosition < inputString.length()) {
        String token = getNextDelimitedWord(' ');
        evaluateToken(token);
    }
    gParserPosition = 0;
}

void ok() {
    print_char(' ');
    print_char('o');
    println_char('k');
}

void loop() {
    // print the string when a newline arrives:
    if (stringComplete) {
        stringComplete = false;
        repl();
        ok();
        // clear the string:
        inputString = "";
    }
}

void serialEvent() {
    while (Serial.available()) {
        // get the new byte:
        char inChar = (char)Serial.read();
        // repl on newline
        if (inChar == '\n') {
            Serial.print(' ');
            stringComplete = true;
            return;
        }
        Serial.print(inChar);
        // add it to the inputString:
        inputString += inChar;
    }
}
