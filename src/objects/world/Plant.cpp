/*
 * Plant.cpp
 *
 *  Created on: Jan 2, 2019
 *      Author: truttle1
 */

#include "Plant.h"
#include "../../species/Species.h"
#include <iostream>
Plant::Plant(int x, int y, int sp) : GameObject(x,y,8,8)
{
	name = "Plant";
	species = sp;
	arbitraryPopNumber = (rand()%10)+1;
	Species::plantSpecies[species].population += arbitraryPopNumber;
	age = 0;
}
Plant::~Plant()
{

}
void Plant::tick()
{

}
void Plant::render()
{
	//DrawRectangle(x,y,8,8,color);
	DrawTexture(Species::plantSpecies[this->species].image,x,y,WHITE);
}
void Plant::nextGeneration()
{
	color = GREEN;
	try
	{
		bool onLand = true;
		for(uint i = 0; i<GameObject::objects.size();i++)
		{
			GameObject* g = GameObject::objects[i];
			if(g->getName() == "Ground")
			{
				Ground* g2 = dynamic_cast<Ground*>(g);
				if(CheckCollisionRecs(g2->getBounds(),this->getBounds()))
				{
					if(g2->getBiome() == WATER || g2->getBiome() == FRESHWATER)
					{
						onLand = false;
					}
				}
			}
		}
		if(!Species::plantSpecies[this->species].land && onLand)
		{
			this->kill();
			//printf("LAND IS BAD\nSPECIES %d HAS LAND VALUE OF %d\n",this->species,Species::plantSpecies[this->species].land);
		}
		else if(Species::plantSpecies[this->species].land && !onLand)
		{
			this->kill();
			//printf("WATER IS BAD\nSPECIES %d HAS LAND VALUE OF %d\n",this->species,Species::plantSpecies[this->species].land);
		}
		//Plants at the same location die.
		killSameLocation();
		//Plants die when they live longer than their lifespan.
		if(age>Species::plantSpecies[this->species].lifespan)
		{
			this->kill();
		}
		//Death by overcrowding
		if(getNeighborhood()>Species::plantSpecies[this->species].maxDeath && rand()%100<75)
		{
			this->kill();
		}
		//Death by lonliness
		if(getNeighborhood()<Species::plantSpecies[this->species].minDeath && rand()%100<33)
		{
			this->kill();
		}
		int repValue;
		if(Species::plantSpecies[this->species].land)
		{
			if(getBiome() == DIRT)
			{
				repValue = rand()%20;
			}
			else if(getBiome() == TUNDRA)
			{
				repValue = rand()%40;
			}
			else if(getBiome() == MOUNTAIN)
			{
				repValue = rand()%35;
			}
			else if(getBiome() == DESERT)
			{
				repValue = rand()%(30-Species::plantSpecies[this->species].nutrients);
			}
			else if(getBiome() == SNOW)
			{
				repValue = rand()%(35-Species::plantSpecies[this->species].nutrients);
			}
			else if(getBiome() == BEACH)
			{
				repValue = rand()%(25-Species::plantSpecies[this->species].nutrients);
			}
		}
		else
		{
			repValue = rand()%26;
		}
		//Reproduce
		if(age>=(Species::plantSpecies[this->species].lifespan/8) && getNeighborhood()<Species::plantSpecies[this->species].maxNew && getNeighborhood()>Species::plantSpecies[this->species].minNew && repValue<15)
		{
			int newX = ((rand()%5)*8)-16;
			int newY = ((rand()%5)*8)-16;
			Plant* p = new Plant(this->getX()+newX,this->getY()+newY,this->getSpecies());
			GameObject::objects.push_back(p);
			if(rand()%10000<5 && !GameObject::evolutionOccuredYet)
			{
				evolve();
				GameObject::evolutionOccuredYet = true;
			}
		}
		if(x<0 || x>=960)
		{
			this->kill();
		}
		if(y<0 || y>=960)
		{
			this->kill();
		}
		//Age goes up.
		age++;
		if(age>2)
		{
			removeFog();
		}

	}
	catch(int e)
	{
		printf("EXCEPTION %d HAPPENED!!!\n",e);
	}
}

