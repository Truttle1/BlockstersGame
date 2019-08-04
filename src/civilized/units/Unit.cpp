/*
 * Unit.cpp
 *
 *  Created on: Jul 24, 2019
 *      Author: truttle1
 */

#include "Unit.h"

Unit::Unit(int ix, int iy) : GameObject(ix,iy,8,8) {
	name = UNIT;
	unit = true;
	targetX = -1;
	targetY = -1;
	movementStage = 0;
	moved = false;
	owner = -1;
	tribal = false;

}

Unit::~Unit() {
	// TODO Auto-generated destructor stub
}

void Unit::setOwner(int iOwner)
{
	owner = iOwner;
}

int Unit::getOwner()
{
	return owner;
}

bool Unit::getTribal()
{
	return tribal;
}

void Unit::nextGeneration()
{
	movementStage = 0;
	moved = false;
	targetX = -1;
	targetY = -1;
}

void Unit::nextMove()
{
	if(!moved && movementStage < 1)
	{
		int spd = 1;
		if(targetX == -1 && targetY == -1)
		{
			selectRandomTarget();
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

void Unit::tick()
{
	if(!moved && targetX != -1 && targetY != -1)
	{
		int normX = (x/16)*16;
		int normY = (y/16)*16;
		int normTX = (targetX/16)*16;
		int normTY = (targetY/16)*16;

		int movement = 1;
		if(x < targetX)
		{
			x+=movement;
		}
		else if(x > targetX)
		{
			x-=movement;
		}
		else if(y < targetY)
		{
			y+=movement;
		}
		else if(y > targetY)
		{
			y-=movement;
		}
		else if(x == targetX && y == targetY)
		{
			moved = true;
			targetX = -1;
			targetY = -1;
		}
		cout << targetX << "," << targetY << endl;
		if(!isMoving())
		{
			x = (x/8)*8;
			y = (y/8)*8;
		}
	}

}

void Unit::selectRandomTarget()
{
	if(targetX == -1)
	{
		targetX = x;
		targetX += (-1+(rand()%3))*8;
	}
	if(targetY == -1)
	{
		targetY = y;
		targetY += (-1+(rand()%3))*8;
	}
	cout << targetX << "," << targetY << endl;
}

bool Unit::isMoving()
{
	return !moved;
}

void Unit::resetMovement()
{
	moved = false;
}

Rectangle Unit::getBounds()
{
	Rectangle r;
	r.x = x;
	r.y = y;
	r.height = 8;
	r.width = 8;
	return r;
}
