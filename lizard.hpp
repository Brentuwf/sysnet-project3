#pragma once
#include <thread>
#include "sharedstate.hpp"

class Lizard {
	public:
		Lizard(int id);
		int getId();
		void run(SharedState &state);
		void wait();

	private:
		static constexpr size_t MAX_LIZARD_SLEEP = 3; /* Maximum seconds for a lizard to sleep */
		static constexpr size_t MAX_LIZARD_EAT = 5; /* Maximum seconds for a lizard to eat */
		static constexpr size_t CROSS_SECONDS = 2; /* number of seconds it takes to cross the driveway */
		/*
		 * Make this 1 to check for lizards travelling in both directions
		 * Leave it 0 to allow bidirectional travel
		 */
		static constexpr bool UNIDIRECTIONAL = 0;
		int     _id;      // the Id of the lizard
		std::thread* _aLizard; // the thread simulating the lizard
		void sago2MonkeyGrassIsSafe(SharedState &state);
		void crossSago2MonkeyGrass(SharedState &state);
		void madeIt2MonkeyGrass(SharedState &state);
		void eat(std::atomic<bool> &debug);
		void monkeyGrass2SagoIsSafe(SharedState &state);
		void crossMonkeyGrass2Sago(SharedState &state);
		void madeIt2Sago(SharedState &state);
		void sleepNow(std::atomic<bool> &debug);
		static void lizardThread(Lizard *aLizard, SharedState& state);
};

