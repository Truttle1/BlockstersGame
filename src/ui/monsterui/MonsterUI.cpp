/*
 * MonsterUI.cpp
 *
 *  Created on: Jan 24, 2019
 *      Author: truttle1
 */

#include <stdio.h>

#include "MonsterUI.h"
#include "../../objects/world/Monster.h"
#include "../../img/MonsterImg.h"
typedef UI super;
MonsterUI::MonsterUI() : super()
{
	running = false;
	editing = false;
	//fontBig = LoadFontEx("src/SGK050.ttf",480,0,0);
	lookingAtPlayer = true;
	index = 0;
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
	green.init(320,72,{0,192,0,255});
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
	green1.init(320,112,{0,128,0,255});
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
	green2.init(320,32,{0,255,0,255});
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
	sizeButton.addOption("+1 Size | -1 Toxicity",1);
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

	carnivoreButton = RadioButton(64,286,font);
	carnivoreButton.addOption("No Change",0);
	carnivoreButton.addOption("Become Carnivore",1);
	carnivoreButton.addOption("Become Herbivore",1);

	hostilityButton = RadioButton(64,362,font);
	hostilityButton.addOption("No Change",0);
	hostilityButton.addOption("+1 Hostility",1);
	hostilityButton.addOption("-1 Hostility",1);

	currentCost = 1;
	initBehaviors();
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
		if(viewingBehaviors)
		{
			for(unsigned int i=0; i<behaviors.size(); i++)
			{
				behaviors[i].tick();
			}
		}


		if(getClicking(behaveToggleX,behaveToggleY,128,32) && GameWindow::tutorial[99])
		{
			viewingBehaviors = !viewingBehaviors;
			if(viewingBehaviors)
			{
				setupBehaveIcons();
			}
		}

		if(getClicking(leftButtonX,leftButtonY,32,32) && !viewingBehaviors)
		{
			clickLeft();
			setupBehaveIcons();
		}
		if(getClicking(rightButtonX,rightButtonY,32,32) && !viewingBehaviors)
		{
			clickRight();
			setupBehaveIcons();
		}
		if(getClicking(editButtonX,editButtonY,82,32) && Species::monsterSpecies[curViewing].population > 0)
		{
			viewingBehaviors = false;
			birthChanceButton.reset();
			immuneSystemButton.reset();
			sizeButton.reset();
			sizeButton2.reset();
			speedButton.reset();
			strengthButton.reset();
			carnivoreButton.reset();
			hostilityButton.reset();
			editing = true;
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

			setupBehaveIcons();

			textBox.setText(Species::generateName());
		}
		if(getClicking(switchButtonX,switchButtonY,128,32))
		{
			cout << "MADE IT" << endl;
			lookingAtPlayer = !lookingAtPlayer;
			index = 0;
		}
	}
	else
	{
		tickEditScreen();
	}

	if(!open)
	{
		lookingAtPlayer = true;
		index = 0;
		running = false;
	}
	if(running && !editing)
	{
		if(IsKeyPressed(KEY_P))
		{
			cout << "MADE IT" << endl;
			lookingAtPlayer = !lookingAtPlayer;
		}
	}
}
void MonsterUI::render()
{
	if(running)
	{
		DrawRectangle(0,0,480,480,WHITE);
		//cout << Species::plMonstersDiscovered.size();
		if(!editing && (lookingAtPlayer ? Species::plMonstersDiscovered.size() : Species::monstersDiscovered.size()) > 0)
		{
			curViewing = lookingAtPlayer ? Species::plMonstersDiscovered[index] : Species::monstersDiscovered[index];
			DrawTexturePro(Species::monsterSpecies[curViewing].image,srcRect,destRect,origin,0,WHITE);
			if(viewingBehaviors)
			{

				behaveTexts.clear();
				int behave;
				for(unsigned int i=0; i<behaviors.size(); i++)
				{
					behaviors[i].render();
					if(behaviors[i].getStatus() == 1 || behaviors[i].getStatus() == 3)
					{
						behaveTexts = behaviors[i].getText();
						behave = i;
					}
				}
				for(unsigned int i=0; i<behaveTexts.size(); i++)
				{
					DrawTextEx(font,behaveTexts[i].c_str(),{284,250+(20*i)},24.0f,0.0f,BLACK); // @suppress("Invalid arguments")
				}
			}
			else
			{
				drawStats();
			}
			if(!viewingBehaviors)
			{
				DrawTexture(leftButton,leftButtonX,leftButtonY,WHITE);
				DrawTexture(rightButton,rightButtonX,rightButtonY,WHITE);
			}

			if(Species::monsterSpecies[curViewing].enemy == false && Species::monsterSpecies[curViewing].population > 0)
			{
				DrawRectangle(editButtonX,editButtonY,82,32,BLACK);
				DrawTextEx(font,"Evolve",{editButtonX+8.0f,editButtonY+4.0f},24.0f,0.0f,WHITE);
				DrawTextEx(font,"Evolve",{editButtonX+9.0f,editButtonY+4.0f},24.0f,0.0f,WHITE);
			}

			if(GameWindow::tutorial[99])
			{
				DrawRectangle(behaveToggleX,behaveToggleY,128,32,BLACK);
				if(viewingBehaviors)
				{
					DrawTextEx(font,"Traits",{behaveToggleX+28.0f,behaveToggleY+4.0f},24.0f,0.0f,WHITE);
					DrawTextEx(font,"Traits",{behaveToggleX+29.0f,behaveToggleY+4.0f},24.0f,0.0f,WHITE);
				}
				else
				{
					DrawTextEx(font,"Behaviors",{behaveToggleX+13.0f,behaveToggleY+4.0f},24.0f,0.0f,WHITE);
					DrawTextEx(font,"Behaviors",{behaveToggleX+14.0f,behaveToggleY+4.0f},24.0f,0.0f,WHITE);
				}
			}
			Color col;
			const char* str;
			if(lookingAtPlayer)
			{
				col = BLUE;
				str = "Player Monsters";
			}
			else
			{
				col = RED;
				str = "Rival Monsters";
			}
			DrawRectangle(switchButtonX,switchButtonY,128,32,col);
			DrawTextEx(font,str,{switchButtonX+4.0f,switchButtonY+4.0f},18.0f,0.0f,WHITE);



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
	if(page == 2)
	{
		birthChanceButton.render();
		immuneSystemButton.render();
		DrawTextEx(font,"Fertility:",{48,256},24.0f,0.0f,BLACK);
		DrawTextEx(font,"Immune System:",{48,332},24.0f,0.0f,BLACK);
		std::string ls = "Lives for " + std::to_string(lifespanUpdate) + " turns.";
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
	else if(page == 0)
	{
		sizeButton.render();
		sizeButton2.render();
		DrawTextEx(font,"Toxicity / Size:",{48,256},24.0f,0.0f,BLACK);
		DrawTextEx(font,"Lifespan / Size:",{48,332},24.0f,0.0f,BLACK);
		std::string ls = "Lives for " + std::to_string(lifespanUpdate) + " turns.";
		DrawTextEx(font,ls.c_str(),{284,250},24.0f,0.0f,BLACK);
		std::string tx = "Toxicity: " + std::to_string(toxicityUpdate) + " HP.";

		std::string tox = "";
		if(toxicityUpdate==0)
		{
			tox += "Non-Toxic";
		}
		else if(toxicityUpdate<3)
		{
			tox += "Slightly Toxic";
		}
		else if(toxicityUpdate<5)
		{
			tox += "Toxic";
		}
		else if(toxicityUpdate<7)
		{
			tox += "Very Toxic";
		}
		else
		{
			tox += "Insanely Toxic";
		}
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
		DrawTextEx(font,tox.c_str(),{284,300},24.0f,0.0f,BLACK);
		DrawTextEx(font,sz.c_str(),{284,320},24.0f,0.0f,BLACK);
		DrawTextEx(font,sizeDesc.c_str(),{284,340},24.0f,0.0f,BLACK);
	}
	else if(page == 1)
	{
		strengthButton.render();
		speedButton.render();
		DrawTextEx(font,"Speed:",{48,256},24.0f,0.0f,BLACK);
		DrawTextEx(font,"Strength / Resiliance:",{48,332},24.0f,0.0f,BLACK);
		std::string sp = "Speed:" + std::to_string(speedUpdate) + " tiles/turn.";
		std::string st = "Strength:" + std::to_string(strengthUpdate) + " HP";
		std::string de = "Defense:" + std::to_string(resilUpdate) + " HP";
		std::string me = "Needs:" + std::to_string(metaUpdate) + " HP/turn";
		DrawTextEx(font,sp.c_str(),{284,250},24.0f,0.0f,BLACK);
		DrawTextEx(font,st.c_str(),{284,280},24.0f,0.0f,BLACK);
		DrawTextEx(font,de.c_str(),{284,320},24.0f,0.0f,BLACK);
		DrawTextEx(font,me.c_str(),{284,360},24.0f,0.0f,BLACK);
	}
	else if(page == 3)
	{
		carnivoreButton.render();
		hostilityButton.render();
		DrawTextEx(font,"Diet:",{48,256},24.0f,0.0f,BLACK);
		DrawTextEx(font,"Hostility:",{48,332},24.0f,0.0f,BLACK);
		std::string ls;
		if(carnivoreUpdate)
		{
			ls = "Carnivore";
		}
		else
		{
			ls = "Herbivore";
		}
		DrawTextEx(font,ls.c_str(),{284,250},24.0f,0.0f,BLACK);
		std::string sz = "Hostility: " + std::to_string(hostilityUpdate);
		std::string sizeDesc;

		if(hostilityUpdate<3)
		{
			sizeDesc += "Peaceful";
		}
		else if(hostilityUpdate<5)
		{
			sizeDesc += "Normal";
		}
		else if(hostilityUpdate<7)
		{
			sizeDesc += "Aggressive";
		}
		else if(hostilityUpdate<11)
		{
			sizeDesc += "Hostile";
		}
		DrawTextEx(font,sz.c_str(),{284,320},24.0f,0.0f,BLACK);
		DrawTextEx(font,sizeDesc.c_str(),{284,340},24.0f,0.0f,BLACK);
	}
	else if(page == 4)
	{
		renderBehaviors();
	}
	std::string cost = "COST: " + to_string(currentCost) + " Evolve Pts.";
	DrawTextEx(font,cost.c_str(),{284,400},24.0f,0.0f,BLACK);
	if(page <= 3)
	{
		DrawTextEx(font,"Traits:",{32,226},36.0f,0.0f,BLACK);
		DrawTextEx(font,"Traits:",{32,227},36.0f,0.0f,BLACK);
	}
	else
	{
		DrawTextEx(font,"Behaviors:",{32,226},36.0f,0.0f,BLACK);
		DrawTextEx(font,"Behaviors:",{32,227},36.0f,0.0f,BLACK);
	}
	DrawRectangle(276,248,4,190,BLUE);
	DrawTexture(leftButton,leftButtonX,leftButtonY,WHITE);
	DrawTexture(rightButton,rightButtonX-190,rightButtonY,WHITE);
	DrawTexture(rightButton,rightButtonX-190,rightButtonY,WHITE);
	DrawRectangle(saveButtonX,saveButtonY,64,32,BLACK);
	DrawTextEx(font,"Save",{saveButtonX+8.0f,saveButtonY+4.0f},24.0f,0.0f,WHITE);
	DrawTextEx(font,"Save",{saveButtonX+9.0f,saveButtonY+4.0f},24.0f,0.0f,WHITE);

	DrawRectangle(saveButtonX-72,saveButtonY,64,32,BLACK);
	DrawTextEx(font,"Close",{saveButtonX-72+8.0f,saveButtonY+4.0f},24.0f,0.0f,WHITE);
	DrawTextEx(font,"Close",{saveButtonX-72+9.0f,saveButtonY+4.0f},24.0f,0.0f,WHITE);
}

void MonsterUI::saveMonster()
{
	MonsterSpecies monster = Species::monsterSpecies[curViewing];
	int groupSize = monster.groupSize;
	int agression = monster.agression;
	bool carnivore = monster.carnivore;

	MonsterSpecies newSp = MonsterSpecies();
	newSp.complexity = monster.complexity + 1;
	newSp.land = monster.land;
	newSp.toxicity = toxicityUpdate;
	newSp.size = sizeUpdate;
	newSp.lifespan = lifespanUpdate;
	newSp.groupSize = groupSize;
	newSp.minNew = minNewUpdate;
	newSp.maxNew = maxNewUpdate;
	newSp.minDeath = minDeathUpdate;
	newSp.maxDeath = maxDeathUpdate;
	newSp.agression = hostilityUpdate;
	newSp.carnivore = carnivoreUpdate;

	newSp.resil = resilUpdate;
	newSp.strength = strengthUpdate;
	newSp.speed = speedUpdate;
	newSp.metabolism = metaUpdate;
	newSp.image = monster.image;


	newSp.name = textBox.getText();
	newSp.enemy = false;
	int monsterX;
	int monsterY;
	int newX = ((rand()%5)*8)-16;
	int newY = ((rand()%5)*8)-16;

	Texture tex = LoadTextureFromImage(GetTextureData((newSp.image)));
	Color pixels[64];
	int c = 0;
	for(int x=0; x<8; x++)
	{
		for(int y=0; y<8; y++)
		{
			pixels[c].r = grid[y][x].r;
			pixels[c].g = grid[y][x].g;
			pixels[c].b = grid[y][x].b;
			pixels[c].a = grid[y][x].a;
			c++;
		}
	}
	UpdateTexture(tex,pixels);
	newSp.image = tex;
	for(int i=0; i<behaviors.size(); i++)
	{
		newSp.behaviors[i] = behaviors[i].getStatus() >= 2;
	}
	Species::monsterSpecies.push_back(newSp);
	Species::plMonstersDiscovered.push_back(Species::monsterSpecies.size()-1);

	for(unsigned int i = 3600; i < GameObject::objects.size(); i++)
	{
		if(GameObject::objects[i]->getName() == MONSTER)
		{
			Monster* monst = static_cast<Monster*>(GameObject::objects[i]);
			if(monst->getSpecies() == curViewing)
			{
				monsterX = monst->getX();
				monsterY = monst->getY();
			}
		}
	}
	Monster* p = new Monster(monsterX+newX,monsterY+newY,Species::monsterSpecies.size()-1,false);
	GameObject::objects.push_back(p);
	int r = rand()%5;
	for(int i=0; i<(r)+1;i++)
	{
		newX = ((rand()%6)*8)-32;
		newY = ((rand()%6)*8)-32;
		Monster* p = new Monster(monsterX+newX,monsterY+newY,Species::monsterSpecies.size()-1,false);
		Monster* p1 = new Monster(monsterX+newX,monsterY+newY+8,Species::monsterSpecies.size()-1,false);
		GameObject::objects.push_back(p);
		GameObject::objects.push_back(p1);
	}
	editing = false;
	curViewing = Species::monsterSpecies.size()-1;
	index = Species::monstersDiscovered.size()-1;


}

void MonsterUI::calculateUpdates()
{
	currentCost = 1;
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
	hostilityUpdate = Species::monsterSpecies[curViewing].agression;
	carnivoreUpdate = Species::monsterSpecies[curViewing].carnivore;

	for(unsigned int i = 0; i < behaviors.size(); i++)
	{
		if(behaviors[i].getStatus() >= 2 && !Species::monsterSpecies[curViewing].behaviors[i])
		{
			currentCost += behaviors[i].getCost();
		}
	}
	if(birthChanceButton.getSelected() == 1)
	{
		lifespanUpdate -= 2;
		minNewUpdate -= 1;
		maxNewUpdate += 1;

		currentCost++;
	}
	else if(birthChanceButton.getSelected() == 2)
	{
		lifespanUpdate += 2;
		minNewUpdate += 1;
		maxNewUpdate -= 1;

		currentCost++;
	}

	if(immuneSystemButton.getSelected() == 1)
	{
		lifespanUpdate -= 2;
		minDeathUpdate -= 1;
		maxDeathUpdate += 1;

		currentCost++;
	}
	else if(immuneSystemButton.getSelected() == 2)
	{
		lifespanUpdate += 2;
		minDeathUpdate += 1;
		maxDeathUpdate -= 1;

		currentCost++;
	}

	if(sizeButton.getSelected() == 1)
	{
		sizeUpdate += 1;
		toxicityUpdate--;

		currentCost++;
	}
	else if(sizeButton.getSelected() == 2)
	{
		sizeUpdate--;
		toxicityUpdate += 2;

		currentCost++;
	}

	if(sizeButton2.getSelected() == 1)
	{
		sizeUpdate += 2;
		lifespanUpdate--;

		currentCost++;
	}
	else if(sizeButton2.getSelected() == 2)
	{
		sizeUpdate--;
		lifespanUpdate += 2;

		currentCost++;
	}

	if(speedButton.getSelected() == 1)
	{
		speedUpdate += 2;
		metaUpdate++;

		currentCost++;
	}
	else if(speedButton.getSelected() == 2)
	{
		speedUpdate--;
		metaUpdate -= 2;

		currentCost++;
	}

	if(strengthButton.getSelected() == 1)
	{
		strengthUpdate += 2;
		resilUpdate--;

		currentCost++;
	}
	else if(strengthButton.getSelected() == 2)
	{
		resilUpdate += 2;
		strengthUpdate--;

		currentCost++;
	}

	if(carnivoreButton.getSelected() == 1)
	{
		carnivoreUpdate = true;

		currentCost++;
	}
	else if(carnivoreButton.getSelected() == 2)
	{
		carnivoreUpdate = false;

		currentCost++;
	}

	if(hostilityButton.getSelected() == 1)
	{
		hostilityUpdate++;

		currentCost++;
	}
	else if(hostilityButton.getSelected() == 2)
	{
		hostilityUpdate--;

		currentCost++;
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
	if(hostilityUpdate > 10)
	{
		hostilityUpdate = 10;
	}

	if(hostilityUpdate < 0)
	{
		hostilityUpdate = 0;
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


	if(GameObject::generation >= 30)
	{
		maxPage = 4;
	}
	else
	{
		maxPage = 3;
	}
	for(int x=0; x<8; x++)
	{
		for(int y=0; y<8; y++)
		{
			if(getClicking((x*16)+32,(y*16)+32,15,15))
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
	if(page == 2)
	{
		birthChanceButton.tick();
		immuneSystemButton.tick();
	}
	else if(page == 0)
	{
		sizeButton.tick();
		sizeButton2.tick();
	}
	else if(page == 1)
	{
		strengthButton.tick();
		speedButton.tick();
	}
	else if(page == 3)
	{
		carnivoreButton.tick();
		hostilityButton.tick();
	}
	else if(page == 4)
	{
		tickBehaviors();
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
	if(getClicking(saveButtonX,saveButtonY,64,32))
	{
		if(GameWindow::getPoints() >= currentCost)
		{
			saveMonster();
			GameWindow::removePoints(currentCost);
		}
		index = Species::plMonstersDiscovered.size() - 1;
	}
	if(getClicking(saveButtonX-72,saveButtonY,64,32))
	{
		editing = false;
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
	std::string num = "Monster #" + std::to_string(index);
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

	std::string host = "";
	if(Species::monsterSpecies[curViewing].agression<3)
	{
		host += "Peaceful";
	}
	else if(Species::monsterSpecies[curViewing].agression<5)
	{
		host += "Normal";
	}
	else if(Species::monsterSpecies[curViewing].agression<7)
	{
		host += "Aggressive";
	}
	else if(Species::monsterSpecies[curViewing].agression<11)
	{
		host += "Hostile";
	}

	std::string tox = "Toxicity: ";
	if(Species::monsterSpecies[curViewing].toxicity==0)
	{
		tox += "Non-Toxic";
	}
	else if(Species::monsterSpecies[curViewing].toxicity<3)
	{
		tox += "Slightly Toxic";
	}
	else if(Species::monsterSpecies[curViewing].toxicity<5)
	{
		tox += "Toxic";
	}
	else if(Species::monsterSpecies[curViewing].toxicity<7)
	{
		tox += "Very Toxic";
	}
	else
	{
		tox += "Insanely Toxic";
	}
	DrawTextEx(font,siz.c_str(),{16,252},24.0f,0.0f,BLACK);
	std::string ls = "Lives for " + std::to_string(Species::monsterSpecies[curViewing].lifespan) + " turns.";
	DrawTextEx(font,ls.c_str(),{16,272},24.0f,0.0f,BLACK);
	std::string sur = "Survives with " + std::to_string(Species::monsterSpecies[curViewing].minDeath) + +"-"+ std::to_string(Species::monsterSpecies[curViewing].maxDeath) + " neighbors.";
	DrawTextEx(font,sur.c_str(),{16,292},24.0f,0.0f,BLACK);
	std::string rep = "Reproduces with " + std::to_string(Species::monsterSpecies[curViewing].minNew) + +"-"+ std::to_string(Species::monsterSpecies[curViewing].maxNew) + " neighbors.";
	DrawTextEx(font,rep.c_str(),{16,312},24.0f,0.0f,BLACK);
	std::string strength = "Strength: " + std::to_string(Species::monsterSpecies[curViewing].strength) + ".";
	DrawTextEx(font,strength.c_str(),{16,332},24.0f,0.0f,BLACK);
	std::string resil = "Defense: " + std::to_string(Species::monsterSpecies[curViewing].resil) + ".";
	DrawTextEx(font,resil.c_str(),{16,352},24.0f,0.0f,BLACK);
	std::string spd = "Moves " + std::to_string(Species::monsterSpecies[curViewing].speed) + " tiles per turn.";
	DrawTextEx(font,spd.c_str(),{16,372},24.0f,0.0f,BLACK);
	std::string met = "Requires " + std::to_string(Species::monsterSpecies[curViewing].metabolism) + " nutrients per turn.";
	DrawTextEx(font,met.c_str(),{16,392},24.0f,0.0f,BLACK);
	if(Species::monsterSpecies[curViewing].carnivore)
	{
		DrawTextEx(font,"CARNIVORE",{256,220},24.0f,0.0f,BLACK);
	}
	DrawTextEx(font,tox.c_str(),{226,140},24.0f,0.0f,BLACK);
	std::string hos = "Hostility: " + host;
	DrawTextEx(font,hos.c_str(),{16,412},24.0f,0.0f,BLACK);
}
void MonsterUI::clickLeft()
{
	if(index>0)
	{
		index--;
	}
	else
	{
		if(lookingAtPlayer)
		{
			index = Species::plMonstersDiscovered.size()-1;
		}
		if(!lookingAtPlayer)
		{
			index = Species::monstersDiscovered.size()-1;
		}
	}
}
void MonsterUI::clickRight()
{
	index++;
	if(index>=Species::plMonstersDiscovered.size() && lookingAtPlayer)
	{
		index = 0;
	}
	if(index>=Species::monstersDiscovered.size() && !lookingAtPlayer)
	{
		index = 0;
	}
}

//Behaviors

void MonsterUI::initBehaviors()
{
	//Run Away Behavior
	Behavior run = Behavior(32,288,2);
	std::vector<std::string> addTexts;
	addTexts.push_back("Your monster will");
	addTexts.push_back("run from other");
	addTexts.push_back("monsters.");
	addTexts.push_back("");
	addTexts.push_back("Cost: 2 Pts");
	run.init(LoadTexture("src/img/ui/behaviors/run.png"),addTexts);
	run.enable();
	behaviors.push_back(run);

	Behavior chase = Behavior(32,336,2);
	addTexts.clear();
	addTexts.push_back("Your monster will");
	addTexts.push_back("run towards other");
	addTexts.push_back("monsters.");
	addTexts.push_back("");
	addTexts.push_back("Cost: 2 Pts");
	chase.init(LoadTexture("src/img/ui/behaviors/chase.png"),addTexts);
	chase.enable();
	behaviors.push_back(chase);

	Behavior spread = Behavior(48,304,3);
	addTexts.clear();
	addTexts.push_back("Your monsters will");
	addTexts.push_back("tend to spread");
	addTexts.push_back("out.");
	addTexts.push_back("");
	addTexts.push_back("Cost: 3 Pts");
	spread.init(LoadTexture("src/img/ui/behaviors/spread.png"),addTexts);
	behaviors.push_back(spread);

	Behavior together = Behavior(64,304,3);
	addTexts.clear();
	addTexts.push_back("Your monsters will");
	addTexts.push_back("tend to group");
	addTexts.push_back("together.");
	addTexts.push_back("");
	addTexts.push_back("Cost: 3 Pts");
	together.init(LoadTexture("src/img/ui/behaviors/together.png"),addTexts);
	behaviors.push_back(together);

	Behavior plants = Behavior(48,320,2);
	addTexts.clear();
	addTexts.push_back("Your monsters will");
	addTexts.push_back("try to move toward");
	addTexts.push_back("plants.");
	addTexts.push_back("");
	addTexts.push_back("Cost: 2 Pts");
	plants.init(LoadTexture("src/img/ui/behaviors/seekplant.png"),addTexts);
	behaviors.push_back(plants);

	Behavior meat1 = Behavior(64,320,4);
	addTexts.clear();
	addTexts.push_back("Your monsters will");
	addTexts.push_back("try to move toward");
	addTexts.push_back("meat.");
	addTexts.push_back("");
	addTexts.push_back("Cost: 4 Pts");
	meat1.init(LoadTexture("src/img/ui/behaviors/gotomeat.png"),addTexts);
	behaviors.push_back(meat1);

	Behavior meat2 = Behavior(80,320,5);
	addTexts.clear();
	addTexts.push_back("Your monsters will");
	addTexts.push_back("try to move away");
	addTexts.push_back("from meat.");
	addTexts.push_back("");
	addTexts.push_back("Cost: 5 Pts");
	meat2.init(LoadTexture("src/img/ui/behaviors/gofrommeat.png"),addTexts);
	behaviors.push_back(meat2);

	Behavior runPoison = Behavior(32,384,5);
	addTexts.clear();
	addTexts.push_back("Your monsters will");
	addTexts.push_back("move away from");
	addTexts.push_back("poisoned plants.");
	addTexts.push_back("");
	addTexts.push_back("Cost: 5 Pts");
	runPoison.init(LoadTexture("src/img/ui/behaviors/runfrompoison.png"),addTexts);
	behaviors.push_back(runPoison);

	Behavior view1 = Behavior(64,384,1);
	addTexts.clear();
	addTexts.push_back("This monster will");
	addTexts.push_back("reveal more dark");
	addTexts.push_back("tiles on the map.");
	addTexts.push_back("");
	addTexts.push_back("Cost: 1 Pts");
	view1.init(LoadTexture("src/img/ui/behaviors/view1.png"),addTexts);
	behaviors.push_back(view1);

	Behavior view2 = Behavior(80,384,3);
	addTexts.clear();
	addTexts.push_back("This monster will");
	addTexts.push_back("reveal more dark");
	addTexts.push_back("tiles on the map.");
	addTexts.push_back("");
	addTexts.push_back("Cost: 3 Pts");
	view2.init(LoadTexture("src/img/ui/behaviors/view2.png"),addTexts);
	behaviors.push_back(view2);

	Behavior swim1 = Behavior(128,384,3);
	addTexts.clear();
	addTexts.push_back("This monster will");
	addTexts.push_back("be able to swim.");
	addTexts.push_back("");
	addTexts.push_back("");
	addTexts.push_back("Cost: 3 Pts");
	swim1.init(LoadTexture("src/img/ui/behaviors/swim1.png"),addTexts);
	addTexts.clear();
	addTexts.push_back("This monster will");
	addTexts.push_back("be able to walk on");
	addTexts.push_back("land.");
	addTexts.push_back("");
	addTexts.push_back("Cost: 3 Pts");
	swim1.setAltTexture(LoadTexture("src/img/ui/behaviors/walk1.png"),addTexts);

	behaviors.push_back(swim1);

	Behavior swim2 = Behavior(144,384,4);
	addTexts.clear();
	addTexts.push_back("This monster will");
	addTexts.push_back("be able to swim.");
	addTexts.push_back("");
	addTexts.push_back("");
	addTexts.push_back("Cost: 4 Pts");
	swim2.init(LoadTexture("src/img/ui/behaviors/swim2.png"),addTexts);
	addTexts.clear();
	addTexts.push_back("This monster will");
	addTexts.push_back("be able to walk on");
	addTexts.push_back("land.");
	addTexts.push_back("");
	addTexts.push_back("Cost: 4 Pts");
	swim2.setAltTexture(LoadTexture("src/img/ui/behaviors/walk2.png"),addTexts);
	behaviors.push_back(swim2);

	Behavior weapons1 = Behavior(128,304,3);
	addTexts.clear();
	addTexts.push_back("This monster will");
	addTexts.push_back("be able to defeat");
	addTexts.push_back("opponents by just");
	addTexts.push_back("touching them.");
	addTexts.push_back("Cost: 3 Pts");
	weapons1.init(LoadTexture("src/img/ui/behaviors/weapons1.png"),addTexts);
	behaviors.push_back(weapons1);

	Behavior weapons2 = Behavior(144,304,6);
	addTexts.clear();
	addTexts.push_back("This monster will");
	addTexts.push_back("be able to destroy");
	addTexts.push_back("shelters by just");
	addTexts.push_back("touching them.");
	addTexts.push_back("Cost: 6 Pts");
	weapons2.init(LoadTexture("src/img/ui/behaviors/weapons2.png"),addTexts);
	behaviors.push_back(weapons2);

	Behavior shelters1 = Behavior(128,336,7);
	addTexts.clear();
	addTexts.push_back("This monster will");
	addTexts.push_back("be able to build");
	addTexts.push_back("simple shelters.");
	addTexts.push_back("Cost: 7 Pts");
	shelters1.init(LoadTexture("src/img/ui/behaviors/shelters1.png"),addTexts);
	behaviors.push_back(shelters1);

	Behavior shelters2 = Behavior(144,336,12);
	addTexts.clear();
	addTexts.push_back("This monster will");
	addTexts.push_back("be able to build");
	addTexts.push_back("more complex");
	addTexts.push_back("shelters.");
	addTexts.push_back("Cost: 12 Pts");
	shelters2.init(LoadTexture("src/img/ui/behaviors/shelters2.png"),addTexts);
	behaviors.push_back(shelters2);

	Behavior civilization = Behavior(160,320,16);
	addTexts.clear();
	addTexts.push_back("This monster will");
	addTexts.push_back("gain sentience");
	addTexts.push_back("and begin a");
	addTexts.push_back("civilization.");
	addTexts.push_back("Cost: 16 Pts");
	civilization.init(LoadTexture("src/img/ui/behaviors/sentience.png"),addTexts);
	behaviors.push_back(civilization);

}

void MonsterUI::getBehaveAllowed()
{
	for(unsigned int i = 2; i < behaviors.size(); i++)
	{
		behaviors[i].disable();
	}
	for(unsigned int i = 0; i < behaviors.size(); i++)
	{
		if(behaviors[i].getStatus() >= 2)
		{
			behaviors[i].enable();
		}
	}
	behaviors[4].enable();
	if(behaviors[0].getStatus() >= 2 || behaviors[1].getStatus() >= 2)
	{
		behaviors[2].enable();
		behaviors[3].enable();
		behaviors[5].enable();
	}
	else
	{
		behaviors[2].disable();
		behaviors[3].disable();
		behaviors[5].disable();
	}
	if(behaviors[4].getStatus() >= 2)
	{
		behaviors[6].enable();
	}
	else
	{
		behaviors[6].disable();
	}
	if((editing && speedUpdate > 4) || (!editing && Species::monsterSpecies[curViewing].speed > 4))
	{
		behaviors[7].enable();
	}
	if((editing && sizeUpdate >= 3) || (!editing && Species::monsterSpecies[curViewing].size >= 3))
	{
		behaviors[8].enable();
	}
	if(behaviors[8].getStatus() >= 2)
	{
		behaviors[9].enable();
	}

	if(Species::monsterSpecies[curViewing].complexity >= 3 && GameObject::generation > 50)
	{
		if(Species::monsterSpecies[curViewing].strength > 4)
		{
			behaviors[Behaviors::WEAPON_1].enable();
		}
		if(Species::monsterSpecies[curViewing].resil > 5)
		{
			behaviors[Behaviors::SHELTER_1].enable();
		}
	}

	if(behaviors[Behaviors::SWALK_1].getStatus() >= 2)
	{
		behaviors[Behaviors::SWALK_2].enable();
	}
	behaviors[Behaviors::SWALK_1].setTexture(!Species::monsterSpecies[curViewing].land);
	behaviors[Behaviors::SWALK_2].setTexture(!Species::monsterSpecies[curViewing].land);

	if(behaviors[Behaviors::SHELTER_1].getStatus() >= 2 && Species::monsterSpecies[curViewing].complexity >= 3)
	{
		behaviors[Behaviors::SHELTER_2].enable();
		behaviors[Behaviors::WEAPON_1].enable();
	}

	if(behaviors[Behaviors::WEAPON_1].getStatus() >= 2  && Species::monsterSpecies[curViewing].complexity >= 3)
	{
		behaviors[Behaviors::WEAPON_2].enable();
		behaviors[Behaviors::SHELTER_1].enable();
	}

	if(behaviors[Behaviors::SHELTER_1].getStatus() >= 2)
	{
		int amountOfShelters = 0;
		for(unsigned int i = 0; i < Species::monsterSpecies.size(); i++)
		{
			if(Species::monsterSpecies[i].enemy && Species::monsterSpecies[i].population > 20 && Species::monsterSpecies[i].behaviors[Behaviors::SHELTER_1])
			{
				amountOfShelters++;
			}
		}
		if(amountOfShelters >= 5)
		{
			behaviors[Behaviors::SENTIENCE].enable();
		}

	}

	if(editing &&  Species::monsterSpecies[curViewing].complexity >= 2)
	{
		behaviors[10].enable();
	}
	for(unsigned int i = 0; i < behaviors.size(); i++)
	{
		if(behaviors[i].getStatus() >= 2)
		{
			behaviors[i].enable();
		}
	}
}

void MonsterUI::tickBehaviors()
{
	getBehaveAllowed();
	if(getClicking(behaveX,behaveY,64,32))
	{
		for(unsigned int i=0; i<behaviors.size(); i++)
		{
			if(behaviors[i].getStatus() == 1)
			{
				behaviors[i].setStatus(2);
				unlockedUpdate[i] = true;
			}
			else if(behaviors[i].getStatus() == 3)
			{
				behaviors[i].setStatus(0);
				unlockedUpdate[i] = false;
			}
		}
	}
	for(unsigned int i=0; i<behaviors.size(); i++)
	{
		behaviors[i].tick();
	}
}

void MonsterUI::renderBehaviors()
{
	behaveTexts.clear();
	int behave;
	for(unsigned int i=0; i<behaviors.size(); i++)
	{
		behaviors[i].render();
		if(behaviors[i].getStatus() == 1 || behaviors[i].getStatus() == 3)
		{
			behaveTexts = behaviors[i].getText();
			behave = i;
		}
	}
	if(behaveTexts.size() > 0)
	{
		DrawRectangle(behaveX,behaveY,64,32,BLACK);
		if(behaviors[behave].getStatus() < 2)
		{
			DrawTextEx(font,"ADD",{behaveX+8,behaveY+4},24.0f,0.0f,WHITE); // @suppress("Invalid arguments")
		}
		else
		{
			DrawTextEx(font,"REMOVE",{behaveX+8,behaveY+4},18.0f,0.0f,WHITE); // @suppress("Invalid arguments")
		}
	}
	for(unsigned int i=0; i<behaveTexts.size(); i++)
	{
		DrawTextEx(font,behaveTexts[i].c_str(),{284,250+(20*i)},24.0f,0.0f,BLACK); // @suppress("Invalid arguments")
	}
}

void MonsterUI::setupBehaveIcons()
{
	getBehaveAllowed();
	for(unsigned int i = 0; i < behaviors.size(); i++)
	{
		if(Species::monsterSpecies[curViewing].behaviors[i])
		{
			behaviors[i].setStatus(2);
		}
		else
		{
			behaviors[i].setStatus(0);
		}
	}
	getBehaveAllowed();
}
