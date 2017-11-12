/**
  * ECE254 Linux Dynamic Memory Management Lab
  * @file: main_test.c
  * @brief: The main file to write tests of memory allocation algorithms
  */ 

/* includes */
/* system provided header files. You may add more */
#include <stdio.h>

/* non-system provided header files. 
   Do not include more user-defined header files here
 */
#include "mem.h"



int main(int argc, char *argv[])
{

	best_fit_memory_init(1024);	// initialize 1KB, best fit

	//please go ahead and de-comment a test to run it!

	//worst_fit_memory_init(1024);
	//testlinkedlist();
	//testFull();
	//randomWorstAlloc();
	//randomBestAlloc();
    //testFragmentation();


	return 0;
}
