/***************************************************************/
/*                                                             */
/* lizard.cpp                                                  */
/*                                                             */
/* To compile, you need all the files listed below             */
/*   lizard.cpp                                                */
/*                                                             */
/* Be sure to use the -lpthread option for the compile command */
/*   g++ -g -Wall -std=c++11 lizard.cpp -o lizard -pthread     */
/*                                                             */
/* Execute with the -d command-line option to enable debugging */
/* output.  For example,                                       */
/*   ./lizard -d                                               */
/*                                                             */
/***************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include <iostream>
#include <thread>
#include <mutex>
#include <vector>
#include <atomic>
#include <memory>

#include "sharedstate.hpp"
#include "lizard.hpp"
#include "cat.hpp"

/*
 * This is a stub file.  It contains very little code and what
 * it does contain may need to be altered or removed.  It is
 * only provided for a starting point.
 *
 * The comments are probably useful.
 */


/*
 * Define "constant" values here
 */
/*
 * Set this to the number of seconds you want the lizard world to
 * be simulated.  
 * Try 30 for development and 120 for more thorough testing.
 */
static constexpr size_t WORLDEND = 30;

/*
 * Number of lizard threads to create
 */
static constexpr size_t NUM_LIZARDS = 20;

/*
 * Number of cat threads to create
 */
static constexpr size_t NUM_CATS = 2;

/*	
 * Maximum lizards crossing at once before alerting cats
 */
static constexpr size_t MAX_LIZARD_CROSSING = 4;

/*
 * Maximum seconds for a cat to sleep
 */
static constexpr size_t MAX_CAT_SLEEP = 3;


/*
 * Declare global variables here
 */

/*
 * main()
 *
 * Should initialize variables, locks, semaphores, etc.
 * Should start the cat thread and the lizard threads
 * Should block until all threads have terminated
 * Status: Incomplete - Make changes to this code.
 */
int main(int argc, char **argv)
{
	SharedState sharedState;
	/*
	 * Declare local variables
	 */




	/*
	 * Check for the debugging flag (-d)
	 */
	sharedState.debug.store(false);
	if (argc > 1)
		if (strncmp(argv[1], "-d", 2) == 0)
			sharedState.debug.store(true);


	/*
	 * Initialize variables
	 */
	sharedState.numCrossingSago2MonkeyGrass.store(0);
	sharedState.numCrossingMonkeyGrass2Sago.store(0);
	sharedState.running.store(true);


	/*
	 * Initialize random number generator
	 */
	srandom((unsigned int)time(NULL));


	/*
	 * Initialize locks and/or semaphores
	 */




	/*
	 * Create NUM_LIZARDS lizard threads
	 */
	std::vector<std::unique_ptr<Lizard>> allLizards;
	for (size_t i = 0; i < NUM_LIZARDS; ++i) 
		allLizards.emplace_back(new Lizard(i));
    

	/*
	 * Create NUM_CATS cat threads
	 */
	std::vector<std::unique_ptr<Cat>> allCats;
	for (size_t i = 0; i < NUM_CATS; ++i) 
		allCats.emplace_back(new Cat(i));
	
	 

	/*
	 * Run NUM_LIZARDS and NUM_CATS threads
	 */
	for (size_t i = 0; i < NUM_LIZARDS; ++i) 
		allLizards.at(i)->run(sharedState);

	for (size_t i = 0; i < NUM_CATS; ++i) 
		allCats.at(i)->run();

	/*
	 * Now let the world run for a while
	 */
	sleep(WORLDEND);


	/*
	 * That's it - the end of the world
	 */
	sharedState.running.store(0);

	/*
	 * Wait until all threads terminate
	 */
	for (size_t i = 0; i < NUM_LIZARDS; ++i) 
		allLizards.at(i)->wait();

	for (size_t i = 0; i < NUM_CATS; ++i) 
		allCats.at(i)->wait();






	/*
	 * Delete the locks and semaphores
	 */
	 
	 
	 
	/*
	 * Delete all cat and lizard objects
	 * We are using unique pointer not necessary
	 */
 



	/*
	 * Exit happily
	 */
	return EXIT_SUCCESS;
}
