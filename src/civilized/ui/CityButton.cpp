/*
 * CityButton.cpp
 *
 *  Created on: Apr 15, 2019
 *      Author: truttle1
 */

#include <iostream>
#include "CityButton.h"

CityButton::CityButton(int iX, int iY, int iCost) {
	status = 0;
	x = iX;
	y = iY;
	cost = iCost;
	messageHeader = "DEFAULT";
}

CityButton::~CityButton() {
	// TODO Auto-generated destructor stub
}

void CityButton::init(Texture2D iTexture,std::vector<std::string> iText)
{
	texture = iTexture;
	text = iText;
}

void CityButton::setTexture(bool tex)
{
	altTexture = tex;
}

void CityButton::setAltTexture(Texture2D iTexture,std::vector<std::string> iText)
{
	texture2 = iTexture;
	altText = iText;
}

bool CityButton::getClicking(int nx, int ny, int wx, int wy)
{

	bool clicking = false;
	if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
	{
		int mx = GetMouseX();
		int my = GetMouseY();
		if(my > 416)
		{
			clicking = (mx > nx && my > ny && mx < nx+wx && my < ny+wy);
		}
	}
	return clicking;
}
void CityButton::tick()
{
	if(visible)
	{
		if(getClicking(x,y,16,16))
		{
			if(status == 0)
			{
				status = 1;
				recentlyChanged = true;
			}
		}
	}
}

bool CityButton::isRecentlyChanged()
{
	return recentlyChanged;
}

void CityButton::doneChanging()
{
	recentlyChanged = false;
}

void CityButton::deselect()
{
	status = 0;
}

std::vector<std::string> CityButton::getMessage()
{
	return warningMessage;
}

std::string CityButton::getHeader()
{
	return messageHeader;
}

void CityButton::render()
{
	if(visible)
	{
		if(status == 0)
		{
			DrawTexture(altTexture ? texture2 : texture,x,y,WHITE);
		}
		else if(status == 1)
		{
			DrawTexture(altTexture ? texture2 : texture,x,y,GREEN);
		}
	}
}

void CityButton::enable()
{
	visible = true;
}

void CityButton::disable()
{
	visible = false;
}

void CityButton::setStatus(int iStatus)
{
	status = iStatus;
}

std::vector<std::string> CityButton::getText()
{
	return altTexture ? altText : text;
}


int CityButton::getStatus()
{
	return status;
}

int CityButton::getCost()
{
	return cost;
}

void CityButton::setWarning(std::string iHeader, std::vector<std::string> iMessage)
{
	messageHeader = iHeader;
	warningMessage = iMessage;
}
