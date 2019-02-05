/*
 * UIButton.cpp
 *
 *  Created on: Jan 23, 2019
 *      Author: truttle1
 */

#include <stdio.h>
#include "UIButton.h"

UIButton::UIButton()
{
	this->x = 0;//496;
	this->y = 0;//48;
	this->height = 0;
	this->width = 0;
	this->ui = NULL;
}
UIButton::UIButton(int x, int y, int width, int height) {
	this->x = x;//496;
	this->y = y;//48;
	this->height = height;
	this->width = width;
	this->ui = NULL;

}

UIButton::~UIButton() {
	// TODO Auto-generated destructor stub
}

int UIButton::getX()
{
	return x;
}

int UIButton::getY()
{
	return y;
}
int UIButton::getWidth()
{
	return width;
}

int UIButton::getHeight()
{
	return height;
}

void UIButton::clicked()
{
	if(this->ui != NULL)
	{
		this->ui->toggle();
	}
}
void UIButton::tick()
{
	bool clicking = false;
	if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
	{
		int mx = GetMouseX();
		int my = GetMouseY();
		clicking = (mx >= x && my >= y && mx <= x+width && my <= y+height);
	}
	if(clicking)
	{
		clicked();
	}
}
void UIButton::render()
{
	DrawRectangle(x,y,32,32,BLUE);
	DrawTexture(img,x,y,WHITE);
}
void UIButton::setImage(Texture img)
{
	this->img = img;
}
void UIButton::addUI(UI* ui)
{
	this->ui = ui;
}
