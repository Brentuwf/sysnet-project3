#include "lizard.hpp"

/**
 * Constructs a lizard.
 *
 * @param id - the Id of the lizard 
 */
Lizard::Lizard (int id)
{
	_id = id;
}

/**
 * Returns the Id of the lizard.
 *
 * @return the Id of a lizard
 * 
 * Status: Complete - No need to change any of this code
 */
int Lizard::getId()
{
	return _id;
}

/**
 * Launches a lizard thread.
 * 
 * Status: Complete - No need to change any of this code.
 */
 void Lizard::run() 
 {
	 // launch the thread to simulate the lizard's behavior
    _aLizard = new thread ( lizardThread, this); 
 }
 
 /**
  * Waits for a lizard to finish running.
  *
  * Status: Complete - No need to change any of this code.
  */
 void Lizard::wait()
 {
	 // wait for the thread to terminate
	if (_aLizard != NULL) {
        _aLizard->join();
    } 
 }
 

/**
 * Simulate a lizard sleeping for a random amount of time
 *
 * Status: Complete - No need to change any of this code.
 */
void Lizard::sleepNow()
{
	int sleepSeconds;

	sleepSeconds = 1 + (int)(random() / (double)RAND_MAX * MAX_LIZARD_SLEEP);

	if (debug)
    {
      cout << "[" << _id << "] sleeping for " << sleepSeconds << " seconds" << endl;
      cout << flush;
    }

	sleep( sleepSeconds );

	if (debug)
    {
      cout << "[" << _id << "] awake" << endl;
      cout << flush;
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
void Lizard::sago2MonkeyGrassIsSafe()
{
	if (debug)
    {
		cout << "[" << _id << "] checking  sago -> monkey grass" << endl;
		cout << flush;
    }

	


	if (debug)
    {
		cout << "[" << _id << "] thinks  sago -> monkey grass  is safe" << endl;
		cout << flush;
    }
}


/**
 *
 * Delays for 1 second to simulate crossing from the sago to
 * the monkey grass. 
 *
 * Status: Incomplete - Make changes as you see are necessary.
 */
void Lizard::crossSago2MonkeyGrass()
{
	if (debug) {
		cout << "[" << _id << "] crossing  sago -> monkey grass" << endl;
		cout << flush;
	}

	/*
	 * One more crossing this way
	 */
	numCrossingSago2MonkeyGrass++;

	/*
	 * Check for lizards cross both ways
	 */
	if (numCrossingMonkeyGrass2Sago && UNIDIRECTIONAL) {
		cout << "\tCrash!  We have a pile-up on the concrete." << endl;
		cout << "\t" << numCrossingSago2MonkeyGrass << " crossing sago -> monkey grass" << endl;
		cout << "\t" << numCrossingMonkeyGrass2Sago << " crossing monkey grass -> sago" << endl;
		exit( -1 );
	}


	/*
	 * It takes a while to cross, so simulate it
	 */
	sleep( CROSS_SECONDS );

    /*
     * That one seems to have made it
     */
    numCrossingSago2MonkeyGrass--;
}


/**
 * Tells others they can go now
 *
 * Status: Incomplete - Make changes as you see are necessary.
 */
void Lizard::madeIt2MonkeyGrass()
{
	/*
	* Whew, made it across
	*/
	if (debug) {
		cout << "[" << _id << "] made the  sago -> monkey grass  crossing" << endl;
		cout << flush;
	}





}


/**
 * Simulate a lizard eating for a random amount of time
 *
 * Status: Complete - No need to change any of this code.
 */
void Lizard::eat()
{
	int eatSeconds;

	eatSeconds = 1 + (int)(random() / (double)RAND_MAX * MAX_LIZARD_EAT);

	if (debug) {
		cout << "[" << _id << "] eating for " << eatSeconds << " seconds" << endl;
		cout << flush;
	}

	/*
	 * Simulate eating by blocking for a few seconds
	 */
	sleep( eatSeconds );

	if (debug) {
		cout << "[" << _id << "] finished eating" << endl;
		cout << flush;
	}
}


/**
 * Returns when it is safe for this lizard to cross from the monkey
 * grass to the sago.   Should use some synchronization 
 * facilities (lock/semaphore) here.
 *
 * Status: Incomplete - Make changes as you see are necessary.
 */
void Lizard::monkeyGrass2SagoIsSafe()
{
	if (debug) {
		cout << "[" << _id << "] checking  monkey grass -> sago" << endl;
		cout << flush;
	}





	if (debug) {
		cout << "[" << _id << "] thinks  monkey grass -> sago  is safe" << endl;
		cout << flush;
	}
}



/**
 * Delays for 1 second to simulate crossing from the monkey
 * grass to the sago. 
 *
 * Status: Incomplete - Make changes as you see are necessary.
 */
void Lizard::crossMonkeyGrass2Sago()
{
	if (debug) {
		cout << "[" << _id << "] crossing  monkey grass -> sago" << endl;
		cout << flush;
	}

	/*
	 * One more crossing this way
	 */
	numCrossingMonkeyGrass2Sago++;

  
	/*
	 * Check for lizards cross both ways
	 */
	if (numCrossingSago2MonkeyGrass && UNIDIRECTIONAL) {
		cout << "\tOh No!, the lizards have cats all over them." << endl;
		cout << "\t " << numCrossingSago2MonkeyGrass << " crossing sago -> monkey grass" << endl;
		cout << "\t " << numCrossingMonkeyGrass2Sago << " crossing monkey grass -> sago" << endl;
		exit( -1 );
	}

	/*
	 * It takes a while to cross, so simulate it
	 */
	sleep( CROSS_SECONDS );

	/*
	 * That one seems to have made it
	 */
	numCrossingMonkeyGrass2Sago--;
}


/**
 *
 * Tells others they can go now
 *
 * Status: Incomplete - Make changes as you see are necessary.
 */
void Lizard::madeIt2Sago()
{
	/*
	 * Whew, made it across
	 */
	if (debug) {
		cout << "[" << _id << "] made the  monkey grass -> sago  crossing" << endl;
		cout << flush;
	}
}

/**
  * Follows the algorithm provided in the assignment
  * description to simulate lizards crossing back and forth
  * between a sago palm and some monkey grass. 
  *  
  * @param aLizard - the lizard to be executed concurrently
  *
  * @return N/A
  
  * Status: Incomplete - Make changes as you see are necessary.
  */
void Lizard::lizardThread(Lizard *aLizard)
{	
	if (debug) {
		cout << "[" << aLizard->getId() << "] lizard is alive" << endl;
		cout << flush;
	}

	while(running) {
	/* 
	 * Follow the algorithm given in the assignment
	 * using calls to the functions declared above.
	 * You'll need to complete the implementation of
	 * some functions by filling in the code.  Some  
	 * are already completed - see the comments.
	 */


















	}

}


