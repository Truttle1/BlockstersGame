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
	editing = true;
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
	ColorBox red = ColorBox();
	red.init(200,72,RED);
	colors.push_back(red);
	ColorBox orange = ColorBox();
	orange.init(240,72,ORANGE);
	colors.push_back(orange);
	ColorBox yellow = ColorBox();
	yellow.init(280,72,YELLOW);
	colors.push_back(yellow);
	ColorBox green = ColorBox();
	green.init(320,72,GREEN);
	colors.push_back(green);
	ColorBox cyan = ColorBox();
	cyan.init(360,72,{0,255,255,255});
	colors.push_back(cyan);
	ColorBox blue = ColorBox();
	blue.init(400,72,BLUE);
	colors.push_back(blue);
	ColorBox magenta = ColorBox();
	magenta.init(440,72,MAGENTA);
	colors.push_back(magenta);

	ColorBox red1 = ColorBox();
	red1.init(200,112,{128,0,0,255});
	colors.push_back(red1);
	ColorBox orange1 = ColorBox();
	orange1.init(240,112,{128,64,0,255});
	colors.push_back(orange1);
	ColorBox yellow1 = ColorBox();
	yellow1.init(280,112,{128,128,0,255});
	colors.push_back(yellow1);
	ColorBox green1 = ColorBox();
	green1.init(320,112,{0,192,0,255});
	colors.push_back(green1);
	ColorBox cyan1 = ColorBox();
	cyan1.init(360,112,{0,128,128,255});
	colors.push_back(cyan1);
	ColorBox blue1 = ColorBox();
	blue1.init(400,112,{0,0,192,255});
	colors.push_back(blue1);
	ColorBox magenta1 = ColorBox();
	magenta1.init(440,112,{128,0,128,255});
	colors.push_back(magenta1);

	ColorBox red2 = ColorBox();
	red2.init(200,32,{255,128,128,255});
	colors.push_back(red2);
	ColorBox orange2 = ColorBox();
	orange2.init(240,32,{255,192,128,255});
	colors.push_back(orange2);
	ColorBox yellow2 = ColorBox();
	yellow2.init(280,32,{255,255,192,255});
	colors.push_back(yellow2);
	ColorBox green2 = ColorBox();
	green2.init(320,32,{128,255,128,255});
	colors.push_back(green2);
	ColorBox cyan2 = ColorBox();
	cyan2.init(360,32,{128,255,255,255});
	colors.push_back(cyan2);
	ColorBox blue2 = ColorBox();
	blue2.init(400,32,{128,128,255,255});
	colors.push_back(blue2);
	ColorBox magenta2 = ColorBox();
	magenta2.init(440,32,{255,128,255,255});
	colors.push_back(magenta2);

	ColorBox black = ColorBox();
	black.init(280,152,{0,0,0,255});
	colors.push_back(black);
	ColorBox gray = ColorBox();
	gray.init(320,152,{128,128,128,255});
	colors.push_back(gray);
	ColorBox white = ColorBox();
	white.init(360,152,{230,230,230,255});
	colors.push_back(white);

	birthChanceButton = RadioButton(64,286,font);
	birthChanceButton.addOption("No Change",0);
	birthChanceButton.addOption("+2 Fertility | -2 Lifespan",1);
	birthChanceButton.addOption("+2 Lifespan | -1 Fertility",1);

	immuneSystemButton = RadioButton(64,362,font);
	immuneSystemButton.addOption("No Change",0);
	immuneSystemButton.addOption("+2 Immune | -2 Lifespan",1);
	immuneSystemButton.addOption("+2 Lifespan | -1 Immune",1);

	sizeButton = RadioButton(64,286,font);
	sizeButton.addOption("No Change",0);
	sizeButton.addOption("+2 Size | -1 Toxicity",1);
	sizeButton.addOption("+2 Toxicity | -1 Size",1);

	sizeButton2 = RadioButton(64,362,font);
	sizeButton2.addOption("No Change",0);
	sizeButton2.addOption("+2 Size | -1 Lifespan",1);
	sizeButton2.addOption("+2 Lifespan | -1 Size",1);

	speedButton = RadioButton(64,286,font);
	speedButton.addOption("No Change",0);
	speedButton.addOption("+2 Speed | +1 Metabolism",1);
	speedButton.addOption("-2 Metabolism | -1 Speed",1);

	strengthButton = RadioButton(64,362,font);
	strengthButton.addOption("No Change",0);
	strengthButton.addOption("+2 Strength | -1 Defense",1);
	strengthButton.addOption("+2 Defense | -1 Strength",1);
}
void MonsterUI::initEditor(int species)
{
	speciesEditing = species;
	textBox = TextBox(32,172,Species::monsterSpecies[curViewing].name,font);
	Color* pixels = (Color*)(GetImageData(GetTextureData(Species::monsterSpecies[curViewing].image)));
	int ct = 0;
	for(int x=0; x<8; x++)
	{
		for(int y=0; y<8; y++)
		{
			grid[y][x] = pixels[ct];
			ct++;
		}
	}
}
void MonsterUI::tick()
{
	if(!editing)
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
	else
	{
		tickEditScreen();
	}

	if(!open)
	{
		running = false;
	}
}
void MonsterUI::render()
{
	if(running)
	{
		DrawRectangle(0,0,480,480,WHITE);
		if(!editing)
		{
			DrawTexturePro(Species::monsterSpecies[curViewing].image,srcRect,destRect,origin,0,WHITE);
			drawStats();
			DrawTexture(leftButton,leftButtonX,leftButtonY,WHITE);
			DrawTexture(rightButton,rightButtonX,rightButtonY,WHITE);
		}
		else if(editing)
		{
			drawEditScreen();
		}

	}
}
void MonsterUI::drawEditScreen()
{
	for(int x=0; x<8; x++)
	{
		for(int y=0; y<8; y++)
		{
			DrawRectangle((x*16)+32,(y*16)+32,16,16,grid[x][y]);
			DrawRectangleLines((x*16)+32,(y*16)+32,16,16,BLACK);
		}
	}
	for(unsigned int i = 0; i < colors.size(); i++)
	{
		colors[i].render();
	}
	textBox.render();
	calculateUpdates();
	if(page == 0)
	{
		birthChanceButton.render();
		immuneSystemButton.render();
		DrawTextEx(font,"Fertility:",{48,256},24.0f,0.0f,BLACK);
		DrawTextEx(font,"Immune System:",{48,332},24.0f,0.0f,BLACK);
		std::string ls = "Lives for " + std::to_string(lifespanUpdate) + " gen.";
		std::string rw = "Reproduces w/" + std::to_string(minNewUpdate) + "-" +
				std::to_string(maxNewUpdate);
		std::string sw = "Survives w/ " + std::to_string(minDeathUpdate) + "-" +
				std::to_string(maxDeathUpdate);
		DrawTextEx(font,ls.c_str(),{284,250},24.0f,0.0f,BLACK);
		DrawTextEx(font,rw.c_str(),{284,270},24.0f,0.0f,BLACK);
		DrawTextEx(font,"Neighbors",{284,290},24.0f,0.0f,BLACK);
		DrawTextEx(font,sw.c_str(),{284,320},24.0f,0.0f,BLACK);
		DrawTextEx(font,"Neighbors",{284,340},24.0f,0.0f,BLACK);
	}
	else if(page == 1)
	{
		sizeButton.render();
		sizeButton2.render();
		DrawTextEx(font,"Toxicity / Size:",{48,256},24.0f,0.0f,BLACK);
		DrawTextEx(font,"Lifespan / Size:",{48,332},24.0f,0.0f,BLACK);
		std::string ls = "Lives for " + std::to_string(lifespanUpdate) + " gen.";
		DrawTextEx(font,ls.c_str(),{284,250},24.0f,0.0f,BLACK);
		std::string tx = "Toxicity: " + std::to_string(toxicityUpdate) + " HP.";
		std::string sz = "Size: " + std::to_string(sizeUpdate);
		std::string sizeDesc;

		if(sizeUpdate<3)
		{
			sizeDesc += "Miniscule";
		}
		else if(sizeUpdate<5)
		{
			sizeDesc += "Small";
		}
		else if(sizeUpdate<7)
		{
			sizeDesc += "Medium";
		}
		else if(sizeUpdate<9)
		{
			sizeDesc += "Large";
		}
		else if(sizeUpdate<11)
		{
			sizeDesc += "Gargantuan";
		}

		DrawTextEx(font,tx.c_str(),{284,280},24.0f,0.0f,BLACK);
		DrawTextEx(font,sz.c_str(),{284,320},24.0f,0.0f,BLACK);
		DrawTextEx(font,sizeDesc.c_str(),{284,340},24.0f,0.0f,BLACK);
	}
	else if(page == 2)
	{
		strengthButton.render();
		speedButton.render();
		DrawTextEx(font,"Speed:",{48,256},24.0f,0.0f,BLACK);
		DrawTextEx(font,"Strength / Resiliance:",{48,332},24.0f,0.0f,BLACK);
		std::string sp = "Speed:" + std::to_string(speedUpdate) + " tiles/gen.";
		std::string st = "Strength:" + std::to_string(strengthUpdate) + " HP";
		std::string de = "Defense:" + std::to_string(resilUpdate) + " HP";
		std::string me = "Needs:" + std::to_string(metaUpdate) + " ntrnts/gen";
		DrawTextEx(font,sp.c_str(),{284,250},24.0f,0.0f,BLACK);
		DrawTextEx(font,st.c_str(),{284,280},24.0f,0.0f,BLACK);
		DrawTextEx(font,de.c_str(),{284,320},24.0f,0.0f,BLACK);
		DrawTextEx(font,me.c_str(),{284,360},24.0f,0.0f,BLACK);
	}
	DrawTextEx(font,"Traits:",{32,226},36.0f,0.0f,BLACK);
	DrawTextEx(font,"Traits:",{32,227},36.0f,0.0f,BLACK);
	DrawRectangle(276,248,4,190,BLUE);
	DrawTexture(leftButton,leftButtonX,leftButtonY,WHITE);
	DrawTexture(rightButton,rightButtonX-190,rightButtonY,WHITE);
}

