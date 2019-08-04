/*
 * Building.cpp
 *
 *  Created on: Jun 27, 2019
 *      Author: truttle1
 */

#include "../buildings/Building.h"

Building::Building(int ix, int iy)  : GameObject(ix,iy,8,8)
{
	name = BUILDING;
	building = true;
}

Building::~Building()
{
	// TODO Auto-generated destructor stub
}

Rectangle Building::getBounds()
{
	Rectangle r;
	r.x = x;
	r.y = y;
	r.height = 8;
	r.width = 8;
	return r;
}

void Building::setOwner(int iOwner)
{
	owner = iOwner;
}

int Building::getOwner()
{
	return owner;
}

bool Building::isPlayer()
{
	return !Species::monsterSpecies[Civilizations::states[owner].monster].enemy;
}

bool Building::getDemolished()
{
	return demolished;
}

void Building::demolish()
{
	if(CivHandler::getDolurz() >= 10 && getCurrentSelection() == CityItems::BULLDOZER)
	{
		demolished = true;
		CivHandler::removeDolurz(10);
		finalize();
	}
}

bool Building::adjacent(GameObject* object)
{
	if(object->getX() == x-8 || object->getX() == x+8 || object->getX() == x)
	{
		if(object->getY() == y-8 || object->getY() == y+8 || object->getY() == y)
		{
			return true;
		}
	}
	return false;
}

int Building::getCurrentSelection()
{
	std::vector<CityButton> buttons = CivHandler::getCityUI().getCityButtons();
	for(unsigned i = 0; i < buttons.size(); i++)
	{
		if(buttons[i].getStatus() == 1)
		{
			return i;
		}
	}
	return -1;
}


bool Building::getClicking()
{

	bool clicking = false;
	if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
	{
		int mx = -1;
		int my = -1;
		if(CivHandler::getCameraZoom() != 0)
		{

			mx = GetMouseX() / CivHandler::getCameraZoom() - CivHandler::getOffsetX() / CivHandler::getCameraZoom();
			my = GetMouseY() / CivHandler::getCameraZoom() - CivHandler::getOffsetY() / CivHandler::getCameraZoom();
		}
		mouseX = mx;
		mouseY = my;
		clicking = (mx >= x+1 && my >= y+1 && mx <= x+width-2 && my <= y+height-2);
		if(clicking && GetMouseX() < 480 && GetMouseY() < 352)
		{
			clickedHere = true;
		}
		else if(GetMouseX() < 480 && GetMouseY() < 352)
		{
			clickedHere = false;
		}
	}
	return clicking;
}

int Building::distanceToBuilding(BuildingType build)
{
	int lowestDistance = 9999999;
	for(unsigned i = 0; i < objects.size(); i++)
	{
		int distance = std::sqrt(std::pow(std::abs(x - objects[i]->getX()),2) + std::pow(std::abs(y - objects[i]->getY()),2));
		if(distance < lowestDistance && objects[i]->getBuilding() == build)
		{
			lowestDistance = distance;
		}
	}
	return lowestDistance;
}

Building* Building::nearestBuilding(BuildingType build)
{
	Building* building;
	int lowestDistance = 9999999;
	for(unsigned i = 0; i < objects.size(); i++)
	{
		int distance = std::sqrt(std::pow(std::abs(x - objects[i]->getX()),2) + std::pow(std::abs(y - objects[i]->getY()),2));;
		if(distance < lowestDistance && objects[i]->getBuilding() == build)
		{
			lowestDistance = distance;
			building = static_cast<Building*>(objects[i]);
		}
	}
	return building;
}

std::vector<GameObject*> Building::getAdjacent(BuildingType build)
{
	std::vector<GameObject*> retVal;
	for(unsigned i = 0; i < objects.size(); i++)
	{
		GameObject* object = objects[i];
		if(object->getX() == x-8 || object->getX() == x+8 || object->getX() == x)
		{
			if(object->getY() == y-8 || object->getY() == y+8 || object->getY() == y)
			{
				if(object->getBuilding() == build)
				{
					retVal.push_back(object);
				}
			}
		}
	}
	return retVal;
}
