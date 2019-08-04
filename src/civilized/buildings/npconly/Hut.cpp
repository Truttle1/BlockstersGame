/*
 * Hut.cpp
 *
 *  Created on: Jul 24, 2019
 *      Author: truttle1
 */

#include "Hut.h"

Texture2D Hut::image;
bool Hut::loadedImages = false;

Hut::Hut(int ix, int iy) : Building(ix,iy)
{
	name = BUILDING;
	buildingType = NPC_HUT;
}

Hut::~Hut()
{

}

void Hut::tick()
{
	if(!loadedImages)
	{
		setImage(LoadTexture("src/img/hut1.png"));
		loadedImages = true;
	}
}

void Hut::render()
{
	DrawTexture(image,x,y,WHITE);
}

void Hut::setImage(Texture2D iImage)
{
	image = iImage;
}

void Hut::nextGeneration()
{
	if(rand()%100<=2)
	{
		NPC* myNPC = new NPC(x,y+8);
		myNPC->setOwner(owner);
		objects.push_back(myNPC);
	}
	for(unsigned i = 0; i < objects.size(); i++)
	{
		if(objects[i]->getName() == UNIT && objects[i]->getUnit() == TRIBENPC)
		{
			if(objects[i]->getX() == x && objects[i]->getY() == y)
			{
				delete(GameObject::objects[i]);
				GameObject::objects[i] = nullptr;
				GameObject::objects.erase(GameObject::objects.begin()+i);
				i--;
			}
		}
	}
}

void Hut::nextMove()
{

}

void Hut::nextEat()
{

}

void Hut::finalize()
{

}


