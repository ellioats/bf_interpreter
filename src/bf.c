#include <stdio.h>
#include "../include/bf.h"

bool jump_check(int data) {
  if (data == 0)
    return true; 
  // [ -> jump to next ']'
  // ] -> continue to next command, do not jump back
  
  return false; 
  // [ -> continue to next command
  // ] -> jump back to '['

}

void printByte(int ascii_code) {
  // printf("attempting to print ascii code %i\n", ascii_code);
  printf("%c", (char)ascii_code);
  
}

// TEST: functionality
char get_input() {
  return getchar();
}

INSTRUCTIONS parse(char input) {
  switch (input) {
    case '>':
      return INC_MEMPTR;
    break;
    case '<':
      return DEC_MEMPTR;
    break;
    case '+':
      return INC_BYTE;
    break;
    case '-':
      return DEC_BYTE;
    break;
    case '.':
      return OUTPUT_BYTE;
    break;
    case ',':
      return INPUT_BYTE;
    break;
    case '[':
      return JUMP_A;
    break;
    case ']':
      return JUMP_B;
    break;
  }

  return INVALID; // invalid instruction
}
