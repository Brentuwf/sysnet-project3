#include <unistd.h>
#include <iostream>
#include <functional>
#include <thread>
#include "sharedstate.hpp"
#include "lizard.hpp"


/**
 * Constructs a lizard.
 *
 * @param id - the Id of the lizard 
 */
Lizard::Lizard(int id) { _id = id; }

/**
 * Returns the Id of the lizard.
 *
 * @return the Id of a lizard
 * 
 * Status: Complete - No need to change any of this code
 */
int Lizard::getId() { return _id; }

/**
 * Launches a lizard thread.
 * 
 * Status: Complete - No need to change any of this code.
 */
 void Lizard::run(SharedState& state) 
 {
	 // launch the thread to simulate the lizard's behavior
	_aLizard = new std::thread(lizardThread, this, std::ref(state)); 
 }
 
 /**
  * Waits for a lizard to finish running.
  *
  * Status: Complete - No need to change any of this code.
  */
 void Lizard::wait()
 {
	 // wait for the thread to terminate
	if (_aLizard != nullptr) {
        _aLizard->join();
    } 
 }
 

/**
 * Simulate a lizard sleeping for a random amount of time
 *
 * Status: Complete - No need to change any of this code.
 */
void Lizard::sleepNow(std::atomic<bool> &debug)
{
	int sleepSeconds = 1 + (int)(random() / (double)RAND_MAX * MAX_LIZARD_SLEEP);

	if (debug.load()) {
		std::cout << "[" << _id << "] sleeping for " << sleepSeconds << " seconds" << std::endl;
		std::cout << std::flush;
	}

	sleep(sleepSeconds);

	if (debug.load()) {
		std::cout << "[" << _id << "] awake" << std::endl;
		std::cout << std::flush;
	}
}



 
/**
 *
 * Returns when it is safe for this lizard to cross from the sago
 * to the monkey grass.   Should use some synchronization 
 * facilities (lock/semaphore) here.
 *
 * Status: Incomplete - Make changes as you see are necessary.
 */
void Lizard::sago2MonkeyGrassIsSafe(SharedState &state)
{
	if (state.debug.load()) {
		std::cout << "[" << _id << "] checking  sago -> monkey grass" << std::endl;
		std::cout << std::flush;
    	}

	


	if (state.debug.load()) {
		std::cout << "[" << _id << "] thinks  sago -> monkey grass  is safe" << std::endl;
		std::cout << std::flush;
    	}
}


/**
 *
 * Delays for 1 second to simulate crossing from the sago to
 * the monkey grass. 
 *
 * Status: Incomplete - Make changes as you see are necessary.
 */
void Lizard::crossSago2MonkeyGrass(SharedState &state)
{
	if (state.debug.load()) {
		std::cout << "[" << _id << "] crossing  sago -> monkey grass" << std::endl;
		std::cout << std::flush;
	}

	/*
	 * One more crossing this way
	 */
	state.numCrossingSago2MonkeyGrass++;

	/*
	 * Check for lizards cross both ways
	 */
	if (state.numCrossingMonkeyGrass2Sago.load() && UNIDIRECTIONAL) {
		std::cout << "\tCrash!  We have a pile-up on the concrete." << std::endl;
		std::cout << "\t" << state.numCrossingSago2MonkeyGrass.load() << " crossing sago -> monkey grass" << std::endl;
		std::cout << "\t" << state.numCrossingMonkeyGrass2Sago.load() << " crossing monkey grass -> sago" << std::endl;
		exit(EXIT_FAILURE);
	}


	/*
	 * It takes a while to cross, so simulate it
	 */
	sleep(CROSS_SECONDS);

	/*
	 * That one seems to have made it
	 */
	state.numCrossingSago2MonkeyGrass--;
}


/**
 * Tells others they can go now
 *
 * Status: Incomplete - Make changes as you see are necessary.
 */
void Lizard::madeIt2MonkeyGrass(SharedState &state)
{
	/*
	* Whew, made it across
	*/
	if (state.debug.load()) {
		std::cout << "[" << _id << "] made the  sago -> monkey grass  crossing" << std::endl;
		std::cout << std::flush;
	}





}