void MonsterUI::calculateUpdates()
{
	lifespanUpdate = Species::monsterSpecies[curViewing].lifespan;
	minNewUpdate = Species::monsterSpecies[curViewing].minNew;
	maxNewUpdate = Species::monsterSpecies[curViewing].maxNew;
	minDeathUpdate = Species::monsterSpecies[curViewing].minDeath;
	maxDeathUpdate = Species::monsterSpecies[curViewing].maxDeath;
	sizeUpdate = Species::monsterSpecies[curViewing].size;
	toxicityUpdate = Species::monsterSpecies[curViewing].toxicity;
	strengthUpdate = Species::monsterSpecies[curViewing].strength;
	resilUpdate = Species::monsterSpecies[curViewing].resil;
	speedUpdate = Species::monsterSpecies[curViewing].speed;
	metaUpdate = Species::monsterSpecies[curViewing].metabolism;

	if(birthChanceButton.getSelected() == 1)
	{
		lifespanUpdate -= 2;
		minNewUpdate -= 1;
		maxNewUpdate += 1;
	}
	else if(birthChanceButton.getSelected() == 2)
	{
		lifespanUpdate += 2;
		minNewUpdate += 1;
		maxNewUpdate -= 1;
	}

	if(immuneSystemButton.getSelected() == 1)
	{
		lifespanUpdate -= 2;
		minDeathUpdate -= 1;
		maxDeathUpdate += 1;
	}
	else if(immuneSystemButton.getSelected() == 2)
	{
		lifespanUpdate += 2;
		minDeathUpdate += 1;
		maxDeathUpdate -= 1;
	}

	if(sizeButton.getSelected() == 1)
	{
		sizeUpdate += 2;
		toxicityUpdate--;
	}
	else if(sizeButton.getSelected() == 2)
	{
		sizeUpdate--;
		toxicityUpdate += 2;
	}

	if(sizeButton2.getSelected() == 1)
	{
		sizeUpdate += 2;
		lifespanUpdate--;
	}
	else if(sizeButton2.getSelected() == 2)
	{
		sizeUpdate--;
		lifespanUpdate += 2;
	}

	if(speedButton.getSelected() == 1)
	{
		speedUpdate += 2;
		metaUpdate++;
	}
	else if(speedButton.getSelected() == 2)
	{
		speedUpdate--;
		metaUpdate -= 2;
	}

	if(strengthButton.getSelected() == 1)
	{
		strengthUpdate += 2;
		resilUpdate--;
	}
	else if(strengthButton.getSelected() == 2)
	{
		resilUpdate += 2;
		strengthUpdate--;
	}
	if(speedUpdate < 1)
	{
		speedUpdate = 1;
	}
	if(metaUpdate < 1)
	{
		metaUpdate = 1;
	}
	if(strengthUpdate < 0)
	{
		strengthUpdate = 0;
	}
	if(resilUpdate < 0)
	{
		resilUpdate = 0;
	}

	while(minDeathUpdate < 0)
	{
		minDeathUpdate++;
		maxDeathUpdate++;
	}

	while(minNewUpdate < 0)
	{
		minNewUpdate++;
		maxNewUpdate++;
	}

	if(sizeUpdate < 1)
	{
		sizeUpdate = 1;
	}

	if(toxicityUpdate < 0)
	{
		toxicityUpdate = 0;
	}

	if(lifespanUpdate < 1)
	{
		lifespanUpdate = 1;
	}
}

