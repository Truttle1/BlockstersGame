/*
 * Residential.cpp
 *
 *  Created on: Jun 27, 2019
 *      Author: truttle1
 */

#include "Residential.h"

Texture2D Residential::house;
Texture2D Residential::teepee;
bool Residential::loadedImages = false;

Residential::Residential(int ix, int iy) : Building(ix,iy)
{
	landValue = 1;
	population = 0;
	buildingType = RES;
	populationDifference = 0;
	hasRoad = false;
	hasFarm = false;
	myFarm = nullptr;
	myRoad = nullptr;
	farmDistance = 0;
	starving = false;
	trafficJam = false;
}

Residential::~Residential()
{

}

void Residential::nextEat()
{

}

void Residential::nextGeneration()
{
	for(unsigned i = 0; i < objects.size(); i++)
	{
		if(objects[i]->getBuilding() == ROAD)
		{
			if(adjacent(objects[i]) && !hasRoad && population > 0)
			{
				hasRoad = true;
				landValue += 1;
				myRoad = static_cast<Road*>(objects[i]);
				trafficAddition = (population/20)+1;
				myRoad->moreTraffic(1);
			}
		}
	}
	if(hasRoad && rand()%10 < 5 && population > 0)
	{
		myRoad->lessenTraffic(trafficAddition);
		std::vector<GameObject*> roads = getAdjacent(ROAD);
		myRoad = static_cast<Road*>(roads[rand()%roads.size()]);
		trafficAddition = (population/20)+1;
		myRoad->moreTraffic(trafficAddition);
	}

	if(hasRoad && !adjacent(myRoad))
	{
		hasRoad = false;
		landValue -= 1;
	}

	if(hasRoad && myRoad->getTraffic() >= 1 && !trafficJam)
	{
		landValue -= 1;
		trafficJam = true;
	}

	if(hasRoad && myRoad->getTraffic() < 1 && trafficJam)
	{
		landValue += 1;
		trafficJam = false;
	}

	if(hasFarm && distanceToBuilding(FARM) > farmDistance)
	{
		landValue -= 1;
		hasFarm = false;
		myFarm = nullptr;
	}

	if(!starving && hasFarm && myFarm->almostEmpty())
	{
		landValue -= 1;
		starving = true;
	}

	if(starving && hasFarm && !myFarm->almostEmpty())
	{
		landValue += 1;
		starving = false;
	}

	if(distanceToBuilding(FARM) < 24)
	{
		Farm* f = static_cast<Farm*>(nearestBuilding(FARM));
		if((!hasFarm && !f->isEmpty()) || (!f->isEmpty() && hasFarm && myFarm->isEmpty()))
		{
			landValue += 1;
			hasFarm = true;
			myFarm = f;
			myFarm->lowerCapacity(1);
		}
	}
	farmDistance = distanceToBuilding(FARM);

	if(rand()%15 <= landValue)
	{
		populationDifference += 3;
	}
	else if(rand()%10 <= 2)
	{
		populationDifference -= 2;
	}
	while(population+populationDifference < 0)
	{
		populationDifference++;
	}
	while(population+populationDifference > maxPop)
	{
		populationDifference--;
	}

	if(true)
	{
		if(populationDifference > 0)
		{
			if(myFarm != nullptr)
			{
				myFarm->lowerCapacity(2);
			}
		}
		else if(populationDifference < 0 && myFarm != nullptr)
		{
			myFarm->raiseCapacity(1);
		}
		CivHandler::addPopulation(populationDifference);
		population += populationDifference;
	}
	populationDifference = 0;
	CivHandler::payTaxes(population);

}

void Residential::setPopulation(int pop)
{
	population = pop;
	CivHandler::addPopulation(pop);
}

int Residential::getPopulation()
{
	return population;
}

void Residential::nextMove()
{

}

void Residential::tick()
{
	 if(!loadedImages)
	 {
		 setImages(
				 LoadTexture("src/img/city/teepee.png"),
				 LoadTexture("src/img/city/house.png"));
		 loadedImages = true;
	 }

	if(getClicking() && isPlayer())
	{
		demolish();
	}
}

void Residential::render()
{
	/*
	if(landValue == 0)
	{
		DrawRectangle(x,y,8,8,BLACK);
	}
	if(landValue == 1)
	{
		DrawRectangle(x,y,8,8,RED);
	}
	if(landValue == 2)
	{
		DrawRectangle(x,y,8,8,BLUE);
	}
	if(landValue == 3)
	{
		DrawRectangle(x,y,8,8,YELLOW);
	}
	if(landValue == 4)
	{
		DrawRectangle(x,y,8,8,GREEN);
	}
	if(landValue == 5)
	{
		DrawRectangle(x,y,8,8,MAGENTA);
	}*/
	if(population <= 0)
	{
		DrawRectangle(x,y,8,8,{0,192,0,255});
	}
	else
	{
		DrawTexture(teepee,x,y,WHITE);
	}
}

void Residential::setImages(Texture2D iTeepee, Texture2D iHouse)
{
	teepee = iTeepee;
	house = iHouse;
}


void Residential::finalize()
{
	if(hasFarm)
	{
		myFarm->lowerCapacity(-1);
	}
}

