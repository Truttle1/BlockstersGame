/*
 * UI.cpp
 *
 *  Created on: Jan 27, 2019
 *      Author: truttle1
 */

#include "UI.h"
bool UI::open = false;
UI::UI() {
	running = false;
}

UI::~UI() {
	// TODO Auto-generated destructor stub
}
void UI::loadFonts(void)
{
	font = LoadFontEx("src/SGK050.ttf",240,0,0);
}

bool UI::getClicking(int x, int y, int width, int height)
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
bool UI::isOpen()
{
	return open;
}
