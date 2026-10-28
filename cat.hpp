#pragma once
/*
 * This class models a cat that sleep, wakes-up, checks on lizards in the driveway
 * and goes back to sleep. If the cat sees enough lizards it "plays" with them.
 */
class Cat {
	
	int       _id;        // the Id of the cat
	thread*   _catThread; // the thread simulating the cat
	
	public:
		Cat (int id, bool debug);
		int getId();
		void run();
		void wait();
    
	private:
		bool isdebug;
		void sleepNow();

        static void catThread (Cat *aCat); 
};
