/*
 * CivHandler.cpp
 *
 *  Created on: Jun 26, 2019
 *      Author: truttle1
 */

#include "CivHandler.h"

UIButton CivHandler::cityUIButton;
UIButton CivHandler::scienceUIButton;
Texture2D CivHandler::cityButton;
Texture2D CivHandler::scienceButton;
CityUI CivHandler::cityUI;
int CivHandler::x;
int CivHandler::y;
int CivHandler::zoom;
int CivHandler::dolurz;
int CivHandler::population;
int CivHandler::taxes;
double CivHandler::taxRate;
double CivHandler::expenses;
double CivHandler::expenseRate;

static ScienceUI scienceUI;
CivHandler::CivHandler() {
	// TODO Auto-generated constructor stub

}

CivHandler::~CivHandler() {
	// TODO Auto-generated destructor stub
}

void CivHandler::render()
{

}

void CivHandler::doGeneration()
{
}

void CivHandler::tick()
{
	cityUIButton.tick();
	scienceUIButton.tick();
	if(cityUI.getRunning())
	{
		cityUI.setColor(getColor());
		cityUI.tick();
	}
	if(scienceUI.getRunning())
	{
		scienceUI.setColor(getColor());
		scienceUI.tick();
	}
	for(unsigned i = 0; i < GameObject::objects.size(); i++)
	{
		if(GameObject::objects[i]->isBuilding())
		{
			Building* bldg = static_cast<Building*>(GameObject::objects[i]);
			if(bldg->getDemolished())
			{
				delete(GameObject::objects[i]);
				GameObject::objects[i] = nullptr;
				GameObject::objects.erase(GameObject::objects.begin()+i);
			}

		}
	}
}

CityUI CivHandler::getCityUI()
{
	return cityUI;
}

void CivHandler::drawGUI()
{
	if(!UI::isOpen())
	{
		cityUIButton.render();
		scienceUIButton.render();
	}
	if(cityUI.getRunning())
	{
		cityUI.render();
	}
	if(scienceUI.getRunning())
	{
		scienceUI.render();
	}
	DrawTextEx(GameObject::font,("Pop: " + to_string(population)).c_str(),{488,200},24.0f,0.0f,BLACK);
	DrawTextEx(GameObject::font,("Pop: " + to_string(population)).c_str(),{489,200},24.0f,0.0f,BLACK);
}

void CivHandler::setDolurz(int set)
{
	dolurz = set;
}

void CivHandler::init()
{
	Civilizations::setStateColors();
	cityUI = CityUI();
	scienceUI = ScienceUI();
	cityButton = LoadTexture("src/img/ui/cityButton.png");
	scienceButton = LoadTexture("src/img/ui/scienceButton.png");
	cityUIButton = UIButton(496,48,32,32);
	cityUIButton.setImage(cityButton);
	cityUIButton.addUI(&cityUI);

	scienceUIButton = UIButton(528,48,32,32);
	scienceUIButton.setImage(scienceButton);
	scienceUIButton.addUI(&scienceUI);

	cityUI.loadFonts();
	cityUI.init();

	scienceUI.loadFonts();
	scienceUI.init();
	taxRate = 0.1;
	expenseRate = 1;

}

void CivHandler::doTurn()
{
	addTaxMoney();
	addExpenses();
	cityUI.nextGeneration();
}
void CivHandler::doMove()
{

}


void CivHandler::addCivilization(bool enemy, int monster, int color)
{
	State newState;
	std::cout << monster << std::endl;
	newState.monster = monster;
	newState.myColor = color;
	newState.started = false;
	Civilizations::states.push_back(newState);
}

Color CivHandler::getColor()
{
	return Civilizations::civColors[Civilizations::states[0].myColor];
}

void CivHandler::setOffsets(int iZoom, int iX, int iY)
{
	zoom = iZoom;
	x = iX;
	y = iY;
}

int CivHandler::getOffsetX()
{
	return x;
}

int CivHandler::getOffsetY()
{
	return y;
}

int CivHandler::getCameraZoom()
{
	return zoom;
}

int CivHandler::getDolurz()
{
	return dolurz;
}

void CivHandler::removeDolurz(int remove)
{
	dolurz -= remove;
}

int CivHandler::getPopulation()
{
	return population;
}

void CivHandler::addPopulation(int add)
{
	population += add;
}

void CivHandler::payTaxes(int money)
{
	taxes += money;
}

void CivHandler::addTaxMoney()
{
	double tax = taxes * taxRate;
	dolurz += tax * 5;
	taxes = 0;
}

void CivHandler::spend(double money)
{
	expenses += money;
}

void CivHandler::addExpenses()
{
	double exp = expenses * expenseRate;
	dolurz -= exp * 3;
	expenses = 0;
}
int CivHandler::getDemand(int demandVal)
{
	return cityUI.getDemand(demandVal);
}

void CivHandler::setDemand(int demandVal, int amount)
{
	return cityUI.setDemand(demandVal, amount);
}

bool CivHandler::getClicking(int x, int y, int width, int height)
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
