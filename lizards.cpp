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

#include <unistd.h>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <atomic>
#include <thread>
#include <mutex>
#include <vector>
#include <memory>

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
 * Make this 1 to check for lizards travelling in both directions
 * Leave it 0 to allow bidirectional travel
 */
static constexpr bool UNIDIRECTIONAL = 0;

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
 * Maximum seconds for a lizard to sleep
 */
static constexpr size_t MAX_LIZARD_SLEEP = 3;

/*
 * Maximum seconds for a cat to sleep
 */
static constexpr size_t MAX_CAT_SLEEP = 3;

/*
 * Maximum seconds for a lizard to eat
 */
static constexpr size_t MAX_LIZARD_EAT = 5;

/*
 * Number of seconds it takes to cross the driveway
 */
static constexpr size_t CROSS_SECONDS = 2;


/*
 * Declare global variables here
 */


/**************************************************/
/* Please leave these variables alone.  They are  */
/* used to check the proper functioning of your   */
/* program.  They should only be used in the code */
/* I have provided.                               */
/**************************************************/
std::atomic<size_t> numCrossingSago2MonkeyGrass;
std::atomic<size_t> numCrossingMonkeyGrass2Sago;
std::atomic<bool> debug;
std::atomic<bool> running;
/**************************************************/



/**
 * This class models a cat that sleep, wakes-up, checks on lizards in the driveway
 * and goes back to sleep. If the cat sees enough lizards it "plays" with them.
 */
class Cat {
	
	int       _id;        // the Id of the cat
	std::thread*   _catThread; // the thread simulating the cat
	
	public:
		Cat (int id);
		int getId();
		void run();
		void wait();
    
	private:
		void sleepNow();

		static void catThread (Cat *aCat); 
};

/**
 * Constructs a cat.
 *
 * @param id - the Id of the cat 
 */
Cat::Cat (int id)
{
	_id = id;
}

/**
 * Returns the Id of the cat.
 *
 * @return the Id of a cat
 */
int Cat::getId()
{
	return _id;
}


/**
 * Launches a cat thread.
 * 
 * Status: Incomplete - Make changes to this code.
 */
 void Cat::run() 
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
void Cat::sleepNow()
{
	int sleepSeconds;

	sleepSeconds = 1 + (int)(random() / (double)RAND_MAX * MAX_CAT_SLEEP);

	if (debug.load()) 
		std::fprintf(stdout, "[%d] cat sleeping for %d seconds\n", _id, sleepSeconds); // BA

	sleep(sleepSeconds);

	if (debug.load()) 
		std::fprintf(stdout, "[%d] cat awake\n", _id); // BA
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
void Cat::catThread(Cat *aCat)
{
	
	if (debug.load()) 
		std::fprintf(stdout, "[%d] cat is alive\n", aCat->getId()); // BA

	while(running.load()) {
		aCat->sleepNow();



		/*
		 * Check for too many lizards crossing
		 */
		if (numCrossingSago2MonkeyGrass.load() + numCrossingMonkeyGrass2Sago.load() > MAX_LIZARD_CROSSING) {
			std::fprintf(stdout, "\tThe cats are happy - they have toys.\n"); // BA
			exit(EXIT_FAILURE);
		}
	}
}

 

class Lizard {
	int     _id;      // the Id of the lizard
	std::thread* _aLizard; // the thread simulating the lizard

	public:
		Lizard(int id);
		int getId();
		void run();
		void wait();

	private:
		void sago2MonkeyGrassIsSafe();
		void crossSago2MonkeyGrass();
		void madeIt2MonkeyGrass();
		void eat();
		void monkeyGrass2SagoIsSafe();
		void crossMonkeyGrass2Sago();
		void madeIt2Sago();
		void sleepNow();

		static void lizardThread(Lizard *aLizard);
	
};


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
	_aLizard = new std::thread(lizardThread, this); 
 }
 
 /**
  * Waits for a lizard to finish running.
  *
  * Status: Complete - No need to change any of this code.
  */
 void Lizard::wait()
 {
	 // wait for the thread to terminate
	if (_aLizard != NULL) 
		_aLizard->join();
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

	if (debug.load()) 
		std::fprintf(stdout,"[%d] sleeping for %d seconds\n", _id, sleepSeconds); // BA

	sleep(sleepSeconds);

	if (debug.load()) 
		std::fprintf(stdout, "[%d] awake\n", _id); // BA
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
	if (debug.load()) 
		std::fprintf(stdout, "[%d] checking sago -> monkey grass\n", _id); // BA

	


	if (debug.load()) 
		std::fprintf(stdout, "[%d] thinks sago -> monkey grass is safe\n", _id); // BA
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
	if (debug.load()) 
		std::fprintf(stdout, "[%d] crossing sago -> monkey grass\n", _id); // BA

	/*
	 * One more crossing this way
	 */
	numCrossingSago2MonkeyGrass++;

	/*
	 * Check for lizards cross both ways
	 */
	if (numCrossingMonkeyGrass2Sago.load() && UNIDIRECTIONAL) {
		std::fprintf(stdout, "\tCrash!  We have a pile-up on the concrete.\n"); // BA
		std::fprintf(stdout, "\t%zu crossing sago -> monkey grass\n", numCrossingSago2MonkeyGrass.load()); // BA
		std::fprintf(stdout, "\t%zu crossing monkey grass -> sago\n", numCrossingMonkeyGrass2Sago.load()); // BA
		exit(EXIT_FAILURE);
	}


	/*
	 * It takes a while to cross, so simulate it
	 */
	sleep(CROSS_SECONDS);

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
	if (debug.load()) 
		std::fprintf(stdout,  "[%d] made the sago -> monkey grass crossing/n", _id); // BA





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

	if (debug.load()) 
		std::fprintf(stdout, "[%d] eating for %d seconds\n", _id, eatSeconds); // BA

	/*
	 * Simulate eating by blocking for a few seconds
	 */
	sleep(eatSeconds);

	if (debug.load()) 
		std::fprintf(stdout, "[%d] finished eating\n", _id); // BA
	
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
	if (debug.load()) 
		std::fprintf(stdout, "[%d] checking monkey grass -> sago\n", _id); // BA





	if (debug.load()) 
		std::fprintf(stdout, "[%d] thinks monkey grass -> sago is safe\n", _id); // BA
}



