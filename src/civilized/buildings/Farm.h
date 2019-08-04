/*
 * Residential.h
 *
 *  Created on: Jun 27, 2019
 *      Author: truttle1
 */

#ifndef CIVILIZED_BUILDINGS_FARM_H_
#define CIVILIZED_BUILDINGS_FARM_H_
#include "Building.h"

class Farm : public Building
{
public:
	Farm(int ix, int iy);
	virtual ~Farm();
	void tick();
	void render();
	void nextGeneration();
	void nextMove();
	void nextEat();
	bool isEmpty();
	bool almostEmpty();
	void lowerCapacity(int amount);
	void raiseCapacity(int amount);
	void finalize();
	void loadFromFile(int iCapacity);
	int getCapacity();

private:
	static bool loadedImages;
	static Texture2D farm;
	int capacity;
	int maxCapacity;

};

#endif /* CIVILIZED_BUILDINGS_RESIDENTIAL_H_ */
