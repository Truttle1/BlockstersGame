/*
 * PlantUI.cpp
 *
 *  Created on: Jan 24, 2019
 *      Author: truttle1
 */

#include "PlantUI.h"
#include <stdio.h>
typedef UI super;
PlantUI::PlantUI() : super(){
	running = false;
	//fontBig = LoadFontEx("src/SGK050.ttf",480,0,0);

}

PlantUI::~PlantUI() {
	// TODO Auto-generated destructor stub
}
void PlantUI::init()
{
	leftButton = LoadTexture("src/img/ui/leftButton.png");
	rightButton = LoadTexture("src/img/ui/rightButton.png");
	printf("hi\n");
}
void PlantUI::tick()
{
	if(running)
	{
		if(getClicking(leftButtonX,leftButtonY,32,32))
		{
			clickLeft();
		}
		if(getClicking(rightButtonX,rightButtonY,32,32))
		{
			clickRight();
		}
	}
	if(!open)
	{
		running = false;
	}
}
void PlantUI::render()
{
	if(running)
	{
		DrawRectangle(0,0,480,480,WHITE);
		if(Species::plantsDiscovered.size()>0)
		{
			curViewing = Species::plantsDiscovered[index];
			if(curViewing < Species::plantSpecies.size())
			{
				DrawTexturePro(Species::plantSpecies[curViewing].image,srcRect,destRect,origin,0,WHITE);
				drawStats();
			}
		}
		DrawTexture(leftButton,leftButtonX,leftButtonY,WHITE);
		DrawTexture(rightButton,rightButtonX,rightButtonY,WHITE);

	}
}
void PlantUI::close()
{

}
void PlantUI::toggle()
{
	if(!UI::isOpen() && !running)
	{
		running = true;
		open = true;
	}
	else if(UI::isOpen() && running)
	{
		running = false;
		open = false;
	}
}
bool PlantUI::getRunning()
{
	return running;
}
void PlantUI::drawStats()
{
	std::string num = "Plant #" + std::to_string(index);
	std::string pop = "Population: " + std::to_string(Species::plantSpecies[curViewing].population);
	DrawTextEx(font,num.c_str(),{256,64},48.0f,0.0f,BLACK);
	DrawTextEx(font,Species::plantSpecies[curViewing].name.c_str(),{256,108},24.0f,0.0f,BLACK);
	DrawTextEx(font,pop.c_str(),{16,172},24.0f,0.0f,BLACK);
	if(Species::plantSpecies[curViewing].land)
	{
		DrawTextEx(font,"Land Plant",{16,192},24.0f,0.0f,BLACK);
	}
	else
	{
		DrawTextEx(font,"Water Plant",{16,192},24.0f,0.0f,BLACK);
	}
	std::string nutrition = "Contains " + std::to_string(Species::plantSpecies[curViewing].nutrients) + " nutrients.";
	DrawTextEx(font,nutrition.c_str(),{16,212},24.0f,0.0f,BLACK);
	std::string grp = "";
	if(Species::plantSpecies[curViewing].groupSize<20)
	{
		grp = "Appears in small groups.";
	}
	else if(Species::plantSpecies[curViewing].groupSize<40)
	{
		grp = "Appears in medium-sized groups.";
	}
	else
	{
		grp = "Appears in large groups.";
	}
	DrawTextEx(font,grp.c_str(),{16,232},24.0f,0.0f,BLACK);
	std::string siz = "Size: ";
	std::string tox = "Toxity: ";
	if(Species::plantSpecies[curViewing].toxicity==0)
	{
		tox += "Non-Toxic";
	}
	else if(Species::plantSpecies[curViewing].toxicity<3)
	{
		tox += "Slightly Toxic";
	}
	else if(Species::plantSpecies[curViewing].toxicity<5)
	{
		tox += "Toxic";
	}
	else if(Species::plantSpecies[curViewing].toxicity<7)
	{
		tox += "Very Toxic";
	}
	else
	{
		tox += "Insanely Toxic";
	}


	if(Species::plantSpecies[curViewing].size<3)
	{
		siz += "Miniscule";
	}
	else if(Species::plantSpecies[curViewing].size<5)
	{
		siz += "Small";
	}
	else if(Species::plantSpecies[curViewing].size<7)
	{
		siz += "Medium";
	}
	else if(Species::plantSpecies[curViewing].size<9)
	{
		siz += "Large";
	}
	else if(Species::plantSpecies[curViewing].size<11)
	{
		siz += "Gargantuan";
	}

	DrawTextEx(font,siz.c_str(),{16,252},24.0f,0.0f,BLACK);
	std::string ls = "Lives for " + std::to_string(Species::plantSpecies[curViewing].lifespan) + " turns.";
	DrawTextEx(font,ls.c_str(),{16,272},24.0f,0.0f,BLACK);
	std::string sur = "Survives with " + std::to_string(Species::plantSpecies[curViewing].minDeath) + +"-"+ std::to_string(Species::plantSpecies[curViewing].maxDeath) + " neighbors.";
	DrawTextEx(font,sur.c_str(),{16,292},24.0f,0.0f,BLACK);
	std::string rep = "Reproduces with " + std::to_string(Species::plantSpecies[curViewing].minNew) + +"-"+ std::to_string(Species::plantSpecies[curViewing].maxNew) + " neighbors.";
	DrawTextEx(font,rep.c_str(),{16,312},24.0f,0.0f,BLACK);
	DrawTextEx(font,tox.c_str(),{226,140},24.0f,0.0f,BLACK);
}
void PlantUI::clickLeft()
{
	if(index>0)
	{
		index--;
	}
}
void PlantUI::clickRight()
{
	index++;
	if(index>=Species::plantsDiscovered.size())
	{
		index = Species::plantsDiscovered.size()-1;
	}
}
