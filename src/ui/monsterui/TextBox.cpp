/*
 * TextBox.cpp
 *
 *  Created on: Feb 23, 2019
 *      Author: truttle1
 */

#include "TextBox.h"

const int TextBox::MAX_LENGTH;
TextBox::TextBox()
{
	x = 0;
	y = 0;
	typing = false;
}
TextBox::TextBox(int ix, int iy, std::string iText, Font iFont)
{
	x = ix;
	y = iy;
	typing = false;
	text = iText;
	font = iFont;

}

TextBox::~TextBox()
{
}

void TextBox::setText(std::string input)
{
	text = input;
}

std::string TextBox::getText()
{
	return text;
}

void TextBox::tick()
{
	if(getClicking(x,y,144,24))
	{
		typing = true;
	}
	else if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
	{
		typing = false;
	}
	if(typing)
	{
		if(IsKeyPressed(KEY_BACKSPACE))
		{
			text = text.substr(0,text.length()-1);
		}
		else if(GetKeyPressed() > 31 && text.length() < MAX_LENGTH)
		{
			text += GetKeyPressed();
		}
		printf("%d\n",GetKeyPressed());
	}
}
void TextBox::render()
{
	if(typing)
	{
		DrawRectangle(x,y,144,24,{0,255,255,255});
	}
	DrawRectangleLines(x,y,144,24,BLACK);
	Vector2 v2;
	v2.x = x + 4;
	v2.y = y - 4;
	DrawTextEx(font,text.c_str(),v2,24.0f,0.0f,BLACK);
}
bool TextBox::getClicking(int x, int y, int width, int height)
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
void TextBox::type()
{

}
