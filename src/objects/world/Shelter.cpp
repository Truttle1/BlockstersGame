/*
 * Shelter.cpp
 *
 *  Created on: Jun 18, 2019
 *      Author: truttle1
 */

#include "Shelter.h"

Texture2D Shelter::basic0;
Texture2D Shelter::basic1;
Texture2D Shelter::simple0;
Texture2D Shelter::simple1;

Shelter::Shelter(int ix, int iy, int iSpecies, int iType, int iFood, int iPop) : GameObject(ix,iy,8,8)
{
	name = SHELTER;
	species = iSpecies;
	type = iType;
	food = iFood;
	population = iPop;
	alive = true;
	wasClicked = false;
	flashTime = 0;
	exitTime = 0;
	clickedHere = false;
	enemy = Species::monsterSpecies[species].enemy;
	Species::monsterSpecies[species].population += iPop;
}

Shelter::~Shelter()
{

}

void Shelter::kill()
{
	if(!alive)
	{
		alive = false;
		Species::monsterSpecies[species].population -= population;
	}
}

Rectangle Shelter::getBounds()
{
	Rectangle r;
	r.x = x+1;
	r.y = y+1;
	r.height = 6;
	r.width = 6;
	return r;

}
void Shelter::tick()
{
	if(food < 0)
	{
		food = 0;
	}
	if(population < 0)
	{
		alive = false;
	}
	if(!alive)
	{
		return;
	}
	if(type == 0)
	{
		if(population > 20)
		{
			population = 20;
		}
	}
	if(type == 1)
	{
		if(population > 30)
		{
			population = 30;
		}
	}
	enemy = Species::monsterSpecies[species].enemy;
	if(!UI::isOpen())
	{
		getClicking();
	}
	if(clickedHere && population > 0)
	{
		if(!enemy)
		{
			GameWindow::setShelterButton(3);
		}
		string owner = Species::monsterSpecies[species].name;
		GameWindow::showUpperText(owner + " Shelter\nPopulation: " + to_string(population) + "     Food: " + to_string(food));
		if(GameWindow::getShelterButton() == 3)
		{
			exit();
			GameWindow::finishClick();
		}
	}

	if(wasClicked && !clickedHere)
	{
		GameWindow::setShelterButton(0);
	}
	wasClicked = clickedHere;
}

void Shelter::deClick()
{
	clickedHere = false;
	if(wasClicked && !clickedHere)
	{
		GameWindow::setShelterButton(0);
	}
}

void Shelter::exit()
{
	int popVal = 7;
	while(popVal > population/2)
	{
		popVal--;
	}
	population -= popVal;
	Species::monsterSpecies[species].population -= popVal;
	food -= Species::monsterSpecies[species].metabolism;
	Monster* m = new Monster(x,y+8,species,enemy);
	m->loadFromFile(0,Species::monsterSpecies[species].metabolism,popVal);
	m->setShelterLoc(x,y);
	objects.push_back(m);
}

void Shelter::render()
{
	if(!alive)
	{
		return;
	}
	if(clickedHere)
	{
		flashTime++;
		if(flashTime > 30)
		{
			flashTime = 0;
		}
	}
	if(flashTime < 15 && clickedHere)
	{
		DrawRectangle(x,y,8,8,{0,255,255,255});
	}

	if(enemy)
	{
		if(type == 0)
		{
			DrawTexture(basic1,x,y,WHITE);
		}
		else
		{
			DrawTexture(simple1,x,y,WHITE);
		}
	}
	else
	{
		if(type == 0)
		{
			DrawTexture(basic0,x,y,WHITE);
		}
		else
		{
			DrawTexture(simple0,x,y,WHITE);
		}
	}
}

void Shelter::nextGeneration()
{
	food -= Species::monsterSpecies[species].metabolism * ((population/Species::monsterSpecies[species].groupSize)+1);

	if(food < 0)
	{
		int popRemove = population - (population / 4);
		if(popRemove <= 0)
		{
			popRemove = 1;
		}
		population -= popRemove;
		Species::monsterSpecies[species].population -= popRemove;
		food = 0;
	}
	else
	{
		population += (Species::monsterSpecies[species].groupSize*5) / (population+1);
		Species::monsterSpecies[species].population +=  (Species::monsterSpecies[species].groupSize*5) / (population+1);
	}

	if(population < 0)
	{
		alive = false;
	}

	if(enemy)
	{
		if(exitTime <= 0 && rand()%100 < 50 && food > Species::monsterSpecies[species].metabolism && food < (Species::monsterSpecies[species].groupSize) * 2)
		{
			exitTime = 2;
			exit();
		}
	}
	exitTime--;
}

void Shelter::nextMove()
{

}

void Shelter::nextEat()
{

}

bool Shelter::getClicking()
{

	bool clicking = false;
	if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
	{
		int mx = GetMouseX() / GameWindow::getCamera()->zoom - GameWindow::getCamera()->offset.x / GameWindow::getCamera()->zoom;
		int my = GetMouseY() / GameWindow::getCamera()->zoom - GameWindow::getCamera()->offset.y / GameWindow::getCamera()->zoom;
		mouseX = mx;
		mouseY = my;
		clicking = (mx >= x && my >= y && mx <= x+width && my <= y+height);
		if(clicking && GetMouseX() < 480)
		{
			clickedHere = true;
		}
		else if(GetMouseX() < 480)
		{
			clickedHere = false;
		}
	}
	return clicking;
}

int Shelter::getSpecies()
{
	return species;
}

int Shelter::getFood()
{
	return food;
}

int Shelter::getType()
{
	return type;
}

int Shelter::getPopulation()
{
	return population;
}

void Shelter::add(int iFood, int iPopulation)
{
	food += iFood;
	population += iPopulation;
	Species::monsterSpecies[species].population += iPopulation;
}

bool Shelter::getAlive()
{
	return alive;
}
