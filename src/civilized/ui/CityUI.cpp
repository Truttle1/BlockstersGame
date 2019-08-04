/*
 * CityUI.cpp
 *
 *  Created on: Jun 30, 2019
 *      Author: truttle1
 */

#include "CityUI.h"

CityUI::CityUI() : UI()
{
	demands.push_back(5);
	demands.push_back(0);
	demands.push_back(5);
}

CityUI::~CityUI()
{
}

void CityUI::close()
{
	closeButtons();
}

std::vector<CityButton> CityUI::getCityButtons()
{
	return cityButtons;
}

void CityUI::setDemand(int demandVal, int amount)
{
	demands[demandVal] = amount;
}

int CityUI::getDemand(int demandVal)
{
	return demands[demandVal];
}

void CityUI::nextGeneration()
{
	if(rand()%100 < 10 && demands[CityItems::DEMAND_RESIDENTIAL] <= 2)
	{
		demands[CityItems::DEMAND_RESIDENTIAL] += 4;
	}

	if(demands[CityItems::DEMAND_RESIDENTIAL] > 10)
	{
		demands[CityItems::DEMAND_RESIDENTIAL] = 10;
	}

	if(demands[CityItems::DEMAND_RESIDENTIAL] < 0)
	{
		demands[CityItems::DEMAND_RESIDENTIAL] = 0;
	}

	if(demands[CityItems::DEMAND_FOOD] > 10)
	{
		demands[CityItems::DEMAND_FOOD] = 10;
	}

	if(demands[CityItems::DEMAND_FOOD] < 0)
	{
		demands[CityItems::DEMAND_FOOD] = 0;
	}
}

void CityUI::tick()
{

	if(!open)
	{
		running = false;
	}
	for(unsigned i = 0; i < cityButtons.size(); i++)
	{
		cityButtons[i].tick();
		if(cityButtons[i].isRecentlyChanged())
		{
			for(unsigned j = 0; j < cityButtons.size(); j++)
			{
				if(i != j)
				{
					cityButtons[j].deselect();
				}
				cityButtons[i].doneChanging();
			}
		}
	}
}

void CityUI::render()
{
	DrawRectangle(0,416,480,64,color);
	cityTexts.clear();
	int behave;
	for(unsigned i = 0; i<cityButtons.size(); i++)
	{
		cityButtons[i].render();
		if(cityButtons[i].getStatus() == 1)
		{
			cityTexts = cityButtons[i].getText();
			behave = i;
		}
	}
	for(unsigned i = 0; i<cityTexts.size(); i++)
	{
		DrawTextEx(font,cityTexts[i].c_str(),{284,424+(20*i)},24.0f,0.0f,BLACK); // @suppress("Invalid arguments")
	}
	/*
	DrawRectangle(0,0,56,128,{64,64,64,255});
	DrawRectangle(8,8,8,4*demands[CityItems::DEMAND_RESIDENTIAL],GREEN);
	DrawRectangle(24,8,8,4*demands[CityItems::DEMAND_COMMERCIAL],BLUE);
	DrawRectangle(40,8,8,4*demands[CityItems::DEMAND_FOOD],YELLOW);
	*/
}

bool CityUI::getRunning()
{
	return running;
}

void CityUI::toggle()
{
	if(!UI::isOpen() && !running)
	{
		running = true;
		open = true;
		setupButtons();
	}
	else if(UI::isOpen() && running)
	{
		closeButtons();
		running = false;
		open = false;
	}
}

void CityUI::closeButtons()
{
	for(unsigned i = 0; i < cityButtons.size(); i++)
	{
		cityButtons[i].deselect();
	}
}

void CityUI::setupButtons()
{
	cityButtons[CityItems::BULLDOZER].enable();
	cityButtons[CityItems::ROAD].enable();
	cityButtons[CityItems::RESIDENTIAL].enable();
	cityButtons[CityItems::FARM].enable();
}

void CityUI::init()
{
	CityButton bulldozer = CityButton(16,432,10);
	addTexts.clear();
	addTexts.push_back("DEMOLISH:");
	addTexts.push_back("Cost: 10 Dolurz");
	bulldozer.init(LoadTexture("src/img/ui/city/bulldozer.png"),addTexts);
	cityButtons.push_back(bulldozer);

	CityButton road = CityButton(32,432,10);
	addTexts.clear();
	addTexts.push_back("ROAD:");
	addTexts.push_back("Cost: 10 Dolurz");
	road.init(LoadTexture("src/img/ui/city/street.png"),addTexts);
	cityButtons.push_back(road);

	CityButton house = CityButton(48,432,15);
	addTexts.clear();
	addTexts.push_back("RESIDENTIAL ZONE:");
	addTexts.push_back("Cost: 15 Dolurz");
	house.init(LoadTexture("src/img/ui/city/residential.png"),addTexts);
	cityButtons.push_back(house);

	CityButton farm = CityButton(64,432,15);
	addTexts.clear();
	addTexts.push_back("FARM ZONE:");
	addTexts.push_back("Cost: 15 Dolurz");
	farm.init(LoadTexture("src/img/ui/city/farm.png"),addTexts);
	cityButtons.push_back(farm);
}

void CityUI::setColor(Color iColor)
{
	color = iColor;
}
