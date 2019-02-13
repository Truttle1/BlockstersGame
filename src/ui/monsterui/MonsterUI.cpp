/*
 * MonsterUI.cpp
 *
 *  Created on: Jan 24, 2019
 *      Author: truttle1
 */

#include <stdio.h>

#include "MonsterUI.h"
typedef UI super;
MonsterUI::MonsterUI() : super(){
	running = false;
	//fontBig = LoadFontEx("src/SGK050.ttf",480,0,0);

}

MonsterUI::~MonsterUI() {
	// TODO Auto-generated destructor stub
}
void MonsterUI::init()
{
	leftButton = LoadTexture("src/img/ui/leftButton.png");
	rightButton = LoadTexture("src/img/ui/rightButton.png");
	printf("hi\n");
}
void MonsterUI::tick()
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
void MonsterUI::render()
{
	if(running)
	{
		DrawRectangle(0,0,480,480,WHITE);
		DrawTexturePro(Species::monsterSpecies[curViewing].image,srcRect,destRect,origin,0,WHITE);
		drawStats();
		DrawTexture(leftButton,leftButtonX,leftButtonY,WHITE);
		DrawTexture(rightButton,rightButtonX,rightButtonY,WHITE);

	}
}
void MonsterUI::close()
{

}
void MonsterUI::toggle()
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
bool MonsterUI::getRunning()
{
	return running;
}
void MonsterUI::drawStats()
{
	std::string num = "Monster #" + std::to_string(curViewing);
	std::string pop = "Population: " + std::to_string(Species::monsterSpecies[curViewing].population);
	DrawTextEx(font,num.c_str(),{236,64},48.0f,0.0f,BLACK);
	DrawTextEx(font,Species::monsterSpecies[curViewing].name.c_str(),{256,108},24.0f,0.0f,BLACK);
	if(Species::monsterSpecies[curViewing].enemy)
	{
		DrawTextEx(font,"RIVAL MONSTER",{256,128},24.0f,0.0f,BLUE);
	}
	DrawTextEx(font,pop.c_str(),{16,172},24.0f,0.0f,BLACK);
	if(Species::monsterSpecies[curViewing].land)
	{
		DrawTextEx(font,"Land Monster",{16,192},24.0f,0.0f,BLACK);
	}
	else
	{
		DrawTextEx(font,"Sea Monster",{16,192},24.0f,0.0f,BLACK);
	}
	std::string grp = "";
	if(Species::monsterSpecies[curViewing].groupSize<20)
	{
		grp = "Appears in small groups.";
	}
	else if(Species::monsterSpecies[curViewing].groupSize<40)
	{
		grp = "Appears in medium-sized groups.";
	}
	else
	{
		grp = "Appears in large groups.";
	}
	DrawTextEx(font,grp.c_str(),{16,232},24.0f,0.0f,BLACK);
	std::string siz = "Size: ";
	if(Species::monsterSpecies[curViewing].size<3)
	{
		siz += "Miniscule";
	}
	else if(Species::monsterSpecies[curViewing].size<5)
	{
		siz += "Small";
	}
	else if(Species::monsterSpecies[curViewing].size<7)
	{
		siz += "Medium";
	}
	else if(Species::monsterSpecies[curViewing].size<9)
	{
		siz += "Large";
	}
	else if(Species::monsterSpecies[curViewing].size<11)
	{
		siz += "Gargantuan";
	}
	DrawTextEx(font,siz.c_str(),{16,252},24.0f,0.0f,BLACK);
	std::string ls = "Lives for " + std::to_string(Species::monsterSpecies[curViewing].lifespan) + " generations.";
	DrawTextEx(font,ls.c_str(),{16,272},24.0f,0.0f,BLACK);
	std::string sur = "Survives with " + std::to_string(Species::monsterSpecies[curViewing].minDeath) + +"-"+ std::to_string(Species::monsterSpecies[curViewing].maxDeath) + " neighbors.";
	DrawTextEx(font,sur.c_str(),{16,292},24.0f,0.0f,BLACK);
	std::string rep = "Reproduces with " + std::to_string(Species::monsterSpecies[curViewing].minNew) + +"-"+ std::to_string(Species::monsterSpecies[curViewing].maxNew) + " neighbors.";
	DrawTextEx(font,rep.c_str(),{16,312},24.0f,0.0f,BLACK);
	std::string strength = "Strength: " + std::to_string(Species::monsterSpecies[curViewing].strength) + ".";
	DrawTextEx(font,strength.c_str(),{16,332},24.0f,0.0f,BLACK);
	std::string resil = "Resiliance: " + std::to_string(Species::monsterSpecies[curViewing].resil) + ".";
	DrawTextEx(font,resil.c_str(),{16,352},24.0f,0.0f,BLACK);
	std::string spd = "Moves " + std::to_string(Species::monsterSpecies[curViewing].speed) + " tiles per generation.";
	DrawTextEx(font,spd.c_str(),{16,372},24.0f,0.0f,BLACK);
	std::string met = "Requires " + std::to_string(Species::monsterSpecies[curViewing].metabolism) + " nutrients per generation.";
	DrawTextEx(font,met.c_str(),{16,392},24.0f,0.0f,BLACK);
}
void MonsterUI::clickLeft()
{
	if(curViewing>0)
	{
		curViewing--;
	}
}
void MonsterUI::clickRight()
{
	curViewing++;
	if(curViewing>=Species::monsterSpecies.size())
	{
		curViewing = Species::monsterSpecies.size()-1;
	}
}