bool Plant::getAlive()
{
	return alive;
}
int Plant::getSpecies()
{
	return species;
}
int Plant::getNeighborhood()
{
	int c = 0;
	for(uint i = 0; i<GameObject::objects.size();i++)
	{
		GameObject* temp = GameObject::objects[i];
		int distX = std::abs((this->getX())-(temp->getX()));
		int distY = std::abs((this->getY())-(temp->getY()));
		if(distX <= 8 && distY <= 8 && temp != this && temp->getName() == "Plant")
		{
			//printf("%d, %d :: %d, %d, :: %d, %d\n",x,y,temp->getX(),temp->getY(),distX,distY);
			c++; //GOT EM
		}
	}
	return c;
}
void Plant::killSameLocation()
{

	for(uint i = 0; i<GameObject::objects.size();i++)
	{
		GameObject* temp = GameObject::objects[i];
		if(temp->getX() == this->getX() && temp->getY() == this->getY() && temp != this && temp->getName() == "Plant")
		{
			Plant* p = dynamic_cast<Plant*>(temp);
			if(p->getAlive() && Species::plantSpecies[p->getSpecies()].toxicity > Species::plantSpecies[species].size)
			{
				p->kill();
			}
			else if(p->getAlive() && Species::plantSpecies[p->getSpecies()].size > Species::plantSpecies[species].size)
			{
				p->kill();
			}
		}
	}
}
void Plant::kill()
{
	if(alive)
	{
		alive = false;
		Species::plantSpecies[species].population -= arbitraryPopNumber;
	}
}
void Plant::evolve()
{
	int minNew = Species::plantSpecies[species].minNew;
	int maxNew = Species::plantSpecies[species].maxNew;
	int minDeath = Species::plantSpecies[species].minDeath;
	int maxDeath = Species::plantSpecies[species].maxDeath;
	int nutrients = Species::plantSpecies[species].nutrients;
	int size = Species::plantSpecies[species].size;
	int toxicity = Species::plantSpecies[species].toxicity;
	int groupSize = Species::plantSpecies[species].groupSize;
	int lifespan = Species::plantSpecies[species].lifespan;

	if(rand()%100<20)
	{
		minNew--;
		maxNew++;
		lifespan--;
	}
	else if(maxNew-minNew > 1 && rand()%100<20)
	{
		minNew++;
		maxNew--;
		lifespan+=2;
	}
	if(rand()%100<20)
	{
		minDeath--;
		maxDeath++;
		lifespan--;
	}
	else if(maxDeath-minDeath > 1 && rand()%100<20)
	{
		minDeath++;
		maxDeath--;
		lifespan+=2;
	}
	if(rand()%100<20)
	{
		toxicity+=2;
		lifespan--;
	}
	else if(toxicity > 0 && rand()%100<20)
	{
		toxicity--;
		lifespan+=2;
	}
	if(rand()%100<20)
	{
		size+=2;
		lifespan++;
		toxicity--;
	}
	else if(size < 0 && rand()%100<20)
	{
		size--;
		toxicity+=2;
	}

	if(rand()%100<20)
	{
		nutrients++;
	}
	if(rand()%100<20)
	{
		nutrients--;
	}
	if(minNew<0)
	{
		minNew = 0;
	}
	if(minDeath<0)
	{
		minDeath = 0;
	}
	if(lifespan<1)
	{
		lifespan = 1;
	}
	PlantSpecies newSp = PlantSpecies();
	newSp.land = Species::plantSpecies[species].land;
	newSp.toxicity = toxicity;
	newSp.size = size;
	newSp.lifespan = lifespan;
	newSp.groupSize = groupSize;
	newSp.nutrients = nutrients;
	newSp.minNew = minNew;
	newSp.maxNew = maxNew;
	newSp.minDeath = minDeath;
	newSp.maxDeath = maxDeath;
	newSp.name = Species::generateName();
	newSp.stemColor = Species::plantSpecies[species].stemColor;
	newSp.flowerColor = Species::plantSpecies[species].flowerColor;
	newSp.highlightColor = Species::plantSpecies[species].highlightColor;
	bool replacedImage = false;
	if(true)
	{
		replacedImage = true;
		if(rand()%5<=2 && newSp.size>=2)
		{
			newSp.image = PlantImg::small0;
		}
		else if(rand()%5<=2 && newSp.size>=2)
		{
			newSp.image = PlantImg::small1;
		}
		else if(rand()%5<=2 && newSp.size>=2)
		{
			newSp.image = PlantImg::small2;
		}
		else if(rand()%5<=1)
		{
			newSp.image = PlantImg::entryLevel3;
		}
		else if(rand()%5<=1)
		{
			newSp.image = PlantImg::entryLevel2;
		}
		else if(newSp.size>2)
		{
			newSp.image = PlantImg::entryLevel1;
		}
		else
		{
			newSp.image = PlantImg::entryLevel0;
		}
	}
	else
	{
		newSp.image = Species::plantSpecies[species].image;
	}
	if(rand()%100<20)
	{
		int r = rand()%ObjectColors::plantColorsFlower.size();
		newSp.flowerColor = ObjectColors::plantColorsFlower[r];
	}
	if(rand()%100<20)
	{
		int h = rand()%ObjectColors::plantColorsHighlight.size();
		newSp.flowerColor = ObjectColors::plantColorsHighlight[h];
	}
	if(replacedImage)
	{
		int r = rand()%ObjectColors::plantColorsFlower.size();
		newSp.flowerColor = ObjectColors::plantColorsFlower[r];
		newSp.image = Species::replaceColorsToImage(&newSp.image,Species::plantSpecies[species].stemColor,newSp.stemColor);
		newSp.image = Species::replaceColorsToImage(&newSp.image,Species::plantSpecies[species].flowerColor,newSp.flowerColor);
	}
	else
	{
		newSp.image = Species::replaceColorsToImage(&newSp.image,ObjectColors::PLANT_GREEN,newSp.stemColor);
		newSp.image = Species::replaceColorsToImage(&newSp.image,ObjectColors::ROSE_RED,newSp.flowerColor);
	}
	Species::plantSpecies.push_back(newSp);
	int newX = ((rand()%5)*8)-16;
	int newY = ((rand()%5)*8)-16;
	Plant* p = new Plant(this->getX()+newX,this->getY()+newY,Species::plantSpecies.size()-1);
	GameObject::objects.push_back(p);
	int r = rand()%20;
	for(int i=0; i<(r)+1;i++)
	{
		newX = ((rand()%6)*8)-32;
		newY = ((rand()%6)*8)-32;
		Plant* p = new Plant(this->getX()+newX,this->getY()+newY,Species::plantSpecies.size()-1);
		GameObject::objects.push_back(p);
	}
}
Rectangle Plant::getBounds()
{
	Rectangle r;
	r.x = x;
	r.y = y;
	r.height = 8;
	r.width = 8;
	return r;
}
Biome Plant::getBiome()
{
	for(unsigned int i = 0; i<GameObject::objects.size();i++)
	{
		GameObject* g = GameObject::objects[i];
		if(g->getName() == "Ground")
		{
			Ground* g2 = dynamic_cast<Ground*>(g);
			if(CheckCollisionRecs(g2->getBounds(),this->getBounds()))
			{
				return g2->getBiome();
			}
		}
	}
	return NIL;
}
void Plant::removeFog()
{
	int normX = x/16;
	int normY = y/16;
	GameObject::fog[normX][normY].disable();
}
void Plant::nextMove()
{

}
void Plant::nextEat()
{

}
