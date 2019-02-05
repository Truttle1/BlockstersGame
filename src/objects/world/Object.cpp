/*
 * Object.cpp
 *
 *  Created on: Jan 2, 2019
 *      Author: truttle1
 */

#include "Object.h"
Object::Object(int x, int y) : GameObject(x,y,8,8)
{

}
Object::~Object()
{

}
void Object::tick()
{

}
void Object::render()
{

}
void Object::nextGeneration()
{

}
Rectangle Object::getBounds()
{
	Rectangle r;
	r.x = 0;
	r.y = 0;
	r.height = 0;
	r.width = 0;
	return r;
}
void Object::nextMove()
{

}
void Object::nextEat()
{

}
