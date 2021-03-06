/*
 * Plant.cpp
 *
 *  Created on: Jan 2, 2019
 *      Author: truttle1
 */

#include "Plant.h"
#include "../../species/Species.h"
#include <iostream>
#include <algorithm>
Plant::Plant(int ix, int iy, int sp) : GameObject(ix,iy,8,8)
{
	name = PLANT;
	species = sp;
	//cout << "Plant of species " << sp << endl;
	arbitraryPopNumber = (rand()%Species::plantSpecies[species].groupSize)+1;
	Species::plantSpecies[species].population += arbitraryPopNumber;
	age = 0;
	hp = (Species::plantSpecies[species].size);
	clusterX = (x / 16) / 6;
	clusterY = (y / 16) / 6;
	//std::cout << clusterX << "," << clusterY << endl;
	bool onLand = true;

	if(generation < 15)
	{
		while(Species::plantSpecies[species].maxDeath - Species::plantSpecies[species].minDeath > 5)
		{
			Species::plantSpecies[species].maxDeath--;
		}
		while(Species::plantSpecies[species].maxNew - Species::plantSpecies[species].minNew > 5)
		{
			Species::plantSpecies[species].maxNew--;
		}
	}
	for(uint i = 0; i<GameObject::objects.size();i++)
	{
		GameObject* g = GameObject::objects[i];
		if(g->getName() == GROUND)
		{
			Ground* g2 = static_cast<Ground*>(g);
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
	curBiome = getBiome();
	cluster[clusterX][clusterY].push_back(this);
}
Plant::~Plant()
{

}
void Plant::tick()
{
	if(hp <= 0)
	{
		kill();
	}
}
void Plant::loadFromFile(int iHp, int iAge, int iPop)
{
	hp = iHp;
	age = iAge;
	arbitraryPopNumber = iPop;
	Species::plantSpecies[species].population += arbitraryPopNumber;
}
int Plant::getPopulation()
{
	return arbitraryPopNumber;
}
void Plant::render()
{
	if(!alive)
	{
		return;
	}
	/*
	if(!alive)
	{
		color = BLACK;
	}
	else if(hp <= 0)
	{
		color = RED;
	}
	else if(hp == 1)
	{
		color = YELLOW;
	}
	else if(hp == 2)
	{
		color = BLUE;
	}
	else
	{
		color = GREEN;
	}*/
	int normX = x/16;
	int normY = y/16;
	if(normX < 60 && normY < 60 && normX > -1 && normY > -1 && !GameObject::fog[normX][normY].isVisible())
	{
		DrawTexture(Species::plantSpecies[this->species].image,x,y,WHITE);
		if(!(std::find(Species::plantsDiscovered.begin(),Species::plantsDiscovered.end(),species) != Species::plantsDiscovered.end()))
		{
			Species::plantsDiscovered.push_back(species);
		}
	}
}
void Plant::nextGeneration()
{
	color = GREEN;
	int gn = getNeighborhood();
	if(hp <= 0)
	{
		kill();
	}

	if(x > 960 || y < 0 || x < 0 || x > 960)
	{
		kill();
	}
	//Plants die when they live longer than their lifespan.
	if(age>Species::plantSpecies[this->species].lifespan)
	{
		this->kill();
	}
	//Death by overcrowding
	if(gn>Species::plantSpecies[this->species].maxDeath && rand()%100<75)
	{
		this->kill();
	}
	//Death by lonliness
	if(gn<Species::plantSpecies[this->species].minDeath && rand()%100<50)
	{
		this->kill();
	}
	if(rand()%40 < Species::plantSpecies[this->species].toxicity)
	{
		kill();
	}
	int repValue;
	if(Species::plantSpecies[this->species].land)
	{
		if(curBiome == DIRT)
		{
			repValue = rand()%20;
		}
		else if(curBiome == TUNDRA)
		{
			repValue = rand()%40;
		}
		else if(curBiome == MOUNTAIN)
		{
			repValue = rand()%35;
		}
		else if(curBiome == DESERT)
		{
			repValue = rand()%(30-Species::plantSpecies[this->species].nutrients);
		}
		else if(curBiome == SNOW)
		{
			repValue = rand()%(35-Species::plantSpecies[this->species].nutrients);
		}
		else if(curBiome == BEACH)
		{
			repValue = rand()%(25-Species::plantSpecies[this->species].nutrients);
		}
	}
	else
	{
		repValue = rand()%26;
	}
	//Reproduce
	if(gn<Species::plantSpecies[this->species].maxNew && gn>Species::plantSpecies[this->species].minNew)
	{
		if( repValue<13 || (generation<0 && repValue < 15))
		{
			int newX = ((rand()%5)*8)-16;
			int newY = ((rand()%5)*8)-16;
			Plant* p = new Plant(this->getX()+newX,this->getY()+newY,this->getSpecies());
			GameObject::objects.push_back(p);
			if(rand()%4000 < 75 && alive && Species::plantSpecies[this->species].evolvePass > 0)
			{
				if(evolutionOccuredYet <= 4 && Species::plantSpecies[species].land)
				{
					evolve();
					GameObject::evolutionOccuredYet++;
				}
				else if(evolutionOccuredYetWater <= 4 && !Species::plantSpecies[species].land)
				{
					evolve();
					GameObject::evolutionOccuredYetWater++;
				}
			}
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
	for(uint i = 0; i<GameObject::cluster[clusterX][clusterY].size();i++)
	{
		GameObject* temp = GameObject::cluster[clusterX][clusterY][i];
		if(temp)
		{
			int distX = std::abs((this->getX())-(temp->getX()));
			int distY = std::abs((this->getY())-(temp->getY()));
			if(distX <= 8 && distY <= 8 && temp != this && temp->getName() == PLANT)
			{
				//printf("%d, %d :: %d, %d, :: %d, %d\n",x,y,temp->getX(),temp->getY(),distX,distY);
				c++; //GOT EM
				Plant* plnt = static_cast<Plant*>(temp);
				/*
				if(Species::plantSpecies[plnt->getSpecies()].toxicity > Species::plantSpecies[species].toxicity)
				{
					if(rand()%100 < 60)
					{
						kill();
					}
				}*/
			}
		}
	}
	return c;
}
void Plant::killSameLocation()
{
	for(uint i = 3600; i<GameObject::objects.size();i++)
	{
		GameObject* temp = GameObject::objects[i];
		if(temp && temp->getX() == this->getX() && temp->getY() == this->getY() && temp != this && temp->getName() == PLANT)
		{
			Plant* p = static_cast<Plant*>(temp);
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
int Plant::getAge()
{
	return age;
}

int Plant::getHP()
{
	return hp;
}

void Plant::evolve()
{
	printf("PLANT EVOLVE!\n");
	int minNew = Species::plantSpecies[species].minNew;
	int maxNew = Species::plantSpecies[species].maxNew;
	int minDeath = Species::plantSpecies[species].minDeath;
	int maxDeath = Species::plantSpecies[species].maxDeath;
	int nutrients = Species::plantSpecies[species].nutrients;
	int size = Species::plantSpecies[species].size;
	int toxicity = Species::plantSpecies[species].toxicity;
	int groupSize = Species::plantSpecies[species].groupSize;
	int lifespan = Species::plantSpecies[species].lifespan;
	Species::plantSpecies[species].evolvePass = -1;

	if(rand()%100<50)
	{
		minNew--;
		maxNew++;
		lifespan--;
	}
	else if(maxNew-minNew > 1 && rand()%100<50)
	{
		minNew++;
		maxNew--;
		lifespan+=2;
	}
	if(rand()%100<50)
	{
		minDeath--;
		maxDeath++;
		lifespan--;
	}
	else if(maxDeath-minDeath > 1 && rand()%100<50)
	{
		minDeath++;
		maxDeath--;
		lifespan+=2;
	}
	if(rand()%100<40)
	{
		toxicity+=2;
	}
	else if(toxicity > 0 && rand()%100<50)
	{
		toxicity--;
		lifespan+=2;
	}
	if(rand()%100<70)
	{
		size+=2;
		lifespan++;
	}
	else
	{
		toxicity+=2;
	}
	size++;
	nutrients++;

	if(nutrients < 1)
	{
		nutrients = 1;
	}
	if(rand()%100<50)
	{
		groupSize+=10;
	}
	if(rand()%100<50 && groupSize > 10)
	{
		groupSize-=10;
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
	newSp.evolvePass = 0;
	bool replacedImage = false;
	if(true)
	{
		replacedImage = true;
		if(rand()%5<=2 && newSp.size>=4)
		{
			newSp.image = PlantImg::medium0;
		}
		else if(rand()%5<=2 && newSp.size>=4)
		{
			newSp.image = PlantImg::medium1;
		}
		else if(rand()%5<=2 && newSp.size>=4)
		{
			newSp.image = PlantImg::medium3;
		}
		else if(rand()%5<=2 && newSp.size>=4)
		{
			newSp.image = PlantImg::medium4;
		}
		else if(rand()%5<=2 && newSp.size>=3)
		{
			newSp.image = PlantImg::medium2;
		}
		else if(rand()%5<=2 && newSp.size>=2)
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
		else if(rand()%5<=2 && newSp.size>=2)
		{
			newSp.image = PlantImg::small3;
		}
		else if(rand()%5<=2 && newSp.size>=2)
		{
			newSp.image = PlantImg::small4;
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
	if(!replacedImage)
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

	if(newSp.size > (generation/5)+3)
	{
		newSp.size = (generation/5)+3;
	}
	/*
	if(newSp.toxicity > (generation/4)+3)
	{
		newSp.toxicity = (generation/4)+3;
	}
	*/
	Species::plantSpecies.push_back(newSp);
	int newX = ((rand()%5)*8)-16;
	int newY = ((rand()%5)*8)-16;
	cout << "MADE IT HERE!" << endl;
	Plant* p = new Plant(this->getX()+newX,this->getY()+newY,Species::plantSpecies.size()-1);
	if(p)
	{
		GameObject::objects.push_back(p);
		int r = rand()%4;
		for(int i=0; i<(r)+1;i++)
		{
			newX = ((rand()%6)*8)-32;
			newY = ((rand()%6)*8)-32;
			Plant* p = new Plant(this->getX()+newX,this->getY()+newY,Species::plantSpecies.size()-1);
			GameObject::objects.push_back(p);
		}
	}
	cout << "MADE IT HERE! VERSION 2" << endl;
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
		if(g->getName() == GROUND)
		{
			Ground* g2 = static_cast<Ground*>(g);
			if(CheckCollisionRecs(g2->getBounds(),this->getBounds()))
			{
				return g2->getBiome();
			}
		}
	}
	return DIRT;
}
void Plant::removeFog()
{
	int normX = x/16;
	int normY = y/16;
	GameObject::fog[normX][normY].disable();
}
void Plant::nextMove()
{
	if(hp <= 0)
	{
		kill();
	}
}
void Plant::nextEat()
{

}
int Plant::getEaten(int amount)
{
	removeHp(amount);
	return Species::plantSpecies[species].nutrients*2;
}
void Plant::removeHp(int amount)
{
	this->hp -= amount;
}


double Plant::distanceToPlayer()
{
	double dist = 99999999;
	for(unsigned int i = 0; i < monsters.size(); i++)
	{
		GameObject* m = monsters[i];
		double tempDist = std::sqrt(std::pow(x-m->getX(),2) + std::pow(x-m->getY(),2));
		if(tempDist < dist)
		{
			dist = tempDist;
		}
	}
	return dist;
}