/**
 * Simulate a lizard eating for a random amount of time
 *
 * Status: Complete - No need to change any of this code.
 */
void Lizard::eat(std::atomic<bool> &debug)
{
	int eatSeconds = 1 + (int)(random() / (double)RAND_MAX * MAX_LIZARD_EAT);

	if (debug.load()) {
		std::cout << "[" << _id << "] eating for " << eatSeconds << " seconds" << std::endl;
		std::cout << std::flush;
	}

	/*
	 * Simulate eating by blocking for a few seconds
	 */
	sleep(eatSeconds);

	if (debug.load()) {
		std::cout << "[" << _id << "] finished eating" << std::endl;
		std::cout << std::flush;
	}
}


/**
 * Returns when it is safe for this lizard to cross from the monkey
 * grass to the sago.   Should use some synchronization 
 * facilities (lock/semaphore) here.
 *
 * Status: Incomplete - Make changes as you see are necessary.
 */
void Lizard::monkeyGrass2SagoIsSafe(SharedState &state)
{
	if (state.debug.load()) {
		std::cout << "[" << _id << "] checking  monkey grass -> sago" << std::endl;
		std::cout << std::flush;
	}





	if (state.debug.load()) {
		std::cout << "[" << _id << "] thinks  monkey grass -> sago  is safe" << std::endl;
		std::cout << std::flush;
	}
}



/**
 * Delays for 1 second to simulate crossing from the monkey
 * grass to the sago. 
 *
 * Status: Incomplete - Make changes as you see are necessary.
 */
void Lizard::crossMonkeyGrass2Sago(SharedState &state)
{
	if (state.debug.load()) {
		std::cout << "[" << _id << "] crossing  monkey grass -> sago" << std::endl;
		std::cout << std::flush;
	}

	/*
	 * One more crossing this way
	 */
	state.numCrossingMonkeyGrass2Sago++;

  
	/*
	 * Check for lizards cross both ways
	 */
	if (state.numCrossingSago2MonkeyGrass.load() && UNIDIRECTIONAL) {
		std::cout << "\tOh No!, the lizards have cats all over them." << std::endl;
		std::cout << "\t " << state.numCrossingSago2MonkeyGrass.load() << " crossing sago -> monkey grass" << std::endl;
		std::cout << "\t " << state.numCrossingMonkeyGrass2Sago.load() << " crossing monkey grass -> sago" << std::endl;
		exit(EXIT_FAILURE);
	}

	/*
	 * It takes a while to cross, so simulate it
	 */
	sleep(CROSS_SECONDS);

	/*
	 * That one seems to have made it
	 */
	state.numCrossingMonkeyGrass2Sago--;
}


/**
 *
 * Tells others they can go now
 *
 * Status: Incomplete - Make changes as you see are necessary.
 */
void Lizard::madeIt2Sago(SharedState &state)
{
	/*
	 * Whew, made it across
	 */
	if (state.debug.load()) {
		std::cout << "[" << _id << "] made the  monkey grass -> sago  crossing" << std::endl;
		std::cout << std::flush;
	}
}

/**
  * Follows the algorithm provided in the assignment
  * description to simulate lizards crossing back and forth
  * between a sago palm and some monkey grass. 
  *  
  * @param aLizard - the lizard to be executed concurrently
  *
  * Status: Incomplete - Make changes as you see are necessary.
  */
void Lizard::lizardThread(Lizard *aLizard, SharedState& state)
{	
	if (state.debug.load()) {
		std::cout << "[" << aLizard->getId() << "] lizard is alive" << std::endl;
		std::cout << std::flush;
	}

	while(state.running.load()) {
	/* 
	 * Follow the algorithm given in the assignment
	 * using calls to the functions declared above.
	 * You'll need to complete the implementation of
	 * some functions by filling in the code.  Some  
	 * are already completed - see the comments.
	 */


















	}

}


