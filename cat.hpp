#pragma once
#include <thread>
#include "sharedstate.hpp"

/*
 * This class models a cat that sleep, wakes-up, checks on lizards in the driveway
 * and goes back to sleep. If the cat sees enough lizards it "plays" with them.
 */
class Cat {
	public:
		Cat (int id);
		int getId();
		void run(SharedState &state);
		void wait();
    
	private:
		static constexpr size_t MAX_LIZARD_CROSSING = 4; /* Maximum lizards crossing at once before alerting cats */
		static constexpr size_t MAX_CAT_SLEEP = 3; /* Maximum seconds for a cat to sleep */
		int       _id;        // the Id of the cat
		std::thread*   _catThread; // the thread simulating the cat
		void sleepNow(std::atomic<bool> &debug);
		static void catThread(Cat *aCat, SharedState &state); 
};
