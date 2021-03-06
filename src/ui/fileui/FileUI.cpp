/*
 * FileUI.cpp
 *
 *  Created on: Jan 24, 2019
 *      Author: truttle1
 */

#include "FileUI.h"
#include <stdio.h>
#include "../../img/MonsterImg.h"
typedef UI super;
FileUI::FileUI() : super(){
	running = false;
	//fontBig = LoadFontEx("src/SGK050.ttf",480,0,0);
	saving = false;

}

FileUI::~FileUI() {
	// TODO Auto-generated destructor stub
}
void FileUI::init(bool iSaving)
{
	leftButton = LoadTexture("src/img/ui/leftButton.png");
	rightButton = LoadTexture("src/img/ui/rightButton.png");
	printf("hi\n");
	saving = iSaving;
	water0 = LoadTexture("src/img/water0.png");
	water1 = LoadTexture("src/img/water1.png");
	freshwater0 = LoadTexture("src/img/freshwater0.png");
	freshwater1 = LoadTexture("src/img/freshwater1.png");
	dirt = LoadTexture("src/img/dirt.png");
	beach = LoadTexture("src/img/sand0.png");
	tundra = LoadTexture("src/img/ice.png");
	desert = LoadTexture("src/img/sand1.png");
	mountain = LoadTexture("src/img/mountain.png");
	snow = LoadTexture("src/img/snow.png");
	grass = LoadTexture("src/img/grass.png");
	fileName = TextBox(200,420,"My World", GameObject::font);
}

void FileUI::lighten()
{
	dark = false;
}

