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
}
void FileUI::tick()
{
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
		DrawRectangle(0,0,480,480,WHITE);
		DrawRectangle(44,130+(selection*28),360,20,{0,255,255,255});
		if(saving)
		{
			DrawTextEx(font,"SAVING FILE",{128,64},48.0f,0.0f,BLACK);
		}
		else
		{
			DrawTextEx(font,"LOADING FILE",{128,64},48.0f,0.0f,BLACK);
		}
		for(int i=0; i<10; i++)
		{
			std::string str = "File " + std::to_string(i);
			DrawTextEx(font,str.c_str(),{48,128+(i*28)},24.0f,0.0f,BLACK);
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
void FileUI::load(std::string filename)
{

	for(uint i = 0; i < GameObject::objects.size(); i++)
	{
		delete GameObject::objects[i];
		GameObject::objects[i] = nullptr;
	}
	GameObject::objects.clear();
	Species::plantSpecies.clear();
	Species::monsterSpecies.clear();
	GameObject::objects.shrink_to_fit();
	std::ifstream file;
	file.open(filename);
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
			//ps.population = stoi(result[12]);
			ps.lifespan = stoi(result[13]);
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
			//ms.population = stoi(result[11]);
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
			Species::monsterSpecies.push_back(ms);
		}
		if(result[0].find("GROUND") != string::npos)
		{
			Ground* g = new Ground(stoi(result[1]),stoi(result[2]),16,16,false);
			g->loadFile(static_cast<Biome>(stoi(result[3])));
			g->setupFreshWaterGraphics(&freshwater0,&freshwater1);
			g->setupWaterGraphics(&water0,&water1);
			g->setupLandGraphics(&dirt,&beach,&tundra,&desert,&mountain,&snow);
			GameObject::objects.push_back(g);
		}
		if(result[0].find("PLANT") != string::npos)
		{
			Plant* g = new Plant(stoi(result[1]),stoi(result[2]),stoi(result[3]));
			g->loadFromFile(stoi(result[5]),stoi(result[4]),stoi(result[6]));
			GameObject::objects.push_back(g);
		}
		if(result[0].find("MONSTER") != string::npos)
		{
			Monster* g = new Monster(stoi(result[1]),stoi(result[2]),stoi(result[3]),stoi(result[7]));
			g->loadFromFile(stoi(result[4]),stoi(result[6]),stoi(result[6]));
			GameObject::objects.push_back(g);
		}
		if(result[0].find("P_PIXEL") != string::npos)
		{
			int species = stoi(result[1].c_str());
			int pixel = stoi(result[2].c_str());
			Texture tex = LoadTextureFromImage(GetTextureData(Species::plantSpecies[species].image));
			Color* pixels = (Color*)(GetImageData(GetTextureData(tex)));
			pixels[pixel].r = stoi(result[3]);
			pixels[pixel].g = stoi(result[4]);
			pixels[pixel].b = stoi(result[5]);
			pixels[pixel].a = stoi(result[6]);
			UpdateTexture(tex,pixels);
			Species::plantSpecies[species].image = tex;
		}
		if(result[0].find("M_PIXEL") != string::npos)
		{
			int species = stoi(result[1].c_str());
			int pixel = stoi(result[2].c_str());
			Texture tex = LoadTextureFromImage(GetTextureData(Species::monsterSpecies[species].image));
			Color* pixels = (Color*)(GetImageData(GetTextureData(tex)));
			pixels[pixel].r = stoi(result[3]);
			pixels[pixel].g = stoi(result[4]);
			pixels[pixel].b = stoi(result[5]);
			pixels[pixel].a = stoi(result[6]);
			UpdateTexture(tex,pixels);
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
	}
	open = false;
	running = false;
	file.close();
}
void FileUI::save(std::string filename)
{
	std::ofstream file;
	file.open(filename);
	{
		file << "GEN,";
		file << to_string(GameObject::generation);
		file << "\n";
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
			if(GameObject::objects[i]->getName() == "Ground")
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
			if(GameObject::objects[i]->getName() == "Plant")
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
			if(GameObject::objects[i]->getName() == "Monster")
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

