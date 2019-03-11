/*
 * Meat.cpp
 *
 *  Created on: Feb 16, 2019
 *      Author: truttle1
 */

#include "Meat.h"
Texture2D Meat::image;
Meat::Meat(int ix, int iy, int iNutrients) : GameObject(ix,iy,8,8)
{
	nutrients = iNutrients;
	timeLeft = 4;
	name = "Meat";
	alive = true;
}

Meat::~Meat() {
}

void Meat::nextGeneration()
{
	timeLeft--;
	if(timeLeft == 0)
	{
		alive = false;
	}
}
void Meat::nextEat()
{

}
void Meat::nextMove()
{

}
Rectangle Meat::getBounds()
{
	Rectangle r;
	r.x = x;
	r.y = y;
	r.height = 8;
	r.width = 8;
	return r;
}
bool Meat::isAlive()
{
	return alive;
}
int Meat::eat()
{
	alive = false;
	return nutrients;
}
void Meat::setMeatTexture(Texture2D img)
{
	image = img;
}
void Meat::tick()
{

}
void Meat::render()
{
	DrawTexture(image,x,y,WHITE);
}
