/*
 * Building.h
 *
 *  Created on: Jun 27, 2019
 *      Author: truttle1
 */

#ifndef CIVILIZED_BUILDINGS_BUILDING_H_
#define CIVILIZED_BUILDINGS_BUILDING_H_
#include "../../objects/GameObject.h"
#include <vector>
#include "../ui/CityButton.h"
#include "../ui/CityItems.h"
#include "../CivHandler.h"
#include <cstdlib>
#include <algorithm>
#include <math.h>
class Building : public GameObject
{
public:
	Building(int ix, int iy);
	virtual ~Building();
	virtual void tick()=0;
	virtual void render()=0;
	virtual void nextGeneration()=0;
	virtual void nextMove()=0;
	virtual void nextEat()=0;
	virtual void finalize()=0;
	virtual Rectangle getBounds();
	void demolish();
	bool getDemolished();
	int getOwner();
	void setOwner(int iOwner);
	int distanceToBuilding(BuildingType build);
	Building* nearestBuilding(BuildingType build);

protected:
	int owner;
	bool demolished = false;
	int getCurrentSelection();
	bool getClicking();
	bool isPlayer();
	bool adjacent(GameObject* object);
	std::vector<GameObject*> getAdjacent(BuildingType build);
};

#endif /* CIVILIZED_BUILDINGS_BUILDING_H_ */
