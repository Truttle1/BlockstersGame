/*
 * Residential.h
 *
 *  Created on: Jun 27, 2019
 *      Author: truttle1
 */

#ifndef CIVILIZED_BUILDINGS_ROAD_H_
#define CIVILIZED_BUILDINGS_ROAD_H_
#include "Building.h"

class Road : public Building
{
public:
	Road(int ix, int iy);
	virtual ~Road();
	void tick();
	void render();
	void nextGeneration();
	void nextMove();
	void nextEat();
	void finalize();
	void setMaxTraffic(int amount);
	void moreTraffic(int amount);
	void lessenTraffic(int amount);
	double getTraffic();

private:
	int traffic;
	int maxTraffic;


};

#endif /* CIVILIZED_BUILDINGS_RESIDENTIAL_H_ */
