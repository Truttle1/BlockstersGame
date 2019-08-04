/*
 * ScienceButton.cpp
 *
 *  Created on: Apr 15, 2019
 *      Author: truttle1
 */

#include "ScienceButton.h"

#include <iostream>

ScienceButton::ScienceButton(int iX, int iY, int iCost) {
	status = 0;
	x = iX;
	y = iY;
	cost = iCost;
	messageHeader = "DEFAULT";
}

ScienceButton::~ScienceButton() {
	// TODO Auto-generated destructor stub
}

void ScienceButton::init(Texture2D iTexture,std::vector<std::string> iText)
{
	texture = iTexture;
	text = iText;
}

void ScienceButton::setTexture(bool tex)
{
	altTexture = tex;
}

void ScienceButton::setAltTexture(Texture2D iTexture,std::vector<std::string> iText)
{
	texture2 = iTexture;
	altText = iText;
}

bool ScienceButton::getClicking(int nx, int ny, int wx, int wy)
{

	bool clicking = false;
	if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
	{
		int mx = GetMouseX();
		int my = GetMouseY();
		if(mx > 208)
		{
			return false;
		}
		clicking = (mx >= nx && my >= ny && mx <= nx+wx && my <= ny+wy);
	}
	return clicking;
}
void ScienceButton::tick()
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
				if(messageHeader != "DEFAULT")
				{
				}
			}
		}
		else if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && status == 1 && GetMouseX() < 208)
		{
			status = 0;
		}
		else if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && status == 3 && GetMouseX() < 208)
		{
			status = 2;
		}
	}
}

std::vector<std::string> ScienceButton::getMessage()
{
	return warningMessage;
}

std::string ScienceButton::getHeader()
{
	return messageHeader;
}

void ScienceButton::render()
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

void ScienceButton::enable()
{
	visible = true;
}

void ScienceButton::disable()
{
	visible = false;
}

void ScienceButton::setStatus(int iStatus)
{
	status = iStatus;
}

std::vector<std::string> ScienceButton::getText()
{
	return altTexture ? altText : text;
}


int ScienceButton::getStatus()
{
	return status;
}

int ScienceButton::getCost()
{
	return cost;
}

void ScienceButton::setWarning(std::string iHeader, std::vector<std::string> iMessage)
{
	messageHeader = iHeader;
	warningMessage = iMessage;
}
