#define LED0 LED_BUILTIN

//#define DEBUG_PARSER

#define INPUT_LENGTH 100

String inputString = "";         // a String to hold incoming data
int gParserPosition = 0;
bool stringComplete = false;  // whether the string is complete

int stack[256];
int stackPtr = 0;

void setup() {
  Serial.begin(9600);
  // reserve N bytes for the inputString:
  inputString.reserve(INPUT_LENGTH);
  Serial.println('?');
}

String getNextDelimitedWord(char delimiter){
  String token = "";

  //skip leading spaces
  while(inputString.charAt(gParserPosition) == ' ')
    gParserPosition++;
    
  //consume word until next space
  while(inputString.charAt(gParserPosition) != delimiter && gParserPosition < inputString.length()){
    token += inputString.charAt(gParserPosition);
    gParserPosition++;
  }
  return token;
}

void push(int number){
  stack[stackPtr++] = number;
}

int pop(){
  return stack[--stackPtr];
}

void printStack(){
  Serial.print('<');
  Serial.print(stackPtr);
  Serial.print('>');
  Serial.print(' ');
  for(int i = 0; i < stackPtr; i++){
     Serial.print(stack[i]);
     Serial.print(" ");
  }  
}

void evaluateToken(String token){
  char *tok = token.c_str();
  if(strcmp(tok, "+") == 0){
    push(pop() + pop());
  }
  else if(strcmp(tok, "-") == 0){
    int b = pop();
    int a = pop();
    push(a - b);
  }
  else if(strcmp(tok, "*") == 0){
    push(pop() * pop());
    
    }
  else if (strcmp(tok, "/") == 0){
    int b = pop();
    int a = pop();
    push(a / b);    
  }
  else if(strcmp(tok,"emit") == 0){
    char c = (char)pop();
    Serial.print(c);
  }
  else if(strcmp(tok,".") == 0){
    Serial.print(pop());
  }
  else if(strcmp(tok,".s") == 0){
    printStack();
  }
  else{
    int number = token.toInt();
    push(number);
  }
}

void repl() {
  while(gParserPosition < inputString.length()){
    String token = getNextDelimitedWord(' ');
    evaluateToken(token);
  }
  gParserPosition = 0;
}

void ok(){
  Serial.print(' ');
  Serial.print('o');
  Serial.println('k');
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
