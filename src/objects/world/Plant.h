/*
 * Plant.h
 *
 *  Created on: Jan 2, 2019
 *      Author: truttle1
 */

#ifndef OBJECTS_WORLD_PLANT_H_
#define OBJECTS_WORLD_PLANT_H_

#include "../GameObject.h"
#include "../../species/Species.h"
#include "Ground.h"
#include "../../img/ObjectColors.h"
class Plant:public GameObject
{
	public:
		Plant(int x, int y, int sp);
		virtual ~Plant();
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
		Color color;
		int arbitraryPopNumber;
		int age;

		int getNeighborhood();
		void killSameLocation();
		void evolve();
		Biome getBiome();
		void removeFog();
};

#endif /* OBJECTS_WORLD_PLANT_H_ */
