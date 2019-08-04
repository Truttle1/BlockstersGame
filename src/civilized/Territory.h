/*
 * Residential.h
 *
 *  Created on: Jun 27, 2019
 *      Author: truttle1
 */

#ifndef CIVILIZED_TERRITORY_H_
#define CIVILIZED_TERRITORY_H_
#include "../objects/GameObject.h"
#include "Civilizations.h"
#include "ui/CityUI.h"
#include "../GameWindow.h"
#include "CivHandler.h"
#include "ui/CityItems.h"
#include "buildings/Road.h"
#include "buildings/Residential.h"
#include "buildings/Farm.h"

class Territory : public GameObject
{
public:
	Territory(int ix, int iy);
	virtual ~Territory();
	void tick();
	void render();
	void nextGeneration();
	void nextMove();
	void nextEat();
	virtual Rectangle getBounds();
	void setOwner(int iOwner, bool iTribe);
	void expand();
	bool getClicking();
	int getOwner();
	bool isTribal();

private:
	int owner;
	bool occupied;
	int getCurrentSelection();
	bool isPlayer();
	bool checkIfOccupied();
	bool tribe;

};

#endif /* CIVILIZED_BUILDINGS_RESIDENTIAL_H_ */
