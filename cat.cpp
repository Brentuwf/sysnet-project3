#include <unistd.h>
#include <iostream>
#include <thread>
#include "sharedstate.hpp"
#include "cat.hpp"

/**
 * Constructs a cat.
 *
 * @param id - the Id of the cat 
 */
Cat::Cat (int id) { _id = id; }

/**
 * Returns the Id of the cat.
 *
 * @return the Id of a cat
 */
int Cat::getId() { return _id; }

/**
 * Launches a cat thread.
 * 
 * Status: Incomplete - Make changes to this code.
 */
 void Cat::run(SharedState &state) 
 {
	 // launch the thread to simulate the cat's behavior	 
	 
 }
 
 /**
  * Waits for a cat to finish running.
  *
  * Status: Incomplete - Make changes to this code.
  */
 void Cat::wait()
 {
	 // wait for the thread to terminate
 }
 
 
/**
 * Simulate a cat sleeping for a random amount of time
 *
 *
 * @return N/A
 *
 * Status: Complete - No need to change any of this code.
 */
void Cat::sleepNow(std::atomic<bool> &debug)
{
	int sleepSeconds = 1 + (int)(random() / (double)RAND_MAX * MAX_CAT_SLEEP);

	if (debug.load()) {
		std::cout << "[" << _id << "] cat sleeping for " << sleepSeconds << " seconds" << std::endl;
		std::cout << std::flush;
	}

	sleep(sleepSeconds);

	if (debug.load()) {
		std::cout << "[" << _id << "] cat awake" << std::endl;
		std::cout << std::flush;
	}
}

/**
  *
  * This simulates a cat that is sleeping and occasionally checking on
  * the driveway on lizards.
  * 
  * @param aCat - a cat that is being run concurrently
  * 
  * @return - N/A
  *
  * Status: Incomplete - Make changes as you see are necessary.
  */
void Cat::catThread(Cat *aCat, SharedState &state)
{
	
	if (state.debug.load()) {
		std::cout << "[" << aCat->getId() << "] cat is alive\n";
		std::cout << std::flush;
	}

	while(state.running.load()) {
		aCat->sleepNow(state.debug);



		/*
		 * Check for too many lizards crossing
		 */
		if (state.numCrossingSago2MonkeyGrass.load() + state.numCrossingMonkeyGrass2Sago.load() > MAX_LIZARD_CROSSING) {
			std::cout << "\tThe cats are happy - they have toys.\n";
			exit(EXIT_FAILURE);
		}
    }
}

