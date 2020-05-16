#ifdef ARDUINO
#include <Arduino.h>
#define print_char(c) Serial.print(c)
#define println_char(c) Serial.println(c)
#define print_int(c) Serial.print(c)
#define print_str(s) Serial.print(s)
typedef int bool;
#endif

#ifndef ARDUINO
#include <stdio.h>
#define print_char(c) printf("%c",c)
#define println_char(c) printf("%c\n",c)
#define print_int(c) printf("%d",c)
#define print_str(s) printf("%s",c)
#define true 1
#define false 0
typedef int bool;
#endif
