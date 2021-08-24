# CITS2002 Project 1

Due date: **11:59pm Friday 17th September (end of week 7)**

Grade weighting: **25%**

<p align="center">
  <img src="coolbook.png" width="250px" height="350"/>
</p>

Work in progress!

`runcool.c` is (will be) an emulator of a very simple 16-bit computer designed to execute programs compiled from the esoteric programming language *cool*.

Compile with:
```
cc -std=c11 -Wall -Werror -o runcool runcool.c
```


## Useful Links

Project info:
 + [project explanation](http://teaching.csse.uwa.edu.au/units/CITS2002/projects/project1.php)
 + [project clarifications](http://teaching.csse.uwa.edu.au/units/CITS2002/projects/project1-clarifications.php)

*cool* language info:
 + [cool syntax](http://teaching.csse.uwa.edu.au/units/CITS2002/projects/coolsyntax.php)
 + [cool instruction set](http://teaching.csse.uwa.edu.au/units/CITS2002/projects/coolinstructions.php)
 + [cool compiler & test files](https://secure.csse.uwa.edu.au/run/coolc)

Misc.: 
 + [help2002](https://secure.csse.uwa.edu.au/run/help2002)
 + [submission location](https://secure.csse.uwa.edu.au/run/cssubmit) (only one member needs to submit)

## Todo

 + [x] Create starter todo list
 + [x] Get test cases
 + [ ] Add names and student numbers to code comment
 + [ ] Implement read_coolexe_file()
     + [ ] Figure out how thats supposed to work
 + [ ] Implement asm instructions in execute_stackmachine()
	 + [ ] Implement halt
	 + [ ] Implement nop
	 + [ ] Implement add
	 + [ ] Implement sub
	 + [ ] Implement mult
	 + [ ] Implement div
	 + [ ] Implement call (hard?)
	 + [ ] Implement return
	 + [ ] Implement jmp
	 + [ ] Implement jeq (hard?)
	 + [ ] Implement printi
	 + [ ] Implement prints
	 + [ ] Implement pushc
	 + [ ] Implement pusha
	 + [ ] Implement pushr
	 + [ ] Implement popa
	 + [ ] Implement popr
 + [ ] Implement statistics measuring
	 + [ ] Measure memory reads
	 + [ ] Measure memory writes
	 + [ ] Measure cache memory hits
	 + [ ] Measure cache memory misses
 + [ ] Figure out how cache memory plays into this.  They keep mentioning it but not explaining it (yet)
 + [ ] Write & compile some more complex *cool* test cases
 