/**
 * Delays for 1 second to simulate crossing from the monkey
 * grass to the sago. 
 *
 * Status: Incomplete - Make changes as you see are necessary.
 */
void Lizard::crossMonkeyGrass2Sago()
{
	if (debug.load()) 
		std::fprintf(stdout, "[%d] crossing monkey grass -> sago\n", _id); // BA

	/*
	 * One more crossing this way
	 */
	numCrossingMonkeyGrass2Sago++;

  
	/*
	 * Check for lizards cross both ways
	 */
	if (numCrossingSago2MonkeyGrass.load() && UNIDIRECTIONAL) {
		std::fprintf(stdout, "\tOh No!, the lizards have cats all over them.\n"); // BA
		std::fprintf(stdout, "\t%zu crossing sago -> monkey grass\n", numCrossingSago2MonkeyGrass.load()); // BA
		std::fprintf(stdout, "\t%zu crossing monkey grass -> sago\n", numCrossingMonkeyGrass2Sago.load()); // BA
		exit(EXIT_FAILURE);
	}

	/*
	 * It takes a while to cross, so simulate it
	 */
	sleep(CROSS_SECONDS);

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
	if (debug.load()) 
		std::fprintf(stdout, "[%d] made the monkey grass -> sago crossing\n", _id); // BA
	
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
	if (debug) 
		std::fprintf(stdout, "[%d] lizard is alive\n", aLizard->getId()); // BA
	

	while(running.load()) {
	/* 
	 * Follow the algorithm given in the assignment
	 * using calls to the functions declared above.
	 * You'll need to complete the implementation of
	 * some functions by filling in the code.  Some  
	 * are already completed - see the comments.
	 */


















	}

}
 



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
	/*
	 * Declare local variables
	 */




	/*
	 * Check for the debugging flag (-d)
	 */
	debug = 0;
	if (argc > 1)
		if (std::strncmp(argv[1], "-d", 2) == 0)
			debug = true;


	/*
	 * Initialize variables
	 * Modified BA, used boolean for running
	 * load() not used due to update note being in critical section
	 */
	numCrossingSago2MonkeyGrass = 0;
	numCrossingMonkeyGrass2Sago = 0;
	running = true;


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
		allLizards.at(i)->run();

	for (size_t i = 0; i < NUM_CATS; ++i) 
		allCats.at(i)->run();

	/*
	 * Now let the world run for a while
	 */
	sleep(WORLDEND);


	/*
	 * That's it - the end of the world
	 */
	running.store(false);


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
