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

// Generic function for pushing to top of stack
void PUSH(int *SP, IWORD x) {
    --*SP;
    write_memory(*SP, x);
}

// Generic function for popping from top of stack
IWORD POP(int *SP) {
    IWORD value = read_memory(*SP);
    ++*SP;
    return value;
}

//  EXECUTE THE INSTRUCTIONS IN main_memory[]
int execute_stackmachine(void)
{
//  THE 3 ON-CPU CONTROL REGISTERS:
    int PC      = 0;                    // 1st instruction is at address=0
    int SP      = N_MAIN_MEMORY_WORDS;  // initialised to top-of-stack
    int FP      = 0;                    // frame pointer

//  REMOVE THE FOLLOWING LINE ONCE YOU ACTUALLY NEED TO USE FP
    //FP = FP;

    while(true) {

        IWORD value1;
        IWORD value2;
        
//  FETCH THE NEXT INSTRUCTION TO BE EXECUTED
        IWORD instruction   = read_memory(PC);
        ++PC;

        printf("%s\n", INSTRUCTION_name[instruction]);

        if(instruction == I_HALT) {
            break;
        }

        switch (instruction) {
            case I_NOP :
                // nop does nothing
                break;

            case I_ADD :
                value1 = POP(&SP);
                value2 = POP(&SP);
                PUSH(&SP, value1+value2);
                break;

            case I_SUB :
                value1 = POP(&SP);
                value2 = POP(&SP);
                PUSH(&SP, value2 - value1);
                break;

            case I_MULT :
                value1 = POP(&SP);
                value2 = POP(&SP);
                PUSH(&SP, value1 * value2);
                break;
            case I_DIV :
                // won't be testing division by zero (CM, W05 workshop)
                value1 = POP(&SP);
                value2 = POP(&SP);
                PUSH(&SP, value2 / value1);
                break;

            case I_CALL :
                PUSH(&SP, PC+1); // push instruction address that will be exec when function returns
                PUSH(&SP, FP); // push previous FP value
                FP = SP; // new FP is current SP

                value1 = read_memory(PC); // called function's address
                PC = value1; // this may need to be PC = value1 - 1; seems to be working as is
                break;

            case I_RETURN :
                value1 = POP(&SP); // the return value
                value2 = read_memory(PC); // the offset to FP for location to write return value
                PC = read_memory(FP + 1); // PC moved back to calling function
                write_memory(FP + value2, value1); // write return value to memory
                SP = FP + value2; // move TOS to where return value is written
                FP = read_memory(FP); // FP is set to previous FP
                break;

            case I_JMP :
                //Get the first word and then the address of that first word
                //I'm not sure how to make it execute after the address of the first word
                //But I think my way of getting the first words address is okay.
                value1 = read_memory(PC);
                --SP;
                value2 = read_memory(value1);
                
                break;

            case I_JEQ :
                printf("    %s not implemented!\n", INSTRUCTION_name[instruction]);
                break; 

            case I_PRINTI :
                value1 = read_memory(SP);
                ++SP;
                --SP;
                //error claiming undeclared identifier 'd' and an expected 
                //expression error
                printf(%d, value1); // prints the integer that was on top of the stack
                break;

            case I_PRINTS :
                printf("    %s not implemented!\n", INSTRUCTION_name[instruction]);
                break;

            case I_PUSHC :
                value1 = read_memory(PC); //value1 is the constant
                ++PC;
                PUSH(&SP, value1);
                break;

            case I_PUSHA :
                value1 = read_memory(PC); // value1 is a memory address
                ++PC;
                value2 = read_memory(value1); // constant at address value1
                PUSH(&SP, value2); // push constant
                break;

            case I_PUSHR :
                value1 = read_memory(PC); // offset from FP
                ++PC;
                value2 = read_memory(FP + value1); // value to push
                PUSH(&SP, value2);
                break;

            case I_POPA :
                value1 = read_memory(PC); // address where popped value will go
                ++PC;
                value2 = POP(&SP); // value to write
                write_memory(value1, value2);
                break;

            case I_POPR :
                value1 = read_memory(PC); // offset to FP
                ++PC;
                value2 = POP(&SP); // value to write
                write_memory(FP + value1, value2);
                break;
        }
    }

//  THE RESULT OF EXECUTING THE INSTRUCTIONS IS FOUND ON THE TOP-OF-STACK
    return read_memory(SP);
}

//  -------------------------------------------------------------------

//  READ THE PROVIDED coolexe FILE INTO main_memory[]
void read_coolexe_file(char filename[])
{
    memset(main_memory, 0, sizeof main_memory);   //  clear all memory

    // Attempt to open file
    FILE* f = fopen(filename, "rb");
    // Check file exists
    if (f == NULL) {
        fprintf(stderr, "Error: couldn't find file \"%s\"\n", filename);
        exit(EXIT_FAILURE);
    }
    // Read content of file
    AWORD byte;
    AWORD file_contents[N_MAIN_MEMORY_WORDS]; // max buffer size is total memory
    int i = 0;
    while (1) {
        fread(&byte, 2, 1, f); // reads 2 bytes (16bit word) at a time
        if (feof(f)) break;
        //printf("Writing %i to %d\n", byte, i);
        file_contents[i] = byte;
        ++i;
    }
    fclose(f);
    memcpy(main_memory, file_contents, sizeof file_contents);
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
    printf("File successfully read into main memory.\n"); // debug

//  EXECUTE THE INSTRUCTIONS FOUND IN main_memory[]
    printf("Executing stack machine...\n\n");
    int result = execute_stackmachine();
    printf("\nresult: %i\n", result); // debug statement, eventually remove

    report_statistics();

    return result;          // or  exit(result);
}