/*
 * EyeCandy.cpp
 *
 *  Created on: Feb 12, 2019
 *      Author: truttle1
 */

#include "EyeCandy.h"
Texture2D EyeCandy::boom_y;
Texture2D EyeCandy::boom_o;
Texture2D EyeCandy::boom_r;
EyeCandy::EyeCandy(int ix, int iy, int iImage) : GameObject(ix,iy,8,8)
{
	image = iImage;
	timeRemaining = 30;
	name = "EyeCandy";
}

EyeCandy::~EyeCandy() {
	// TODO Auto-generated destructor stub
}

void EyeCandy::tick()
{
	timeRemaining--;
}
void EyeCandy::render()
{
	if(image == 0)
	{
		DrawTexture(boom_y,x,y,WHITE);
	}
	if(image == 1)
	{
		DrawTexture(boom_o,x,y,WHITE);
	}
	if(image == 2)
	{
		DrawTexture(boom_r,x,y,WHITE);
	}
}
void EyeCandy::nextGeneration()
{
	timeRemaining = 0;
}
void EyeCandy::nextMove()
{
}
void EyeCandy::nextEat()
{

}
Rectangle EyeCandy::getBounds()
{
	Rectangle r;
	r.x = x;
	r.y = y;
	r.height = 8;
	r.width = 8;
	return r;
}
void EyeCandy::setBoomR(Texture2D img)
{
	boom_r = img;
}

void EyeCandy::setBoomO(Texture2D img)
{
	boom_o = img;
}

void EyeCandy::setBoomY(Texture2D img)
{
	boom_y = img;
}
int EyeCandy::getTimeRemaining()
{
	return timeRemaining;
}
