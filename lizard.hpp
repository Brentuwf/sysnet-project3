#pragma once

class Lizard {
	int     _id;      // the Id of the lizard
	thread* _aLizard; // the thread simulating the lizard

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

