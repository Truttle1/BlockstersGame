/*
 * GameObject.cpp
 *
 *  Created on: Nov 4, 2018
 *      Author: truttle1
 */

#include "GameObject.h"
#include "../GameWindow.h"

vector<GameObject*> GameObject::objects;
GameObject* GameObject::groundArray[60][60];
Fog GameObject::fog[60][60];
int GameObject::internalClock = 0;
int GameObject::generation = 1;
int GameObject::worldMouseX = 0;
int GameObject::worldMouseY = 0;
bool GameObject::evolutionOccuredYet = false;
Font GameObject::font;

	GameObject::GameObject(int x, int y,int w, int h)
	{
		GameObject::x = x;
		GameObject::y = y;
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
	string GameObject::getName()
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
	}

