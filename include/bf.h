#include <stdbool.h>
#define MEM_LENGTH 100

typedef enum {
  INC_MEMPTR, 
  DEC_MEMPTR,
  INC_BYTE,
  DEC_BYTE,
  OUTPUT_BYTE,
  INPUT_BYTE,
  JUMP_A,
  JUMP_B,
  INVALID
} INSTRUCTIONS;

INSTRUCTIONS parse(char input);

// , : gets byte of input
char get_input();
void printByte(int ascii_code);
bool jump_check(int data);
