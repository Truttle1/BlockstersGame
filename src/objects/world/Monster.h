/*
 * Object.h
 *
 *  Created on: Jan 2, 2019
 *      Author: truttle1
 */

#ifndef OBJECTS_WORLD_Object_H_
#define OBJECTS_WORLD_Object_H_

#include "../GameObject.h"
class Monster:public GameObject {
	public:
		Monster(int x, int y, int sp);
		virtual ~Monster();
		void tick();
		void render();
		void nextGeneration();
		void nextEat();
		void nextMove();
		Rectangle getBounds();
		int getSpecies();
		bool getAlive();
		void kill();
	private:
		int species;
		bool alive = true;
		int arbitraryPopNumber;
		int age;
		int getNeighborhood();
		void killSameLocation();
		void evolve();
		Biome getBiome();
		void removeFog();
};

#endif /* OBJECTS_WORLD_Object_H_ */
