/*
 * GameObject.cpp
 *
 *  Created on: Nov 4, 2018
 *      Author: truttle1
 */

#include "GameObject.h"
#include "../GameWindow.h"

vector<GameObject*> GameObject::objects;
vector<GameObject*> GameObject::monsters;
vector<vector<vector<GameObject*>>> GameObject::cluster(15, vector<vector<GameObject*>> (15));
GameObject* GameObject::groundArray[60][60];
Fog GameObject::fog[60][60];
int GameObject::internalClock = 0;
int GameObject::generation = -15;
int GameObject::worldMouseX = 0;
int GameObject::worldMouseY = 0;
int GameObject::evolutionOccuredYet = false;
int GameObject::evolutionOccuredYetMonst = 0;
Font GameObject::font;

	GameObject::GameObject(int ix, int iy,int w, int h)
	{
		GameObject::x = ix;
		GameObject::y = iy;
		GameObject::width = w;
		GameObject::height = h;

	}
	GameObject::~GameObject()
	{
	}
	void GameObject::setX(int x)
	{
		this->x = x;
	}
	void GameObject::setY(int y)
	{
		this->y = y;
	}
	int GameObject::getX()
	{
		return this->x;
	}
	int GameObject::getY()
	{
		return this->y;
	}
	int GameObject::getWidth()
	{
		return this->width;
	}
	int GameObject::getHeight()
	{
		return this->height;
	}
	ObjectType GameObject::getName()
	{
		return this->name;
	}
	void tick()
	{

	}
	void render()
	{

	}
	void GameObject::setInternalClock(int clock)
	{
		internalClock = clock;
	}
	void GameObject::setGroundArray(GameObject* groundArray[60][60])
	{
		for(int x=0; x<60;x++)
		{
			for(int y=0; y<60; y++)
			{
				GameObject::groundArray[x][y] = groundArray[x][y];
			}
		}
	}
	void GameObject::setMousePos(int x, int y)
	{
		GameObject::worldMouseX = x;
		GameObject::worldMouseY = y;
	}
	Vector2 GameObject::getMousePos()
	{
		Vector2 v2;
		v2.x = GameObject::worldMouseX;
		v2.y = GameObject::worldMouseY;
		return v2;
	}
	void GameObject::resetEvolution()
	{
		evolutionOccuredYet = false;
		evolutionOccuredYetMonst = false;
	}

	void GameObject::unClick()
	{
		clicked = false;
	}

	bool GameObject::isClicked()
	{
		return clicked;
	}
	bool GameObject::getClicking()
	{

		bool clicking = false;
		if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
		{
			int mx = GetMouseX() / GameWindow::getCamera()->zoom - GameWindow::getCamera()->offset.x / GameWindow::getCamera()->zoom;
			int my = GetMouseY() / GameWindow::getCamera()->zoom - GameWindow::getCamera()->offset.y / GameWindow::getCamera()->zoom ;
			mouseX = mx;
			mouseY = my;
			clicking = (mx >= x && my >= y && mx <= x+width && my <= y+height);
			if(clicking)
			{
				clickedHere = true;
			}
			else
			{
				clickedHere = false;
			}
		}
		return clicking;
	}

	int GameObject::getRemovedFog()
	{
		int ret = 0;
		for(int i=0; i<60;i++)
		{
			for(int j=0; j<60; j++)
			{
				if(!fog[i][j].isVisible())
				{
					ret++;
				}
			}
		}
		return ret;
	}

