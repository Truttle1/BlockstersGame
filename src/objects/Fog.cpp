/*
 * Fog.cpp
 *
 *  Created on: Feb 3, 2019
 *      Author: truttle1
 */

#include "Fog.h"
Fog::Fog()
{
	this->x = 0;
	this->y = 0;
	visible = true;
}
Fog::Fog(int x, int y)
{
	visible = true;
	this->x = x;
	this->y = y;
}

Fog::~Fog() {
}

void Fog::disable()
{
	visible = false;
}

void Fog::render()
{
	if(visible)
	{
		DrawRectangle(x,y,16,16,BLACK);
	}
	if(IsKeyPressed(KEY_LEFT_ALT))
	{
		visible = false;
	}
}
bool Fog::isVisible()
{
	return visible;
}

void Fog::enable()
{
	visible = true;
}

