# CITS2002 Project 1

Due date: **11:59pm Friday 17th September (end of week 7)**

Grade weighting: **25%**

<p align="center">
  <img src="coolbook.png" width="250px" height="350"/>
</p>

Work in progress!

`runcool.c` is (will be) an emulator of a very simple 16-bit computer designed to execute programs compiled from the esoteric programming language *cool*.

To compile `runcool.c`:
```
cc -std=c11 -Wall -Werror -o runcool runcool.c
```

To run `runcool` program with a cool executable:
```
./runcool program.coolexe
```

To compile *cool* source files use the script `cool-executables/coolc.sh`:
```
./coolc.sh program.cool
```

This will output `cool-executables/program.coolexe`.  Run this command in `cool-executables/` folder to avoid clogging up the main directory.

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
 + [x] Get basic test cases
 + [x] Appreciate Chris McDonald
 + [ ] Check [this thread](https://secure.csse.uwa.edu.au/run/help2002?p=np&a=262&all=y2) on how cache handles main memory addresses.  Check off when we know the answer
    + [ ] Read a chapter on cacheing as recommended in that post
 + [x] Add names and student numbers to code comment
	+ [ ] Check how this should be formatted
 + [x] Check if compiler flags are same for gcc and clang, otherwise we got a problem
 + [x] Implement read_coolexe_file()
     + [x] Figure out how thats supposed to work
 + [x] Implement asm instructions in execute_stackmachine()
	 + [x] Implement `halt`
		+ [x] Check if starter code already has this fully implemented
	 + [x] Implement `nop`
	 + [x] Implement `add`
	 + [x] Implement `sub`
	 + [x] Implement `mult`
	 + [x] Implement `div`
	 + [x] Implement `call` (hard?)
		+ [ ] Get head around the PC and FP and SP switching for this
	 + [x] Implement `return`
	 + [x] Implement `jmp`
	 + [x] Implement `jeq` (hard?)
	 + [x] Implement `printi`
	 + [x] Implement `prints`
	 + [x] Implement `pushc`
	 + [x] Implement `pusha`
	 + [x] Implement `pushr`
	 + [x] Implement `popa`
	 + [x] Implement `popr`
 + [ ] Check if implementation works for recursive functions.  Easier to do once we have print and jeq done.
 + [ ] Implement statistics measuring
	 + [ ] Measure memory reads
	 + [ ] Measure memory writes
	 + [ ] Measure cache memory hits
	 + [ ] Measure cache memory misses
 + [ ] Figure out how cache memory plays into this.  They keep mentioning it but not explaining it (yet)
 + [ ] Write & compile some more complex *cool* test cases
 


