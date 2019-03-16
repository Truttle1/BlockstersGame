/*
 * ColorBox.cpp
 *
 *  Created on: Feb 18, 2019
 *      Author: truttle1
 */

#include "ColorBox.h"



ColorBox::ColorBox()
{
	selected = false;
}
ColorBox::~ColorBox()
{
}
void ColorBox::init(int ix, int iy, Color icolor)
{
	this->x = ix;
	this->y = iy;
	this->color = icolor;
	Texture2D cb1 = LoadTexture("src/img/ui/colorbox.png");
	Texture2D cb2 = LoadTexture("src/img/ui/selectedcolorbox.png");
	regular = replaceColorsToImage(&cb1,WHITE,color);
	pressed = replaceColorsToImage(&cb2,WHITE,color);

}
void ColorBox::tick()
{
	if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
	{
		int mx = GetMouseX();
		int my = GetMouseY();
		printf("%d, %d\n",mx,my);
		if(mx >= x && my >= y && mx <= x+32 && my <= y+32)
		{
			selected = true;
		}
		else if(mx > 200 && my > 32 && mx < 480 && my < 180)
		{
			selected = false;
		}
	}
}
void ColorBox::render()
{
	if(selected)
	{
		DrawTexture(pressed,x,y,WHITE);
	}
	else
	{
		DrawTexture(regular,x,y,WHITE);
	}
}
Color ColorBox::getColor()
{
	return color;
}

Texture ColorBox::replaceColorsToImage(Texture* image, Color c1, Color c2)
{
	Texture ret = LoadTextureFromImage(GetTextureData(*image));
	Color* pixels = (Color*)(GetImageData(GetTextureData(ret)));
	for(unsigned int i = 0; i<1024; i++)
	{
		Color c = pixels[i];
		if(c.r == c1.r && c.g == c1.g && c.b == c1.b && c.a == c1.a)
		{
			pixels[i] = c2;
		}
		UpdateTexture(ret,pixels);
	}
	return ret;
}
bool ColorBox::getSelected()
{
	return selected;
}

