#include <stdio.h>
#include <getopt.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "../include/bf.h"

void help_menu() {
  printf("-f: specify filename with brianfuck\n");
  printf("-i: provide inline brainfuck\n");
  printf("-h: shows help menu\n");
}

int main(int argc, char *argv[]) {

  bool file = false;
  char *filename = NULL;

  bool cli = false;
  char *content = NULL;

  bool displayHelpMenu = false;

  int c;
  while ((c = getopt(argc, argv, "hf:i:")) != -1) {
    switch (c) {
      case 'f':
        file = true;
        filename = optarg;
        break;
      case 'i':
        cli = true;
        content = optarg;
        break;
      case 'h':
        displayHelpMenu = true;
      break;
    }
  }

  if (displayHelpMenu) {
    help_menu();
    return 0;
  }

  // FIX: unoptimal design, create new function for parsing tokens from input, regardless of source (file / cli input)  
  if (cli) {

    int mem[MEM_LENGTH] = {0};
    int current_index = 0;
    int jump_start_index;
    int jump_end_index;

    int direction = 1;

    bool isJumping = false;
    INSTRUCTIONS jump_break_condition;

    int len = strlen(content);
    
    // iterates over each instruction
    for (int x = 0; x < len; x += direction) {
      switch(parse(content[x])) {
        case INC_MEMPTR: 
          #ifdef DEBUG
          //printf("increment current index to %i\n", x);
          #endif
          current_index++;
          break;
        case DEC_MEMPTR:
          #ifdef DEBUG
          // printf("decrementing current index to %i\n", x);
          #endif
          current_index--;
          break;
        case INC_BYTE:
          #ifdef DEBUG
          //printf("incrementing current byte to %i\n", mem[current_index] + 1);
          #endif
          mem[current_index]++;
          break;
        case DEC_BYTE: 
          #ifdef DEBUG
          // puts("decrementing current byte");
          #endif
          mem[current_index]--;
          break;
        case OUTPUT_BYTE:
          #ifdef DEBUG
          //puts("outputting current byte");
          #endif
          printByte(mem[current_index]);
          break;
        case INPUT_BYTE: 
          #ifdef DEBUG
          puts("inputting current byte");
          #endif
          get_input();
          break;
        case JUMP_A:
          jump_start_index = x;
          if (jump_check(mem[current_index])) {
            if (jump_end_index != -1 && jump_start_index < jump_end_index) { // if jump end index exists
              x = jump_end_index + 1;
            } else { // if jump end does not exist or isn't associated with the current bracket
              direction = 1;
              jump_break_condition = JUMP_B;
              isJumping = true;
            }
          } else {
            // continues to next command
          }
          break;
        case JUMP_B:
          jump_end_index = current_index;
          if (jump_check(mem[current_index])) {
            // continue to next command
          } else {
            x = jump_start_index + 1;
          }
          break;
        case INVALID:
          puts("invalid instruction detected... Exiting");
          return 0;
          break;  
      }
    }


  }
  printf("\n");

  return 0;
}
