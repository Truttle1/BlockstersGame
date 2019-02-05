/*
 * Object.cpp
 *
 *  Created on: Jan 2, 2019
 *      Author: truttle1
 */

#include "Monster.h"
Monster::Monster(int x, int y, int sp) : GameObject(x,y,8,8)
{
	name = "Plant";
	species = sp;
	arbitraryPopNumber = (rand()%10)+1;
	Species::plantSpecies[species].population += arbitraryPopNumber;
	age = 0;
}
Monster::~Monster()
{

}
void Monster::tick()
{

}
void Monster::render()
{

}
void Monster::nextGeneration()
{

}
Rectangle Monster::getBounds()
{
	Rectangle r;
	r.x = 0;
	r.y = 0;
	r.height = 0;
	r.width = 0;
	return r;
}
void Monster::nextMove()
{

}
void Monster::nextEat()
{

}
bool Monster::getAlive()
{
	return alive;
}
int Monster::getSpecies()
{
	return species;
}
void Monster::kill()
{
	if(!alive)
	{
		alive = false;
		Species::monsterSpecies[species].population -= arbitraryPopNumber;
	}
}
void Monster::evolve()
{
}
void Monster::killSameLocation()
{
}
