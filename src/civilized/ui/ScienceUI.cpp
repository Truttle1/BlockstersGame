/*
 * ScienceUI.cpp
 *
 *  Created on: Jul 19, 2019
 *      Author: truttle1
 */

#include "ScienceUI.h"

ScienceUI::ScienceUI()
{
}

ScienceUI::~ScienceUI()
{

}

void ScienceUI::init()
{

	ScienceButton combat = ScienceButton(96,16,50);
	addTexts.clear();
	addTexts.push_back("MILITIA");
	addTexts.push_back("Cost: 50 Dolurz");
	addTexts.push_back("Lets you build Warrior");
	addTexts.push_back("Units to fight against");
	addTexts.push_back("wild animals, tribes,");
	addTexts.push_back("and other citystates.");
	combat.init(LoadTexture("src/img/ui/science/combat0.png"),addTexts);
	sciButtons.push_back(combat);
	behave = -1;
}

void ScienceUI::toggle()
{
	if(!UI::isOpen() && !running)
	{
		setupButtons();
		running = true;
		open = true;
		behave = -1;
	}
	else if(UI::isOpen() && running)
	{
		running = false;
		open = false;
		closeButtons();
		behave = -1;
	}
}

void ScienceUI::closeButtons()
{

}

void ScienceUI::setColor(Color iColor)
{
	color = iColor;
}

bool ScienceUI::getRunning()
{
	return running;
}

void ScienceUI::tick()
{
	if(!open)
	{
		running = false;
	}
	for(unsigned i = 0; i<sciButtons.size(); i++)
	{
		sciButtons[i].tick();
	}
	if(getClicking(RESEARCH_X,RESEARCH_Y,224,32))
	{
		if(behave != -1 && sciButtons[behave].getCost() <= CivHandler::getDolurz() && sciButtons[behave].getStatus() == 1)
		{
			sciButtons[behave].setStatus(2);
			Civilizations::states[0].technologies[behave] = true;
			behave = -1;
		}
	}
}

bool ScienceUI::getClicking(int x, int y, int width, int height)
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

void ScienceUI::render()
{
	DrawRectangle(0,0,480,480,color);
	DrawRectangle(208,16,256,448,WHITE);
	sciTexts.clear();
	bool found = false;
	for(unsigned i = 0; i<sciButtons.size(); i++)
	{
		sciButtons[i].render();
		if(sciButtons[i].getStatus() == 1 || sciButtons[i].getStatus() == 3)
		{
			sciTexts = sciButtons[i].getText();
			behave = i;
			found = true;
		}
	}
	if(!found)
	{
		behave = -1;
	}
	if(behave > -1)
	{
		std::cout << sciTexts.size() << std::endl;
		DrawTextEx(font,sciTexts[0].c_str(),{242,32},48.0f,0.0f,BLACK); // @suppress("Invalid arguments")
		DrawTextEx(font,sciTexts[1].c_str(),{222,64},36.0f,0.0f,BLACK); // @suppress("Invalid arguments")
		if(sciTexts.size() > 2)
		{
			for(unsigned i = 2; i<sciTexts.size(); i++)
			{
				DrawTextEx(font,sciTexts[i].c_str(),{222,72+(20*i)},24.0f,0.0f,BLACK); // @suppress("Invalid arguments")
			}
		}
		if(sciButtons[behave].getStatus() <= 1)
		{
			DrawRectangle(RESEARCH_X,RESEARCH_Y,224,32,BLACK);
			DrawTextEx(font,"RESEARCH",{RESEARCH_X+64,RESEARCH_Y+4},24.0f,0.0f,WHITE); // @suppress("Invalid arguments")
			DrawTextEx(font,"RESEARCH",{RESEARCH_X+65,RESEARCH_Y+4},24.0f,0.0f,WHITE); // @suppress("Invalid arguments")

		}
		else
		{
			DrawRectangle(RESEARCH_X,RESEARCH_Y,224,32,{0,128,0,255});
			DrawTextEx(font,"RESEARCHED!",{RESEARCH_X+64,RESEARCH_Y+4},24.0f,0.0f,WHITE); // @suppress("Invalid arguments")
			DrawTextEx(font,"RESEARCHED!",{RESEARCH_X+65,RESEARCH_Y+4},24.0f,0.0f,WHITE); // @suppress("Invalid arguments")

		}
	}

}

void ScienceUI::setupButtons()
{
	sciButtons[Techs::COMBAT_0].enable();
}
