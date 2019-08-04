/*
 * NPC.cpp
 *
 *  Created on: Jul 24, 2019
 *      Author: truttle1
 */

#include "NPC.h"

NPC::NPC(int ix, int iy) : Unit(ix,iy)
{
	unitType = TRIBENPC;
	startX = ix;
	startY = iy;
	tribal = true;

}

NPC::~NPC() {
	// TODO Auto-generated destructor stub
}

void NPC::tick()
{
	Unit::tick();
}

void NPC::render()
{
	if(isMoving())
	{
		DrawRectangle(x,y,8,8,RED);
	}
	DrawTexture(Species::monsterSpecies[Civilizations::tribes[owner].monster].image,x,y,WHITE);
}

void NPC::finalize()
{

}

void NPC::nextMove()
{
	if(!moved && movementStage < 1)
	{
		int spd = 1;
		if(targetX == -1 && targetY == -1)
		{
			bool finished = false;
			int count = 0;
			x = (x/8)*8;
			y = (y/8)*8;
			while(!finished)
			{
				selectRandomTarget();
				targetX = (targetX/8)*8;
				targetY = (targetY/8)*8;
				for(unsigned i = 0; i < objects.size(); i++)
				{
					if(objects[i]->getName() == TERRITORY && objects[i]->getX() == targetX && objects[i]->getY() == targetY)
					{
						Territory* t = static_cast<Territory*>(objects[i]);
						if(t->isTribal() && t->getOwner() == owner)
						{
							finished = true;
							break;
						}
					}
				}
				count++;
				if(count > 10)
				{
					finished = true;
					targetX = (x/8)*8;
					targetY = (y/8)*8;
				}
			}
		}
		if(x == targetX && y == targetY)
		{
			movementStage++;
			targetX = -1;
			targetY = -1;
		}
	}
	else
	{
		moved = true;
		targetX = -1;
		targetY = -1;
	}
}

void NPC::nextEat()
{

}

void NPC::nextGeneration()
{
	Unit::nextGeneration();
}
