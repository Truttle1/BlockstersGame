/*
 * Residential.h
 *
 *  Created on: Jun 27, 2019
 *      Author: truttle1
 */

#ifndef CIVILIZED_BUILDINGS_RESIDENTIAL_H_
#define CIVILIZED_BUILDINGS_RESIDENTIAL_H_
#include "Building.h"
#include "Farm.h"
#include "Road.h"

class Residential : public Building
{
public:
	Residential(int ix, int iy);
	virtual ~Residential();
	void tick();
	void render();
	void nextGeneration();
	void nextMove();
	void nextEat();
	void finalize();
	static void setImages(Texture2D iTeepee, Texture2D iHouse);
	void setPopulation(int pop);
	int getPopulation();

private:
	static Texture2D teepee;
	static Texture2D house;
	static bool loadedImages;
	int landValue;
	int maxPop = 20;
	int population;
	int populationDifference;
	bool hasRoad;
	bool hasFarm;
	Farm* myFarm;
	int farmDistance;
	Road* myRoad;
	bool starving;
	bool trafficJam;
	int trafficAddition;

};

#endif /* CIVILIZED_BUILDINGS_RESIDENTIAL_H_ */
