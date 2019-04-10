/*
 * MessageBox.cpp
 *
 *  Created on: Apr 8, 2019
 *      Author: truttle1
 */

#include "MessageBox.h"
MessageBox::MessageBox()
{

}
void MessageBox::init(Font iFont)
{
	font = iFont;

}

MessageBox::~MessageBox() {
	// TODO Auto-generated destructor stub
}


bool MessageBox::getClicking(int x, int y, int width, int height)
{

	bool clicking = false;
	if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
	{
		int mx = GetMouseX();
		int my = GetMouseY();
		clicking = (mx >= x && my >= y && mx <= x+width && my <= y+height);
	}
	return clicking;
}

void MessageBox::tick()
{
	if(visible)
	{
		if(getClicking(212,324,64,32))
		{
			visible = false;
		}
	}
}

void MessageBox::render()
{
	if(visible)
	{
		stringstream str(text);
		vector<string> result;
		while(str.good())
		{
			string substring;
			getline(str, substring, '/');
			result.push_back(substring);
		}
		DrawRectangle(16,64,448,320,WHITE);
		DrawTextEx(font,result[0].c_str(),{32.0f,72.0f},48.0f,0.0f,BLACK);
		for(unsigned int i = 1; i < result.size(); i++)
		{
			DrawTextEx(font,result[i].c_str(),{32.0f,96.0f+(i*16.0f)},24.0f,0.0f,BLACK);
		}
		DrawRectangle(212,324,64,32,BLACK);
		DrawTextEx(font,"OK",{232.0f,326.0f},24.0f,0.0f,WHITE);
	}
}


bool MessageBox::getVisible()
{
	return visible;
}

void MessageBox::enable(std::string iText)
{
	text = iText;
	visible = true;
}

void MessageBox::disable()
{
	visible = false;
}

