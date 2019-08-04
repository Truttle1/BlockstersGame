/*
 * Residential.cpp
 *
 *  Created on: Jun 27, 2019
 *      Author: truttle1
 */

#include "Farm.h"

Texture2D Farm::farm;
bool Farm::loadedImages;

Farm::Farm(int ix, int iy)  : Building(ix,iy)
{
	name = BUILDING;
	buildingType = FARM;
	capacity = 10;
	maxCapacity = 10;
}

Farm::~Farm()
{
}

void Farm::render()
{
	//DrawRectangle(x,y,8,8,{25*capacity,25*capacity,25*capacity,255});
	DrawTexture(farm,x,y,WHITE);
}

void Farm::nextEat()
{

}

void Farm::loadFromFile(int iCapacity)
{
	capacity = iCapacity;
}

int Farm::getCapacity()
{
	return capacity;
}

void Farm::nextGeneration()
{
	CivHandler::spend(1);
}

void Farm::nextMove()
{

}

void Farm::lowerCapacity(int amount)
{
	capacity -= amount;
}

void Farm::raiseCapacity(int amount)
{
	capacity += amount;
}

bool Farm::isEmpty()
{
	if(capacity < 0)
	{
		capacity = 0;
	}
	return capacity <= 0;
}

bool Farm::almostEmpty()
{
	return capacity <= maxCapacity/5;
}

void Farm::finalize()
{

}

void Farm::tick()
{
	if(!loadedImages)
	{
		loadedImages = true;
		farm = LoadTexture("src/img/city/farm.png");
	}
	if(getClicking() && isPlayer())
	{
		demolish();
	}
}
