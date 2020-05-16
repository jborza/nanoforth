#define LED0 LED_BUILTIN

//#define DEBUG_PARSER

#define INPUT_LENGTH 100

#include "config.h"
#include "platform.h"
#include "stack.h"
#include "forth.h"

int stringComplete = 0;  // whether the string is complete
String inputBuffer = "";

void setup() {
  #ifdef ARDUINO
    Serial.begin(9600);
  #endif
    // reserve N bytes for the inputString:
    inputBuffer.reserve(INPUT_LENGTH);
    println_char('?');
}

void loop() {
    // print the string when a newline arrives:
    if (stringComplete) {
        stringComplete = false;
        inputString = inputBuffer.c_str();
        repl();        
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
        inputBuffer += inChar;
    }
}
