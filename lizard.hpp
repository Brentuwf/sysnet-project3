#pragma once
#include <thread>

class Lizard {
	public:
		Lizard(int id, bool &debug);
		int getId();
		void run(bool &running);
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
		bool &debug;
		void sago2MonkeyGrassIsSafe();
		void crossSago2MonkeyGrass();
		void madeIt2MonkeyGrass();
		void eat();
		void monkeyGrass2SagoIsSafe();
		void crossMonkeyGrass2Sago();
		void madeIt2Sago();
		void sleepNow();
		static void lizardThread(Lizard *aLizard, bool &running);
	
};

