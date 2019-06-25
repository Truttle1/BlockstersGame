/*
 * Behavior.cpp
 *
 *  Created on: Apr 15, 2019
 *      Author: truttle1
 */

#include "Behavior.h"
#include <iostream>

Behavior::Behavior(int iX, int iY, int iCost) {
	status = 0;
	x = iX;
	y = iY;
	cost = iCost;
}

Behavior::~Behavior() {
	// TODO Auto-generated destructor stub
}

void Behavior::init(Texture2D iTexture,std::vector<std::string> iText)
{
	texture = iTexture;
	text = iText;
}

void Behavior::setTexture(bool tex)
{
	altTexture = tex;
}

void Behavior::setAltTexture(Texture2D iTexture,std::vector<std::string> iText)
{
	texture2 = iTexture;
	altText = iText;
}

bool Behavior::getClicking(int nx, int ny, int wx, int wy)
{

	bool clicking = false;
	if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
	{
		int mx = GetMouseX();
		int my = GetMouseY();
		clicking = (mx >= nx && my >= ny && mx <= nx+wx && my <= ny+wy);
	}
	return clicking;
}
void Behavior::tick()
{
	if(visible)
	{
		if(getClicking(x,y,16,16))
		{
			if(status == 0)
			{
				status = 1;
			}
			else if(status == 2)
			{
				status = 3;
			}
		}
		else if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && status == 1)
		{
			status = 0;
		}
		else if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && status == 3)
		{
			status = 2;
		}
	}
}

void Behavior::render()
{
	if(visible)
	{
		if(status == 0)
		{
			DrawTexture(altTexture ? texture2 : texture,x,y,WHITE);
		}
		else if(status == 1)
		{
			std::cout << "doy" << std::endl;
			DrawTexture(altTexture ? texture2 : texture,x,y,YELLOW);
		}
		else if(status == 2)
		{
			std::cout << "doy" << std::endl;
			DrawTexture(altTexture ? texture2 : texture,x,y,{0,255,255,255});
		}
		else if(status == 3)
		{
			std::cout << "doy" << std::endl;
			DrawTexture(altTexture ? texture2 : texture,x,y,RED);
		}
	}
}

void Behavior::enable()
{
	visible = true;
}

void Behavior::disable()
{
	visible = false;
}

void Behavior::setStatus(int iStatus)
{
	status = iStatus;
}

std::vector<std::string> Behavior::getText()
{
	return altTexture ? altText : text;
}


int Behavior::getStatus()
{
	return status;
}

int Behavior::getCost()
{
	return cost;
}