void MonsterUI::tickEditScreen()
{
	for(unsigned int i = 0; i < colors.size(); i++)
	{
		colors[i].tick();
		if(colors[i].getSelected())
		{
			drawingColor = colors[i].getColor();
		}
	}
	textBox.tick();

	for(int x=0; x<8; x++)
	{
		for(int y=0; y<8; y++)
		{
			if(getClicking((x*16)+32,(y*16)+32,16,16))
			{
				if(grid[x][y].a > 100)
				{
					grid[x][y].a = 0;
				}
				else
				{
					grid[x][y].r = drawingColor.r;
					grid[x][y].g = drawingColor.g;
					grid[x][y].b = drawingColor.b;
					grid[x][y].a = 255;
				}
			}
		}
	}
	if(page == 0)
	{
		birthChanceButton.tick();
		immuneSystemButton.tick();
	}
	else if(page == 1)
	{
		sizeButton.tick();
		sizeButton2.tick();
	}
	else if(page == 2)
	{
		strengthButton.tick();
		speedButton.tick();
	}
	if(getClicking(leftButtonX,leftButtonY,32,32))
	{
		if(page > 0)
		{
			page--;
			printf("page %d\n",page);
		}
	}
	if(getClicking(rightButtonX-190,rightButtonY,32,32))
	{
		if(page < maxPage)
		{
			page++;
			printf("page %d\n",page);
		}
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
	std::string resil = "Defense: " + std::to_string(Species::monsterSpecies[curViewing].resil) + ".";
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

