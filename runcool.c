//  CITS2002 Project 1 2021
//  Name(s):             Zach Manson, Dempsey Thompson
//  Student number(s):   22903345, 22988643

//  compile with:  cc -std=c11 -Wall -Werror -o runcool runcool.c

#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

//  THE STACK-BASED MACHINE HAS 2^16 (= 65,536) WORDS OF MAIN MEMORY
#define N_MAIN_MEMORY_WORDS (1<<16)

//  EACH WORD OF MEMORY CAN STORE A 16-bit UNSIGNED ADDRESS (0 to 65535)
#define AWORD               uint16_t
//  OR STORE A 16-bit SIGNED INTEGER (-32,768 to 32,767)
#define IWORD               int16_t

//  THE ARRAY OF 65,536 WORDS OF MAIN MEMORY
AWORD                       main_memory[N_MAIN_MEMORY_WORDS];

//  THE SMALL-BUT-FAST CACHE HAS 32 WORDS OF MEMORY
#define N_CACHE_WORDS       32


//  see:  http://teaching.csse.uwa.edu.au/units/CITS2002/projects/coolinstructions.php
enum INSTRUCTION {
    I_HALT       = 0,
    I_NOP,
    I_ADD,
    I_SUB,
    I_MULT,
    I_DIV,
    I_CALL,
    I_RETURN,
    I_JMP,
    I_JEQ,
    I_PRINTI,
    I_PRINTS,
    I_PUSHC,
    I_PUSHA,
    I_PUSHR,
    I_POPA,
    I_POPR
};

//  USE VALUES OF enum INSTRUCTION TO INDEX THE INSTRUCTION_name[] ARRAY
const char *INSTRUCTION_name[] = {
    "halt",
    "nop",
    "add",
    "sub",
    "mult",
    "div",
    "call",
    "return",
    "jmp",
    "jeq",
    "printi",
    "prints",
    "pushc",
    "pusha",
    "pushr",
    "popa",
    "popr"
};

//  ----  IT IS SAFE TO MODIFY ANYTHING BELOW THIS LINE  --------------


//  THE STATISTICS TO BE ACCUMULATED AND REPORTED
int n_main_memory_reads     = 0;
int n_main_memory_writes    = 0;
int n_cache_memory_hits     = 0;
int n_cache_memory_misses   = 0;

void report_statistics(void)
{
    printf("@number-of-main-memory-reads\t%i\n",    n_main_memory_reads);
    printf("@number-of-main-memory-writes\t%i\n",   n_main_memory_writes);
    printf("@number-of-cache-memory-hits\t%i\n",    n_cache_memory_hits);
    printf("@number-of-cache-memory-misses\t%i\n",  n_cache_memory_misses);
}

//  -------------------------------------------------------------------

//  EVEN THOUGH main_memory[] IS AN ARRAY OF WORDS, IT SHOULD NOT BE ACCESSED DIRECTLY.
//  INSTEAD, USE THESE FUNCTIONS read_memory() and write_memory()
//
//  THIS WILL MAKE THINGS EASIER WHEN WHEN EXTENDING THE CODE TO
//  SUPPORT CACHE MEMORY

AWORD read_memory(int address)
{
    ++n_main_memory_reads;
    return main_memory[address];
}

void write_memory(AWORD address, AWORD value)
{
    ++n_main_memory_writes;
    main_memory[address] = value;
}

//  -------------------------------------------------------------------

//  EXECUTE THE INSTRUCTIONS IN main_memory[]
int execute_stackmachine(void)
{
//  THE 3 ON-CPU CONTROL REGISTERS:
    int PC      = 0;                    // 1st instruction is at address=0
    int SP      = N_MAIN_MEMORY_WORDS;  // initialised to top-of-stack
    int FP      = 0;                    // frame pointer

//  REMOVE THE FOLLOWING LINE ONCE YOU ACTUALLY NEED TO USE FP
    FP = FP;

    while(true) {

        IWORD value1;
        IWORD value2;
        
//  FETCH THE NEXT INSTRUCTION TO BE EXECUTED
        IWORD instruction   = read_memory(PC);
        ++PC;

//      printf("%s\n", INSTRUCTION_name[instruction]);

        if(instruction == I_HALT) {
            break;
        }

        switch (instruction) {
            case I_NOP :
                // nop does nothing
                break;

            case I_ADD :
                value1 = read_memory(SP);
                ++SP;
                value2 = read_memory(SP);
                ++SP;
                --SP;
                write_memory(SP, value1 + value2);
                break;

            case I_SUB :
                value1 = read_memory(SP);
                ++SP;
                value2 = read_memory(SP);
                ++SP;
                --SP;
                write_memory(SP, value1 - value2);
                break;

            case I_MULT :
                value1 = read_memory(SP);
                ++SP;
                value2 = read_memory(SP);
                ++SP;
                --SP;
                write_memory(SP, value1 * value2);
                break;
            case I_DIV :
                // won't be testing division by zero (CM, W05 workshop)
                value1 = read_memory(SP);
                ++SP;
                value2 = read_memory(SP);
                ++SP;
                --SP;
                write_memory(SP, value1 / value2);
                break;

            case I_CALL :
                break;

            case I_RETURN :
                break;

            case I_JMP :
                break;

            case I_JEQ :
                break;

            case I_PRINTI :
                break;

            case I_PRINTS :
                break;

            case I_PUSHC :
                value1 = read_memory(PC);
                ++PC;
                --SP;
                write_memory(SP, value1);
                break;

            case I_PUSHA :
                break;

            case I_PUSHR :
                break;

            case I_POPA :
                break;

            case I_POPR :
                break;
        }

//  SUPPORT OTHER INSTRUCTIONS HERE
//      ....
    }

//  THE RESULT OF EXECUTING THE INSTRUCTIONS IS FOUND ON THE TOP-OF-STACK
    return read_memory(SP);
}

//  -------------------------------------------------------------------

//  READ THE PROVIDED coolexe FILE INTO main_memory[]
void read_coolexe_file(char filename[])
{
    memset(main_memory, 0, sizeof main_memory);   //  clear all memory

//  READ CONTENTS OF coolexe FILE

    FILE* f = fopen(filename, "rb");
    char byte;
    int i = 0;
    while (1) {
        fread(&byte, 2, 1, f); // reads 2 bytes (16bit word) at a time
        if (feof(f)) break;
        printf("Writing %d to %d\n", byte, i);
        write_memory(i,byte); // check if should be directly to main_memory[]
        ++i;
    }
    fclose(f);

}

//  -------------------------------------------------------------------

int main(int argc, char *argv[])
{
//  CHECK THE NUMBER OF ARGUMENTS
    if(argc != 2) {
        fprintf(stderr, "Usage: %s program.coolexe\n", argv[0]);
        exit(EXIT_FAILURE);
    }

//  READ THE PROVIDED coolexe FILE INTO THE EMULATED MEMORY
    read_coolexe_file(argv[1]);

//  EXECUTE THE INSTRUCTIONS FOUND IN main_memory[]
    int result = execute_stackmachine();
    
    printf("result: %i\n", result); // debug statement, eventually remove

    report_statistics();

    return result;          // or  exit(result);
}