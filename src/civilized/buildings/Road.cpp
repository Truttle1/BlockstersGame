/*
 * Residential.cpp
 *
 *  Created on: Jun 27, 2019
 *      Author: truttle1
 */

#include "Road.h"

Road::Road(int ix, int iy)  : Building(ix,iy)
{
	name = BUILDING;
	buildingType = ROAD;
	traffic = 0;
	maxTraffic = 2;
}

Road::~Road()
{
}

void Road::render()
{
	DrawRectangle(x,y,8,8,{128,64,0,255});
	if(getTraffic() > 0.2)
	{
		DrawTextureEx(Species::monsterSpecies[Civilizations::states[getOwner()].monster].image,{static_cast<float>(x),static_cast<float>(y)},0.0,0.5,WHITE);
	}
	if(getTraffic() > 0.5)
	{
		DrawTextureEx(Species::monsterSpecies[Civilizations::states[getOwner()].monster].image,{static_cast<float>(x+4),static_cast<float>(y+4)},0.0,0.5,WHITE);
	}
	if(getTraffic() > 1)
	{
		DrawTextureEx(Species::monsterSpecies[Civilizations::states[getOwner()].monster].image,{static_cast<float>(x+4),static_cast<float>(y)},0.0,0.5,WHITE);
		DrawTextureEx(Species::monsterSpecies[Civilizations::states[getOwner()].monster].image,{static_cast<float>(x),static_cast<float>(y+4)},0.0,0.5,WHITE);
	}
}

void Road::nextEat()
{

}

void Road::moreTraffic(int amount)
{
	traffic += amount;
}

void Road::setMaxTraffic(int amount)
{
	maxTraffic = amount;
}

void Road::lessenTraffic(int amount)
{
	traffic -= amount;
}

double Road::getTraffic()
{
	return traffic / static_cast<double>(maxTraffic);
}

void Road::nextGeneration()
{
	CivHandler::spend(0.1);
}

void Road::nextMove()
{

}

void Road::tick()
{
	if(getClicking() && isPlayer())
	{
		demolish();
	}
}

void Road::finalize()
{

}