void FileUI::tick()
{
	if(saving)
	{
		dark = false;
	}
	if(running)
	{
		if(IsKeyPressed(KEY_DOWN))
		{
			if(selection == 9)
			{
				selection = 0;
			}
			else
			{
				selection++;
			}
		}
		if(IsKeyPressed(KEY_UP))
		{
			if(selection == 0)
			{
				selection = 9;
			}
			else
			{
				selection--;
			}
		}
		if(dark && getClicking(backX,backY,128,64))
		{
			toggle();
		}
	}
	if(saving && running)
	{
		saveUI();
	}
	else if(!saving)
	{
		loadUI();
	}
	if(!open)
	{
		running = false;
	}

}
void FileUI::saveUI()
{
	if(IsKeyPressed(KEY_ENTER) && saving && running)
	{
		std::string select = std::to_string(selection);
		save("file" + select + ".blkstrs");
	}
}
void FileUI::loadUI()
{
	if(IsKeyPressed(KEY_ENTER) && !saving && running)
	{
		MusicHandler::playSong(MusicHandler::boyDog);
		std::string select = std::to_string(selection);
		try
		{
			load("file" + select + ".blkstrs");
		}
		catch (const std::exception& e)
		{
			cout << "EXCEPTION " << e.what() << endl;
		}
	}
}
void FileUI::render()
{
	if(running)
	{

		Color bg;
		Color text;
		Color defText;
		Color highlight;

		if(!dark)
		{
			bg = WHITE;
			text = BLACK;
			defText = BLACK;
			highlight = {0,255,255,255};
		}
		else
		{
			bg = BLACK;
			text = WHITE;
			defText = WHITE;
			highlight = {0,192,0,255};
		}
		DrawRectangle(0,0,dark ? 640 : 480,480,bg);
		DrawRectangle(44,130+(selection*28),360,20,highlight);
		if(saving)
		{
			DrawTextEx(font,"SAVING FILE",{128,64},48.0f,0.0f,text);
			DrawTextEx(font,"File Name:",{64,420},24.0f,0.0f,text);
			fileName.render();
			fileName.tick();
		}
		else
		{
			DrawTextEx(font,"LOADING FILE",{128,64},48.0f,0.0f,text);
		}
		for(int i=0; i<10; i++)
		{
			std::string name = "";
			std::ifstream file;
			file.open("file" + to_string(i) + ".blkstrs");
			while(file.good() && !file.eof())
			{
				string input;
				getline(file,input);

				stringstream str(input);
				vector<string> result;
				while(str.good())
				{
					string substring;
				    getline(str, substring, ',');
				    result.push_back(substring);
				}
				if(result[0].find("NAME") != string::npos)
				{
					name += result[1];
					break;
				}
				break;
			}
			if(!file.good())
			{
				text = RED;
			}
			std::string str = "File " + std::to_string(i);
			DrawTextEx(font,str.c_str(),{48.0f,128.0f+(i*28.0f)},24.0f,0.0f,text);
			DrawTextEx(font,name.c_str(),{160.0f,128.0f+(i*28.0f)},24.0f,0.0f,text);
			text = defText;
		}
		if(dark)
		{
			DrawRectangle(backX,backY,128,64,WHITE);
			DrawTextEx(GameObject::font,"BACK",{backX+32,backY+16},36.0f,0.0f,BLACK); // @suppress("Invalid arguments")
		}
	}
}
void FileUI::close()
{

}
void FileUI::toggle()
{
	if(!UI::isOpen() && !running)
	{
		running = true;
		open = true;
		fileName.setText(GameWindow::getFileName());
	}
	else if(UI::isOpen() && running)
	{
		running = false;
		open = false;
	}
}
bool FileUI::getRunning()
{
	return running;
}
bool FileUI::load(std::string filename)
{
	GameWindow::getMessageBox()->disable();
	std::ifstream file;
	file.open(filename);
	if(!file.good())
	{
		return false;
	}
	GameWindow::setGameScreen();
	GameObject::setInternalClock(30);
	dark = false;
	for(uint i = 0; i < GameObject::objects.size(); i++)
	{
		delete GameObject::objects[i];
		GameObject::objects[i] = nullptr;
	}
	for(unsigned int i = 0; i < 60; i++)
	{

		for(unsigned int j = 0; j < 60; j++)
		{
			GameObject::fog[i][j].enable();
		}
	}
	GameWindow::getCamera()->zoom = 0.5f;
	GameObject::objects.clear();
	Species::plantSpecies.clear();
	Species::monsterSpecies.clear();
	Species::monstersDiscovered.clear();
	Species::plMonstersDiscovered.clear();
	Species::plantsDiscovered.clear();
	GameObject::objects.shrink_to_fit();
	while(!file.eof())
	{
		string input;
		getline(file,input);

		stringstream str(input);
		vector<string> result;
		while(str.good())
		{
			string substring;
		    getline(str, substring, ',');
		    result.push_back(substring);
		}
		printf("%s!\n",result[0].c_str());
		if(result[0].find("GEN") != string::npos)
		{
			GameObject::generation = stoi(result[1]);
		}
		if(result[0].find("DOLURZ") != string::npos)
		{
			CivHandler::setDolurz(stoi(result[1]));
		}
		if(result[0].find("NAME") != string::npos)
		{
			GameWindow::setFileName(result[1]);
		}
		if(result[0].find("BHVR") != string::npos)
		{
			Species::monsterSpecies[stoi(result[1])].behaviors[stoi(result[2])] = stoi(result[3]);
		}
		if(result[0].find("STATE") != string::npos)
		{
			State st;
			st.monster = stoi(result[1]);
			st.myColor = stoi(result[2]);
			st.started = stoi(result[3]);
			st.type = stoi(result[4]);
			Civilizations::states.push_back(st);
		}
		if(result[0].find("_TRIBE") != string::npos)
		{
			Tribe st;
			st.monster = stoi(result[1]);
			st.baseFriendship = stoi(result[2]);
			Civilizations::tribes.push_back(st);
		}
		if(result[0].find("PSPECIES") != string::npos)
		{
			printf("%d",stoi(result[1]));
			printf("\n");
			int species = stoi(result[1].c_str());
			PlantSpecies ps;
			ps.minNew = stoi(result[2]);
			ps.maxNew = stoi(result[3]);
			ps.minDeath = stoi(result[4]);
			ps.maxDeath = stoi(result[5]);
			ps.toxicity = stoi(result[6]);
			ps.size = stoi(result[7]);
			ps.nutrients = stoi(result[8]);
			ps.groupSize = stoi(result[9]);
			ps.land = stoi(result[10]);
			ps.name = result[11];
			ps.population = 0;
			ps.lifespan = stoi(result[13]);
			ps.evolvePass = stoi(result[14]);
			cout << "IMAGE" << endl;
			ps.image.height = 8;
			ps.image.width = 8;
			ps.image = MonsterImg::basic0;
			Species::plantSpecies.push_back(ps);
		}
		if(result[0].find("MSPECIES") != string::npos)
		{
			MonsterSpecies ms;
			printf("%d",stoi(result[1]));
			printf("\n");
			int species = stoi(result[1].c_str());
			ms.minNew = stoi(result[2]);
			printf("minnew\n");
			ms.maxNew = stoi(result[3]);
			printf("maxnew\n");
			ms.minDeath = stoi(result[4]);
			printf("mindeath\n");
			ms.maxDeath = stoi(result[5]);
			printf("maxdeath\n");
			ms.toxicity = stoi(result[6]);
			printf("toxicity\n");
			ms.size = stoi(result[7]);
			printf("size\n");
			ms.groupSize = stoi(result[8]);
			printf("groupsize\n");
			ms.land = stoi(result[9]);
			printf("land\n");
			ms.name = result[10];
			printf("name\n");
			ms.population = 0;
			printf("pop\n");
			ms.metabolism = stoi(result[12]);
			printf("met\n");
			ms.lifespan = stoi(result[13]);
			printf("life\n");
			ms.speed = stoi(result[14]);
			printf("spd\n");
			ms.strength = stoi(result[15]);
			printf("str\n");
			ms.resil = stoi(result[16]);
			printf("resl\n");
			ms.agression = stoi(result[17]);
			printf("ag\n");
			ms.enemy = stoi(result[18]);
			printf("en\n");
			ms.image.height = 8;
			ms.image.width = 8;
			ms.image = MonsterImg::basic0;
			printf("carn\n");
			ms.carnivore = stoi(result[19]);
			ms.complexity = stoi(result[20]);
			ms.evolvePass = stoi(result[21]);
			Species::monsterSpecies.push_back(ms);
		}
		if(result[0].find("GROUND") != string::npos)
		{
			Ground* g = new Ground(stoi(result[1]),stoi(result[2]),16,16,false);
			g->loadFile(static_cast<Biome>(stoi(result[3])));
			g->setupFreshWaterGraphics(&freshwater0,&freshwater1);
			g->setupWaterGraphics(&water0,&water1);
			g->setupLandGraphics(&dirt,&beach,&tundra,&desert,&mountain,&snow,&grass);
			GameObject::objects.push_back(g);
		}

		if(result[0].find("TERRITORY") != string::npos)
		{
			Territory* g = new Territory(stoi(result[1]),stoi(result[2]));
			if(result.size() > 4)
			{
				g->setOwner(stoi(result[3]), stoi(result[4]));
			}
			else
			{
				g->setOwner(stoi(result[3]), false);
			}
			GameObject::objects.push_back(g);
		}
		if(result[0].find("TRIBENPC") != string::npos)
		{
			NPC* g = new NPC(stoi(result[1]),stoi(result[2]));
			g->setOwner(stoi(result[3]));
			GameObject::objects.push_back(g);
		}
		if(result[0].find("CIVILIZED") != string::npos)
		{
			GameWindow::setCivilizedMode(stoi(result[1]));
		}
		if(result[0].find("ROAD") != string::npos)
		{
			Road* g = new Road(stoi(result[1]),stoi(result[2]));
			g->setOwner(stoi(result[3]));
			GameObject::objects.push_back(g);
		}

		if(result[0].find("FARM") != string::npos)
		{
			Farm* g = new Farm(stoi(result[1]),stoi(result[2]));
			g->setOwner(stoi(result[3]));
			g->loadFromFile(stoi(result[4]));
			GameObject::objects.push_back(g);
		}

		if(result[0].find("RES") != string::npos)
		{
			Residential* g = new Residential(stoi(result[1]),stoi(result[2]));
			g->setOwner(stoi(result[3]));
			g->setPopulation(stoi(result[4]));
			GameObject::objects.push_back(g);
		}

		if(result[0].find("HUT") != string::npos)
		{
			Hut* g = new Hut(stoi(result[1]),stoi(result[2]));
			g->setOwner(stoi(result[3]));
			GameObject::objects.push_back(g);
		}

		if(result[0].find("PLANT") != string::npos)
		{
			Plant* g = new Plant(stoi(result[1]),stoi(result[2]),stoi(result[3]));
			g->loadFromFile(stoi(result[5]),stoi(result[4]),stoi(result[6]));
			GameObject::objects.push_back(g);
		}
		if(result[0].find("MEAT") != string::npos)
		{
			Meat* g = new Meat(stoi(result[1]),stoi(result[2]),stoi(result[3]),stoi(result[4]));
			GameObject::objects.push_back(g);
		}

		if(result[0].find("SHELTER") != string::npos)
		{
			Shelter* g = new Shelter(stoi(result[1]),stoi(result[2]),stoi(result[3]),stoi(result[4]),stoi(result[5]),stoi(result[6]));
			GameObject::objects.push_back(g);
			GameObject::shelters.push_back(g);
		}

		if(result[0].find("MONSTER") != string::npos)
		{
			Monster* g = new Monster(stoi(result[1]),stoi(result[2]),stoi(result[3]),stoi(result[7]));
			g->loadFromFile(stoi(result[4]),stoi(result[6]),stoi(result[6]));
			GameObject::objects.push_back(g);
			GameObject::monsters.push_back(g);
		}
		if(result[0].find("P_PIXEL") != string::npos)
		{
			int species = stoi(result[1].c_str());
			int pixel = stoi(result[2].c_str());
			//Color* pixels = (Color*)(GetImageData(GetTextureData(tex)));
			Species::plantSpecies[species].pixels[pixel].r = stoi(result[3]);
			Species::plantSpecies[species].pixels[pixel].g = stoi(result[4]);
			Species::plantSpecies[species].pixels[pixel].b = stoi(result[5]);
			Species::plantSpecies[species].pixels[pixel].a = stoi(result[6]);
		}
		if(result[0].find("END_P_PXL") != string::npos)
		{
			int species = stoi(result[1].c_str());
			Texture tex = LoadTextureFromImage(GetTextureData(Species::plantSpecies[species].image));
			UpdateTexture(tex,(Species::plantSpecies[species].pixels));
			Species::plantSpecies[species].image = tex;
		}
		if(result[0].find("M_PIXEL") != string::npos)
		{
			int species = stoi(result[1].c_str());
			int pixel = stoi(result[2].c_str());
			//Texture tex = LoadTextureFromImage(GetTextureData(Species::monsterSpecies[species].image));
			//Color* pixels = (Color*)(GetImageData(GetTextureData(tex)));
			Species::monsterSpecies[species].pixels[pixel].r = stoi(result[3]);
			Species::monsterSpecies[species].pixels[pixel].g = stoi(result[4]);
			Species::monsterSpecies[species].pixels[pixel].b = stoi(result[5]);
			Species::monsterSpecies[species].pixels[pixel].a = stoi(result[6]);
			//UpdateTexture(tex,pixels);
			//Species::monsterSpecies[species].image = tex;
		}
		if(result[0].find("END_M_PXL") != string::npos)
		{
			int species = stoi(result[1].c_str());
			Texture tex = LoadTextureFromImage(GetTextureData(Species::monsterSpecies[species].image));
			UpdateTexture(tex,(Species::monsterSpecies[species].pixels));
			Species::monsterSpecies[species].image = tex;
		}
		if(result[0].find("P_COLOR0") != string::npos)
		{
			int species = stoi(result[1]);
			Species::plantSpecies[species].stemColor.r = stoi(result[2]);
			Species::plantSpecies[species].stemColor.g = stoi(result[3]);
			Species::plantSpecies[species].stemColor.b = stoi(result[4]);
			Species::plantSpecies[species].stemColor.a = 255;
		}
		if(result[0].find("P_COLOR1") != string::npos)
		{
			int species = stoi(result[1]);
			Species::plantSpecies[species].flowerColor.r = stoi(result[2]);
			Species::plantSpecies[species].flowerColor.g = stoi(result[3]);
			Species::plantSpecies[species].flowerColor.b = stoi(result[4]);
			Species::plantSpecies[species].flowerColor.a = 255;
		}
		if(result[0].find("P_COLOR2") != string::npos)
		{
			int species = stoi(result[1]);
			Species::plantSpecies[species].highlightColor.r = stoi(result[2]);
			Species::plantSpecies[species].highlightColor.g = stoi(result[3]);
			Species::plantSpecies[species].highlightColor.b = stoi(result[4]);
			Species::plantSpecies[species].highlightColor.a = 255;
		}

		if(result[0].find("M_COLOR0") != string::npos)
		{
			int species = stoi(result[1]);
			Species::monsterSpecies[species].bodyColor.r = stoi(result[2]);
			Species::monsterSpecies[species].bodyColor.g = stoi(result[3]);
			Species::monsterSpecies[species].bodyColor.b = stoi(result[4]);
			Species::monsterSpecies[species].bodyColor.a = 255;
		}
		if(result[0].find("M_COLOR1") != string::npos)
		{
			int species = stoi(result[1]);
			Species::monsterSpecies[species].eyeColor.r = stoi(result[2]);
			Species::monsterSpecies[species].eyeColor.g = stoi(result[3]);
			Species::monsterSpecies[species].eyeColor.b = stoi(result[4]);
			Species::monsterSpecies[species].eyeColor.a = 255;
		}
		if(result[0].find("M_COLOR2") != string::npos)
		{
			int species = stoi(result[1]);
			Species::monsterSpecies[species].highlightColor.r = stoi(result[2]);
			Species::monsterSpecies[species].highlightColor.g = stoi(result[3]);
			Species::monsterSpecies[species].highlightColor.b = stoi(result[4]);
			Species::monsterSpecies[species].highlightColor.a = 255;
		}
		if(result[0].find("FOG") != string::npos)
		{
			if(!stoi(result[3]))
			{
				GameObject::fog[stoi(result[1])][stoi(result[2])].disable();
			}
		}
		if(result[0].find("PLNT_DISCOVERED") != string::npos)
		{
				Species::plantsDiscovered.push_back(stoi(result[1]));
		}
		if(result[0].find("AIMNSTERS_DISCOVERED") != string::npos)
		{
				Species::monstersDiscovered.push_back(stoi(result[1]));
		}
		if(result[0].find("PLMNSTERS_DISCOVERED") != string::npos)
		{
				Species::plMonstersDiscovered.push_back(stoi(result[1]));
		}
		if(result[0].find("PTSGN") != string::npos)
		{
				GameWindow::pointIncrease = stoi(result[1]);
		}
		if(result[0].find("EVLVPTS") != string::npos)
		{
				GameWindow::setPoints(stoi(result[1]));
		}
		if(result[0].find("TTRL") != string::npos)
		{
				GameWindow::tutorial[stoi(result[1])] = stoi(result[2]);
		}
	}
	open = false;
	running = false;
	file.close();
	return true;
}
void FileUI::save(std::string filename)
{
	std::ofstream file;
	GameWindow::setFileName(fileName.getText());
	file.open(filename);
	{
		file << "NAME,";
		file << fileName.getText();
		file << "\n";
		file << "CIVILIZED,";
		file << GameWindow::getCivilizedMode();
		file << "\n";
		file << "GEN,";
		file << to_string(GameObject::generation);
		file << "\n";

		file << "PTSGN,";
		file << to_string(GameWindow::pointIncrease);
		file << "\n";

		file << "EVLVPTS,";
		file << GameWindow::getPoints();
		file << "\n";
		if(GameWindow::getCivilizedMode())
		{
			file << "DOLURZ,";
			file << CivHandler::getDolurz();
			file << "\n";
		}

		for(unsigned i = 0; i < Civilizations::states.size(); i++)
		{
			file << "STATE,";
			file << Civilizations::states[i].monster;
			file << ",";
			file << Civilizations::states[i].myColor;
			file << ",";
			file << Civilizations::states[i].started;
			file << ",";
			file << Civilizations::states[i].type;
			file << "\n";
		}
		for(unsigned i = 0; i < Civilizations::tribes.size(); i++)
		{
			file << "_TRIBE,";
			file << Civilizations::tribes[i].monster;
			file << ",";
			file << Civilizations::tribes[i].baseFriendship;
			file << "\n";
		}
		for(unsigned int i = 0; i < Species::plantSpecies.size(); i++)
		{
			file << "PSPECIES,";
			file << i;
			file << ",";
			file << to_string(Species::plantSpecies[i].minNew);
			file << ",";
			file << to_string(Species::plantSpecies[i].maxNew);
			file << ",";
			file << to_string(Species::plantSpecies[i].minDeath);
			file << ",";
			file << to_string(Species::plantSpecies[i].maxDeath);
			file << ",";
			file << to_string(Species::plantSpecies[i].toxicity);
			file << ",";
			file << to_string(Species::plantSpecies[i].size);
			file << ",";
			file << to_string(Species::plantSpecies[i].nutrients);
			file << ",";
			file << to_string(Species::plantSpecies[i].groupSize);
			file << ",";
			file << to_string(Species::plantSpecies[i].land);
			file << ",";
			file << Species::plantSpecies[i].name;
			file << ",";
			file << to_string(Species::plantSpecies[i].population);
			file << ",";
			file << to_string(Species::plantSpecies[i].lifespan);
			file << ",";
			file << to_string(Species::plantSpecies[i].evolvePass);
			file << "\n";

			file << "P_COLOR0";
			file << ",";
			file << to_string(i);
			file << ",";
			file << to_string(Species::plantSpecies[i].stemColor.r);
			file << ",";
			file << to_string(Species::plantSpecies[i].stemColor.g);
			file << ",";
			file << to_string(Species::plantSpecies[i].stemColor.b);
			file << "\n";

			file << "P_COLOR1";
			file << ",";
			file << to_string(i);
			file << ",";
			file << to_string(Species::plantSpecies[i].flowerColor.r);
			file << ",";
			file << to_string(Species::plantSpecies[i].flowerColor.g);
			file << ",";
			file << to_string(Species::plantSpecies[i].flowerColor.b);
			file << "\n";

			file << "P_COLOR2";
			file << ",";
			file << to_string(i);
			file << ",";
			file << to_string(Species::plantSpecies[i].highlightColor.r);
			file << ",";
			file << to_string(Species::plantSpecies[i].highlightColor.g);
			file << ",";
			file << to_string(Species::plantSpecies[i].highlightColor.b);
			file << "\n";
			for(unsigned int j = 0; j<64; j++)
			{
				Texture image = Species::plantSpecies[i].image;
				Color* pixels = (Color*)(GetImageData(GetTextureData(image)));
				Color c = pixels[j];
				file << "P_PIXEL,";
				file << to_string(i);
				file << ",";
				file << to_string(j);
				file << ",";
				file << to_string(c.r);
				file << ",";
				file << to_string(c.g);
				file << ",";
				file << to_string(c.b);
				file << ",";
				file << to_string(c.a);
				file << "\n";
			}
			file << "END_P_PXL,";
			file << to_string(i);
			file << "\n";

		}
		for(unsigned int i = 0; i < 100; i++)
		{

			file << "TTRL,";
			file << to_string(i);
			file << ",";
			file << to_string(GameWindow::tutorial[i]);
			file << "\n";
		}
		for(unsigned int i = 0; i < Species::monsterSpecies.size(); i++)
		{
			file << "MSPECIES,";
			file << to_string(i);
			file << ",";
			file << to_string(Species::monsterSpecies[i].minNew);
			file << ",";
			file << to_string(Species::monsterSpecies[i].maxNew);
			file << ",";
			file << to_string(Species::monsterSpecies[i].minDeath);
			file << ",";
			file << to_string(Species::monsterSpecies[i].maxDeath);
			file << ",";
			file << to_string(Species::monsterSpecies[i].toxicity);
			file << ",";
			file << to_string(Species::monsterSpecies[i].size);
			file << ",";
			file << to_string(Species::monsterSpecies[i].groupSize);
			file << ",";
			file << to_string(Species::monsterSpecies[i].land);
			file << ",";
			file << Species::monsterSpecies[i].name;
			file << ",";
			file << to_string(Species::monsterSpecies[i].population);
			file << ",";
			file << to_string(Species::monsterSpecies[i].metabolism);
			file << ",";
			file << to_string(Species::monsterSpecies[i].lifespan);
			file << ",";
			file << to_string(Species::monsterSpecies[i].speed);
			file << ",";
			file << to_string(Species::monsterSpecies[i].strength);
			file << ",";
			file << to_string(Species::monsterSpecies[i].resil);
			file << ",";
			file << to_string(Species::monsterSpecies[i].agression);
			file << ",";
			file << to_string(Species::monsterSpecies[i].enemy);
			file << ",";
			file << to_string(Species::monsterSpecies[i].carnivore);
			file << ",";
			file << to_string(Species::monsterSpecies[i].complexity);
			file << ",";
			file << to_string(Species::monsterSpecies[i].evolvePass);
			file << "\n";

			file << "M_COLOR0";
			file << ",";
			file << to_string(i);
			file << ",";
			file << to_string(Species::monsterSpecies[i].bodyColor.r);
			file << ",";
			file << to_string(Species::monsterSpecies[i].bodyColor.g);
			file << ",";
			file << to_string(Species::monsterSpecies[i].bodyColor.b);
			file << "\n";

			file << "M_COLOR1";
			file << ",";
			file << to_string(i);
			file << ",";
			file << to_string(Species::monsterSpecies[i].eyeColor.r);
			file << ",";
			file << to_string(Species::monsterSpecies[i].eyeColor.g);
			file << ",";
			file << to_string(Species::monsterSpecies[i].eyeColor.b);
			file << "\n";

			file << "M_COLOR2";
			file << ",";
			file << to_string(i);
			file << ",";
			file << to_string(Species::monsterSpecies[i].highlightColor.r);
			file << ",";
			file << to_string(Species::monsterSpecies[i].highlightColor.g);
			file << ",";
			file << to_string(Species::monsterSpecies[i].highlightColor.b);
			file << "\n";


			for(unsigned int j = 0; j<100; j++)
			{
				file << "BHVR,";
				file << to_string(i);
				file << ",";
				file << to_string(j);
				file << ",";
				file << to_string(Species::monsterSpecies[i].behaviors[j]);
				file << "\n";
			}

			for(unsigned int j = 0; j<64; j++)
			{
				Texture image = Species::monsterSpecies[i].image;
				Color* pixels = (Color*)(GetImageData(GetTextureData(image)));
				Color c = pixels[j];
				file << "M_PIXEL,";
				file << to_string(i);
				file << ",";
				file << to_string(j);
				file << ",";
				file << to_string(c.r);
				file << ",";
				file << to_string(c.g);
				file << ",";
				file << to_string(c.b);
				file << ",";
				file << to_string(c.a);
				file << "\n";
			}
			file << "END_M_PXL,";
			file << to_string(i);
			file << "\n";
		}
		for(unsigned int x = 0; x < 60; x++)
		{
			for(unsigned int y = 0; y < 60; y++)
			{
				file << "FOG";
				file << ",";
				file << to_string(x).c_str();
				file << ",";
				file << to_string(y).c_str();
				file << ",";
				file << to_string(GameObject::fog[x][y].isVisible()).c_str();
				file << "\n";
			}
		}
		for(unsigned int i = 0; i < GameObject::objects.size(); i++)
		{
			if(GameObject::objects[i]->getName() == GROUND)
			{
				Ground* g = static_cast<Ground*>(GameObject::objects[i]);
				file << "GROUND,";
				file << to_string(g->getX()).c_str();
				file << ",";
				file << to_string(g->getY()).c_str();
				file << ",";
				file << to_string(g->getBiome()).c_str();
				file << "\n";
			}
			if(GameObject::objects[i]->getName() == PLANT)
			{
				Plant* g = static_cast<Plant*>(GameObject::objects[i]);
				file << "PLANT,";
				file << to_string(g->getX()).c_str();
				file << ",";
				file << to_string(g->getY()).c_str();
				file << ",";
				file << to_string(g->getSpecies()).c_str();
				file << ",";
				file << to_string(g->getAge()).c_str();
				file << ",";
				file << to_string(g->getHP()).c_str();
				file << ",";
				file << to_string(g->getPopulation()).c_str();
				file << "\n";
			}
			if(GameObject::objects[i]->getName() == MEAT)
			{
				Meat* g = static_cast<Meat*>(GameObject::objects[i]);
				file << "MEAT,";
				file << to_string(g->getX()).c_str();
				file << ",";
				file << to_string(g->getY()).c_str();
				file << ",";
				file << to_string(g->getNutrients()).c_str();
				file << ",";
				file << to_string(g->getSpecies()).c_str();
				file << "\n";
			}
			if(GameObject::objects[i]->getName() == MONSTER)
			{
				Monster* g = static_cast<Monster*>(GameObject::objects[i]);
				file << "MONSTER,";
				file << to_string(g->getX()).c_str();
				file << ",";
				file << to_string(g->getY()).c_str();
				file << ",";
				file << to_string(g->getSpecies()).c_str();
				file << ",";
				file << to_string(g->getAge()).c_str();
				file << ",";
				file << to_string(g->getHP()).c_str();
				file << ",";
				file << to_string(g->getPopulation()).c_str();
				file << ",";
				file << to_string(g->isEnemy()).c_str();
				file << "\n";
			}

			if(GameObject::objects[i]->getName() == SHELTER)
			{
				Shelter* g = static_cast<Shelter*>(GameObject::objects[i]);
				file << "SHELTER,";
				file << to_string(g->getX()).c_str();
				file << ",";
				file << to_string(g->getY()).c_str();
				file << ",";
				file << to_string(g->getSpecies()).c_str();
				file << ",";
				file << to_string(g->getType()).c_str();
				file << ",";
				file << to_string(g->getFood()).c_str();
				file << ",";
				file << to_string(g->getPopulation()).c_str();
				file << "\n";
			}

			if(GameObject::objects[i]->getName() == TERRITORY)
			{
				Territory* g = static_cast<Territory*>(GameObject::objects[i]);
				file << "TERRITORY,";
				file << to_string(g->getX()).c_str();
				file << ",";
				file << to_string(g->getY()).c_str();
				file << ",";
				file << to_string(g->getOwner()).c_str();
				file << ",";
				file << to_string(g->isTribal()).c_str();
				file << "\n";
			}
			if(GameObject::objects[i]->getUnit() == TRIBENPC)
			{
				NPC* g = static_cast<NPC*>(GameObject::objects[i]);
				file << "TRIBENPC,";
				file << to_string(g->getX()).c_str();
				file << ",";
				file << to_string(g->getY()).c_str();
				file << ",";
				file << to_string(g->getOwner()).c_str();
				file << "\n";
			}

			if(GameObject::objects[i]->getBuilding() == ROAD)
			{
				Road* g = static_cast<Road*>(GameObject::objects[i]);
				file << "ROAD,";
				file << to_string(g->getX()).c_str();
				file << ",";
				file << to_string(g->getY()).c_str();
				file << ",";
				file << to_string(g->getOwner()).c_str();
				file << "\n";
			}
			if(GameObject::objects[i]->getBuilding() == FARM)
			{
				Farm* g = static_cast<Farm*>(GameObject::objects[i]);
				file << "FARM,";
				file << to_string(g->getX()).c_str();
				file << ",";
				file << to_string(g->getY()).c_str();
				file << ",";
				file << to_string(g->getOwner()).c_str();
				file << ",";
				file << to_string(g->getCapacity()).c_str();
				file << "\n";
			}
			if(GameObject::objects[i]->getBuilding() == RES)
			{
				Residential* g = static_cast<Residential*>(GameObject::objects[i]);
				file << "RES,";
				file << to_string(g->getX()).c_str();
				file << ",";
				file << to_string(g->getY()).c_str();
				file << ",";
				file << to_string(g->getOwner()).c_str();
				file << ",";
				file << to_string(g->getPopulation()).c_str();
				file << "\n";
			}
			if(GameObject::objects[i]->getBuilding() == NPC_HUT)
			{
				Hut* g = static_cast<Hut*>(GameObject::objects[i]);
				file << "NPCHUT,";
				file << to_string(g->getX()).c_str();
				file << ",";
				file << to_string(g->getY()).c_str();
				file << ",";
				file << to_string(g->getOwner()).c_str();
				file << "\n";
			}
		}
		for(unsigned int i = 0; i < Species::plantsDiscovered.size(); i++)
		{
			file << "PLNT_DISCOVERED," << Species::plantsDiscovered[i] << "\n";
		}
		for(unsigned int i = 0; i < Species::monstersDiscovered.size(); i++)
		{
			file << "AIMNSTERS_DISCOVERED," << Species::monstersDiscovered[i] << "\n";
		}
		for(unsigned int i = 0; i < Species::plMonstersDiscovered.size(); i++)
		{
			file << "PLMNSTERS_DISCOVERED," << Species::plMonstersDiscovered[i] << "\n";
		}
		open = false;
		running = false;
	}
	file.close();
}

