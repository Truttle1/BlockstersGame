/*
 * RadioButton.cpp
 *
 *  Created on: Mar 3, 2019
 *      Author: truttle1
 */

#include "RadioButton.h"

RadioButton::RadioButton()
{
	x = 0;
	y = 0;
	selected = 0;
}

RadioButton::RadioButton(int ix, int iy, Font iFont)
{
	x = ix;
	y = iy;
	selected = 0;
	font = iFont;
}

RadioButton::~RadioButton()
{

}
void RadioButton::reset()
{
	selected = 0;
}
void RadioButton::tick()
{
	for(unsigned int i = 0; i < options.size(); i++)
	{
		if(getClicking(x,y+(i*16)))
		{
			selected = i;
		}
	}
}

bool RadioButton::getClicking(int nx, int ny)
{

	bool clicking = false;
	if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
	{
		int mx = GetMouseX();
		int my = GetMouseY();
		clicking = (mx >= nx-4 && my >= ny-4 && mx <= nx+4 && my <= ny+4);
	}
	return clicking;
}

void RadioButton::render()
{
	for(unsigned int i = 0; i < options.size(); i++)
	{
		Color c;
		if(i == 0)
		{
			c = BLUE;
		}
		else
		{
			c = GREEN;
		}
		DrawCircle(x,y+(i*16),6,c);
		DrawCircle(x,y+(i*16),4,WHITE);
		if(i == selected)
		{
			DrawCircle(x,y+(i*16),3,c);
		}

		stringstream str(options[i]);
		vector<string> result;
		while(str.good())
		{
			string substring;
			getline(str, substring, '|');
			result.push_back(substring);
		}
		if(result.size() > 1)
		{
			DrawTextEx(font,result[0].c_str(),{static_cast<float>(x + 16),static_cast<float>(y+(i*16)-8)},16.0f,0.0f,GREEN);
			DrawTextEx(font,result[1].c_str(),{static_cast<float>(x + 96),static_cast<float>(y+(i*16)-8)},16.0f,0.0f,RED);
			DrawTextEx(font,result[0].c_str(),{static_cast<float>(x + 17),static_cast<float>(y+(i*16)-8)},16.0f,0.0f,GREEN);
			DrawTextEx(font,result[1].c_str(),{static_cast<float>(x + 97),static_cast<float>(y+(i*16)-8)},16.0f,0.0f,RED);
		}
		else
		{
			DrawTextEx(font,result[0].c_str(),{static_cast<float>(x + 16),static_cast<float>(y+(i*16)-8)},16.0f,0.0f,BLUE);
			DrawTextEx(font,result[0].c_str(),{static_cast<float>(x + 17),static_cast<float>(y+(i*16)-8)},16.0f,0.0f,BLUE);
		}

	}
}

int RadioButton::getSelected()
{
	return selected;
}

void RadioButton::addOption(string optionName, int optionCost)
{
	options.push_back(optionName);
	optionCosts.push_back(optionCost);
}
