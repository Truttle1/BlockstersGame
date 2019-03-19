/*
 * Meat.cpp
 *
 *  Created on: Feb 16, 2019
 *      Author: truttle1
 */

#include "Meat.h"
#include "../../GameWindow.h"
Texture2D Meat::image;
Meat::Meat(int ix, int iy, int iNutrients, int iSpecies) : GameObject(ix,iy,8,8)
{
	nutrients = iNutrients;
	timeLeft = 4;
	name = "Meat";
	alive = true;
	species = iSpecies;
	clickedHere = false;
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
	getClicking();
	if(clickedHere)
	{
		string meatType = Species::monsterSpecies[species].name;
		GameWindow::showUpperText("Meat of " + meatType + "\nContains " + to_string(nutrients) + " HP of Nutrients");
	}
}
void Meat::render()
{
	DrawTexture(image,x,y,WHITE);
}
