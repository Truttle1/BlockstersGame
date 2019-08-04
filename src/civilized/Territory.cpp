/*
 * Territory.cpp
 *
 *  Created on: Jun 27, 2019
 *      Author: truttle1
 */

#include "Territory.h"

Territory::Territory(int ix, int iy) : GameObject(ix,iy,8,8)
{
	name = TERRITORY;
	owner = 0;
	std::cout << "HEY THERE!!!" << std::endl;
}

Territory::~Territory()
{
}

void Territory::nextEat()
{

}

void Territory::nextGeneration()
{

}

bool Territory::isPlayer()
{
	return !Species::monsterSpecies[Civilizations::states[owner].monster].enemy;
}

void Territory::expand()
{
	bool aboveOk = true;
	bool belowOk = true;
	bool leftOk = true;
	bool rightOk = true;
	for(unsigned i = 0; i < objects.size(); i++)
	{
		if(objects[i] != this && objects[i]->getName() == TERRITORY)
		{
			if(objects[i]->getX() == x-8 && objects[i]->getY() == y)
			{
				leftOk = false;
			}
			if(objects[i]->getX() == x+8 && objects[i]->getY() == y)
			{
				rightOk = false;
			}
			if(objects[i]->getY() == y-8 && objects[i]->getX() == x)
			{
				aboveOk = false;
			}
			if(objects[i]->getY() == y+8 && objects[i]->getX() == x)
			{
				belowOk = false;
			}
		}
	}
	if(aboveOk)
	{
		Territory* t = new Territory(x,y-8);
		t->setOwner(owner,tribe);
		objects.push_back(t);
	}
	if(belowOk)
	{
		Territory* t = new Territory(x,y+8);
		t->setOwner(owner,tribe);
		objects.push_back(t);
	}
	if(leftOk)
	{
		Territory* t = new Territory(x-8,y);
		t->setOwner(owner,tribe);
		objects.push_back(t);
	}
	if(rightOk)
	{
		Territory* t = new Territory(x+8,y);
		t->setOwner(owner,tribe);
		objects.push_back(t);
	}
}

void Territory::nextMove()
{

}

int Territory::getCurrentSelection()
{
	std::vector<CityButton> buttons = CivHandler::getCityUI().getCityButtons();
	for(unsigned i = 0; i < buttons.size(); i++)
	{
		if(buttons[i].getStatus() == 1)
		{
			return i;
		}
	}
	return -1;
}

void Territory::tick()
{
	if(CivHandler::getCityUI().getRunning())
	{
		if(getClicking() && !occupied)
		{
			if(CivHandler::getDolurz() >= 10 && getCurrentSelection() == CityItems::ROAD)
			{
				CivHandler::removeDolurz(10);
				Road* r = new Road(x,y);
				r->setOwner(owner);
				r->setMaxTraffic(2);
				objects.push_back(r);
				expand();
			}
			if(CivHandler::getDolurz() >= 15 && getCurrentSelection() == CityItems::RESIDENTIAL)
			{
				CivHandler::removeDolurz(15);
				Residential* r = new Residential(x,y);
				r->setOwner(owner);
				objects.push_back(r);
				expand();
			}
			if(CivHandler::getDolurz() >= 15 && getCurrentSelection() == CityItems::FARM)
			{
				CivHandler::removeDolurz(15);
				Farm* r = new Farm(x,y);
				r->setOwner(owner);
				objects.push_back(r);
				expand();
			}
		}
		occupied = checkIfOccupied();
	}
}

bool Territory::checkIfOccupied()
{
	for(unsigned i = 0; i < objects.size(); i++)
	{
		if(objects[i] != this && objects[i]->getName() == BUILDING && objects[i]->getX() == x && objects[i]->getY() == y)
		{
			return true;
		}
	}
	return false;
}

void Territory::setOwner(int iOwner, bool iTribe)
{
	owner = iOwner;
	tribe = iTribe;
}

int Territory::getOwner()
{
	return owner;
}

void Territory::render()
{
	if(tribe)
	{
		int shade = (50+Civilizations::tribes[owner].baseFriendship)*3;
		Color c = {shade,shade,shade,255};
		DrawRectangle(x,y,8,8,darken(c,127));
		DrawRectangle(x+1,y+1,6,6,c);
	}
	else
	{
		DrawRectangle(x,y,8,8,darken(Civilizations::civColors[Civilizations::states[owner].myColor],127));
		if(!occupied)
		{
			DrawRectangle(x+1,y+1,6,6,Civilizations::civColors[Civilizations::states[owner].myColor]);
		}
	}

}

bool Territory::isTribal()
{
	return tribe;
}

Rectangle Territory::getBounds()
{
	Rectangle r;
	r.x = x;
	r.y = y;
	r.height = 8;
	r.width = 8;
	return r;
}

bool Territory::getClicking()
{

	bool clicking = false;
	if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
	{
		int mx = GetMouseX() / GameWindow::getCamera()->zoom - GameWindow::getCamera()->offset.x / GameWindow::getCamera()->zoom;
		int my = GetMouseY() / GameWindow::getCamera()->zoom - GameWindow::getCamera()->offset.y / GameWindow::getCamera()->zoom;
		mouseX = mx;
		mouseY = my;
		clicking = (mx >= x+1 && my >= y+1 && mx <= x+width-2 && my <= y+height-2);
		if(clicking && GetMouseX() < 480 && GetMouseY() < 352)
		{
			clickedHere = true;
		}
		else if(GetMouseX() < 480 && GetMouseY() < 352)
		{
			clickedHere = false;
		}
	}
	return clicking;
}
