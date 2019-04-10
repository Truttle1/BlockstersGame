/*
 * GameWindow.cpp
 *
 *  Created on: Nov 6, 2018
 *      Author: truttle1
 */

#include "GameWindow.h"

FileUI saveUI;
FileUI loadUI;
Camera2D* GameWindow::camera;
bool GameWindow::showingUpperText;
std::string GameWindow::upperText;
int GameWindow::points = -4;
int GameWindow::pointIncrease = 1;
GameWindow::GameMode GameWindow::gameMode = TITLE_SCREEN;
std::string GameWindow::fileName = "File Name";
MessageBox GameWindow::messageBox;
bool GameWindow::tutorial[100];

GameWindow::GameWindow()
{
	moving = false;
	internalClock = 0;
	for(int i=0; i<100; i++)
	{
		GameWindow::tutorial[i] = false;
	}
}

GameWindow::~GameWindow()
{
}

void GameWindow::init(Camera2D* cam)
{
	camera = cam;
	camera->offset = {0,0};
	camera->target = {0,0};
	camera->zoom = 0.5f;
	camera->rotation = 0.0f;
	messageBox = MessageBox();

	InitWindow(GameWindow::WINDOW_WIDTH,GameWindow::WINDOW_HEIGHT,"Blocksters - A Truttle1 Game");

	PlantImg::initTextures();
	MonsterImg::initTextures();
	ObjectColors::initColors();
	generatePlants();
	generateMonsters(false);

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
	//BUTTONS
	nextGenButton = LoadTexture("src/img/genbutton.png");
	moveButton = LoadTexture("src/img/finishmoving.png");
	plantButton = LoadTexture("src/img/ui/plantButton.png");
	monsterButton = LoadTexture("src/img/ui/monsterButton.png");
	saveButton = LoadTexture("src/img/ui/saveButton.png");
	loadButton = LoadTexture("src/img/ui/loadButton.png");
	titleScreen = LoadTexture("src/img/TitleScreen.png");

	EyeCandy::setBoomR(LoadTexture("src/img/boom_r.png"));
	EyeCandy::setBoomO(LoadTexture("src/img/boom_o.png"));
	EyeCandy::setBoomY(LoadTexture("src/img/boom_y.png"));

	setupLand();
	GameObject::font = LoadFontEx("src/SGK050.ttf",240,0,0);
	plantUI = PlantUI();
	plantUI.loadFonts();
	plantUI.init();
	plantUIButton = UIButton(496,48,32,32);
	plantUIButton.setImage(plantButton);
	plantUIButton.addUI(&plantUI);

	monsterUI = MonsterUI();
	monsterUI.loadFonts();
	monsterUI.init();
	monsterUIButton = UIButton(528,48,32,32);
	monsterUIButton.setImage(monsterButton);
	monsterUIButton.addUI(&monsterUI);
	monsterUI.initEditor(0);

	saveUI = FileUI();
	saveUI.loadFonts();
	saveUI.init(true);
	saveUIButton = UIButton(496,80,32,32);
	saveUIButton.setImage(saveButton);
	saveUIButton.addUI(&saveUI);

	loadUI = FileUI();
	loadUI.loadFonts();
	loadUI.init(false);
	loadUIButton = UIButton(528,80,32,32);
	loadUIButton.setImage(loadButton);
	loadUIButton.addUI(&loadUI);

	Meat::setMeatTexture(LoadTexture("src/img/meat.png"));
	MusicHandler::loadMusic();
	MusicHandler::playFirstSong(MusicHandler::dotWorld);

	messageBox.enable("Welcome!/Hey there, and welcome to this little/monster simulation game!/"
			"Right now, many small, simple monsters/are living on Blockster World!/"
			"/Click the Next Generation button to/have your monsters eat, die,/and reproduce now.");
	messageBox.init(GameObject::font);
}
void GameWindow::removePoints(int removePoints)
{
	points -= removePoints;
}
int GameWindow::getPoints()
{
	return points;
}
void GameWindow::setupLand()
{
	for(int x=0; x<60;x++)
	{
		for(int y=0; y<60;y++)
		{
			Ground* g = new Ground(16*x,16*y,16,16,true);
			g->setupFreshWaterGraphics(&freshwater0,&freshwater1);
			g->setupWaterGraphics(&water0,&water1);
			g->setupLandGraphics(&dirt,&beach,&tundra,&desert,&mountain,&snow);
			GameObject::objects.push_back(g);
			groundArray[x][y] = GameObject::objects[GameObject::objects.size()-1];

			Fog f = Fog(16*x,16*y);
			GameObject::fog[x][y] = f;
		}
	}

}

void GameWindow::tick()
{
	if(gameMode == TITLE_SCREEN)
	{
		titleScreenTick();
	}
	else if(gameMode == GAME_SCREEN)
	{
		gameTick();
	}
}

void GameWindow::render()
{
	if(gameMode == TITLE_SCREEN)
	{
		titleScreenRender();
	}
	else if(gameMode == GAME_SCREEN)
	{
		gameRender();
	}
}

void GameWindow::drawGUI()
{
	if(gameMode == TITLE_SCREEN)
	{
		titleScreenDrawGUI();
	}
	else if(gameMode == GAME_SCREEN)
	{
		gameDrawGUI();
	}
}

void GameWindow::titleScreenTick()
{
	loadUI.tick();
	if(getClicking(playX,playY,128,64))
	{
		gameMode = GAME_SCREEN;
		loadUI.lighten();
	}
	if(getClicking(loadX,loadY,128,64))
	{
		loadUI.toggle();
	}
}

MessageBox* GameWindow::getMessageBox()
{
	return &messageBox;
}


void GameWindow::gameTick()
{
	tutorialMessages();
	if(UI::isOpen())
	{
		showingUpperText = false;
	}
	if(GameObject::generation == 0 && genPhase == MOVE_PHASE)
	{
		doMove();
	}
	messageBox.tick();
	//cout << GetFPS() << " " << GameObject::objects.size() << endl;
	//cout << camera->offset.x << " " << camera->offset.y << endl;
	if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
	{
		showingUpperText = false;
	}
	if(GameObject::generation<0)
	{
		if(offsetTime<wait)
		{
			offsetTime++;
		}
		else
		{
			if(spacer <= 0)
			{
				doGeneration();
				spacer = spaceTime;
			}
			else
			{
				spacer--;
			}
		}
	}
	if(GameObject::generation == -1)
	{
		MusicHandler::playSong(MusicHandler::pirateKite);
	}
	if(GameObject::generation >= 0)
	{
		MusicHandler::handleMusic();
	}
	centerX = (240/camera->zoom)-(camera->offset.x/camera->zoom);
	centerY = (240/camera->zoom)-(camera->offset.y/camera->zoom);
	internalClock++;
	GameObject::setGroundArray(groundArray);
	if(!messageBox.getVisible() || GameObject::generation < 0)
	{
		for(uint i = GameObject::generation < 1 ? 0 : 0; i<GameObject::objects.size();i++)
		{
			vector<GameObject*> objects = GameObject::objects;
			GameObject* obj = GameObject::objects[i];
			obj->setInternalClock(internalClock);
			obj->tick();
			if(obj != nullptr && moving && obj->getName() == "Monster")
			{
				obj->nextMove();
			}
			GameObject* temp = GameObject::objects[i];
			if(temp)
			{
				if(temp->getName() == "Plant")
				{
					Plant* p = static_cast<Plant*>(temp);
					if(!(p->getAlive()))
					{
						delete(GameObject::objects[i]);
						GameObject::objects[i] = nullptr;
						GameObject::objects.erase(GameObject::objects.begin()+i);
					}
				}
				if(temp->getName() == "EyeCandy")
				{
					EyeCandy* p = static_cast<EyeCandy*>(temp);
					if((p->getTimeRemaining()<=0))
					{
						delete(GameObject::objects[i]);
						GameObject::objects[i] = nullptr;
						GameObject::objects.erase(GameObject::objects.begin()+i);
					}
				}
				if(temp->getName() == "Meat")
				{
					Meat* p = static_cast<Meat*>(temp);
					if(!(p->isAlive()))
					{
						delete(GameObject::objects[i]);
						GameObject::objects[i] = nullptr;
						GameObject::objects.erase(GameObject::objects.begin()+i);
					}
				}
			}
		}
	}
	/*
	for(uint i = 0; i<GameObject::objects.size();i++)
	{

	}*/
	moving = isMoving();
	if(GameObject::generation >= 1)
	{
		if(camera->zoom<8.0f)
		{
			if(IsKeyPressed(KEY_LEFT_SHIFT) || IsKeyPressed(KEY_RIGHT_SHIFT))
			{
				int dCenterX = centerX;
				int dCenterY = centerY;
				camera->zoom *= 2.0f;
				centerX = (240/camera->zoom)-(camera->offset.x/camera->zoom);
				centerY = (240/camera->zoom)-(camera->offset.y/camera->zoom);

				while(centerX<dCenterX)
				{
					camera->offset.x--;
					printf("(%d/%d, %d/%d)\n",centerX,dCenterX,centerY,dCenterY);
					centerX = (240/camera->zoom)-(camera->offset.x/camera->zoom);
					centerY = (240/camera->zoom)-(camera->offset.y/camera->zoom);
					if(centerX>=dCenterX)
					{
						break;
					}
				}
				while(centerX>dCenterX)
				{
					camera->offset.x++;
					printf("(%d/%d, %d/%d)\n",centerX,dCenterX,centerY,dCenterY);
					centerX = (240/camera->zoom)-(camera->offset.x/camera->zoom);
					centerY = (240/camera->zoom)-(camera->offset.y/camera->zoom);
					if(centerX<=dCenterX)
					{
						break;
					}
				}
				while(centerY>dCenterY)
				{
					camera->offset.y++;
					printf("(%d/%d, %d/%d)\n",centerX,dCenterX,centerY,dCenterY);
					centerX = (240/camera->zoom)-(camera->offset.x/camera->zoom);
					centerY = (240/camera->zoom)-(camera->offset.y/camera->zoom);
					if(centerY<=dCenterY)
					{
						break;
					}
				}
				while(centerY<dCenterY)
				{
					camera->offset.y--;
					printf("(%d/%d, %d/%d)\n",centerX,dCenterX,centerY,dCenterY);
					centerX = (240/camera->zoom)-(camera->offset.x/camera->zoom);
					centerY = (240/camera->zoom)-(camera->offset.y/camera->zoom);
					if(centerY>=dCenterY)
					{
						break;
					}
				}
			}
		}
		if(camera->zoom>0.5f)
		{
			if(IsKeyPressed(KEY_LEFT_CONTROL) || IsKeyPressed(KEY_RIGHT_CONTROL))
			{
				int dCenterX = centerX;
				int dCenterY = centerY;
				camera->zoom /= 2.0f;
				centerX = (240/camera->zoom)-(camera->offset.x/camera->zoom);
				centerY = (240/camera->zoom)-(camera->offset.y/camera->zoom);

				while(centerX<dCenterX)
				{
					camera->offset.x--;
					printf("(%d/%d, %d/%d)\n",centerX,dCenterX,centerY,dCenterY);
					centerX = (240/camera->zoom)-(camera->offset.x/camera->zoom);
					centerY = (240/camera->zoom)-(camera->offset.y/camera->zoom);
					if(centerX>=dCenterX)
					{
						break;
					}
				}
				while(centerX>dCenterX)
				{
					camera->offset.x++;
					printf("(%d/%d, %d/%d)\n",centerX,dCenterX,centerY,dCenterY);
					centerX = (240/camera->zoom)-(camera->offset.x/camera->zoom);
					centerY = (240/camera->zoom)-(camera->offset.y/camera->zoom);
					if(centerX<=dCenterX)
					{
						break;
					}
				}
				while(centerY>dCenterY)
				{
					camera->offset.y++;
					printf("(%d/%d, %d/%d)\n",centerX,dCenterX,centerY,dCenterY);
					centerX = (240/camera->zoom)-(camera->offset.x/camera->zoom);
					centerY = (240/camera->zoom)-(camera->offset.y/camera->zoom);
					if(centerY<=dCenterY)
					{
						break;
					}
				}
				while(centerY<dCenterY)
				{
					camera->offset.y--;
					printf("(%d/%d, %d/%d)\n",centerX,dCenterX,centerY,dCenterY);
					centerX = (240/camera->zoom)-(camera->offset.x/camera->zoom);
					centerY = (240/camera->zoom)-(camera->offset.y/camera->zoom);
					if(centerY>=dCenterY)
					{
						break;
					}
				}
			}
		}
		if(camera->zoom>8.0f)
		{
			camera->zoom = 8.0f;
		}
		if(camera->zoom<0.5f)
		{
			camera->zoom = 0.5f;
		}
		if(IsKeyDown(KEY_LEFT))
		{
			camera->offset.x += 16/*camera->zoom*/;
		}
		if(IsKeyDown(KEY_RIGHT))
		{
			camera->offset.x -= 16/*camera->zoom*/;
		}
		if(IsKeyDown(KEY_UP))
		{
			camera->offset.y += 16/*camera->zoom*/;
		}
		if(IsKeyDown(KEY_DOWN))
		{
			camera->offset.y -= 16/*camera->zoom*/;
		}
		if(false/*IsKeyPressed(KEY_R)*/)
		{
			reset();
		}
	}
	int max;
	if(camera->zoom>1)
	{
		max = 480*((2*camera->zoom)-1);
	}
	else
	{
		max = 480*((2*camera->zoom)-1);
	}
	if(camera->offset.x<-max)
	{
		camera->offset.x = -max;
	}
	if(camera->offset.y<-max)
	{
		camera->offset.y = -max;
	}
	if(camera->offset.x>0 || camera->zoom == 0.5f)
	{
		camera->offset.x = 0;
	}
	if(camera->offset.y>0 || camera->zoom == 0.5f)
	{
		camera->offset.y = 0;
	}
	runUI();
}


void GameWindow::titleScreenRender()
{
}

void GameWindow::gameRender()
{
	DrawRectangle(-100,-100,1500,1500,PURPLE);
	for(uint i=0; i<GameObject::objects.size();i++)
	{
		GameObject* obj = GameObject::objects[i];
		if(obj)
		{
			obj->render();
		}
	}
	for(uint i=0; i<GameObject::objects.size();i++)
	{
		GameObject* obj = GameObject::objects[i];
		if(obj)
		{
			if(obj->getName() == "EyeCandy" || obj->getName() == "Meat")
			{
					obj->render();
			}
		}
	}
	for(uint x=0; x<60; x++)
	{
		for(uint y=0; y<60; y++)
		{
			GameObject::fog[x][y].render();
		}

	}

}

void GameWindow::titleScreenDrawGUI()
{
	DrawTexture(titleScreen,0,0,WHITE);
	DrawRectangle(playX,playY,128,64,WHITE);
	DrawTextEx(GameObject::font,"PLAY",{playX+32,playY+16},36.0f,0.0f,BLACK); // @suppress("Invalid arguments")
	DrawRectangle(loadX,loadY,128,64,WHITE);
	DrawTextEx(GameObject::font,"LOAD",{loadX+32,loadY+16},36.0f,0.0f,BLACK); // @suppress("Invalid arguments")
	loadUI.render();
}

void GameWindow::gameDrawGUI()
{
	if(GameObject::generation >= 0)
	{
		plantUI.render();
		monsterUI.render();
		saveUI.render();
		loadUI.render();
		DrawRectangle(480,0,160,480,WHITE);
		string genString = "Gen: " + to_string(GameObject::generation);

		if(!UI::isOpen())
		{
			plantUIButton.render();
			monsterUIButton.render();
			saveUIButton.render();
			loadUIButton.render();
			if(genPhase == MOVE_PHASE)
			{
				DrawTexture(moveButton,NEXT_GEN_X,NEXT_GEN_Y,WHITE);
			}
			else if(!moving)
			{
				DrawTexture(nextGenButton,NEXT_GEN_X,NEXT_GEN_Y,WHITE);
			}
		}
		else
		{
			DrawRectangle(BACK_X,BACK_Y,BACK_W,BACK_H,RED);
			DrawTextEx(GameObject::font,"BACK TO MAP",{506,64},20,0.0f,WHITE);
		}
		Vector2 genPos;
		genPos.x = 496;
		genPos.y = 16;
		DrawTextEx(GameObject::font,&genString[0],genPos,24,0.0f,BLACK);
		genPos.x = 497;
		genPos.y = 16;
		DrawTextEx(GameObject::font,&genString[0],genPos,24,0.0f,BLACK);

		string pointString = "Evolve Pts: " + to_string(GameWindow::points);
		Vector2 ptPos;
		ptPos.x = 488;
		ptPos.y = 128;
		DrawTextEx(GameObject::font,&pointString[0],ptPos,24,0.0f,BLACK);
		ptPos.x = 489;
		ptPos.y = 128;
		DrawTextEx(GameObject::font,&pointString[0],ptPos,24,0.0f,BLACK);


		if(showingUpperText)
		{
			DrawRectangle(0,0,480,96,WHITE);
			DrawTextEx(GameObject::font,upperText.c_str(),{16,16},24,0.0f,BLACK);
		}
		messageBox.render();
	}
	else
	{
		DrawRectangle(0,0,640,480,BLACK);
		DrawTextEx(GameObject::font,"GENERATING MAP",{16,16},72,0.0f,WHITE);
		DrawTextEx(GameObject::font,"As you could probably imagine, it takes a minute or so for Blocksters",{16,100},18,0.0f,WHITE);
		DrawTextEx(GameObject::font,"Planets Construction Inc. to build a planet for you.",{16,112},18,0.0f,WHITE);
		DrawTextEx(GameObject::font,"You might feel like complaining, but they are working as fast as they",{16,124},18,0.0f,WHITE);
		DrawTextEx(GameObject::font,"can! Building planets is no small feat!",{16,136},18,0.0f,WHITE);

		DrawRectangle(16,432,608,32,WHITE);
		int slices = (GameObject::generation+15)*(608/15);
		DrawRectangle(16,432,slices,32,GREEN);
	}

}
void GameWindow::reset()
{
	for(uint i=0; i<GameObject::objects.size();i++)
	{
		GameObject::objects.clear();
	}
	this->setupLand();
	internalClock = 0;
	GameObject::generation = -15;
	for(int x = 0; x<60; x++)
	{
		for(int y = 0; y<60; y++)
		{
			GameObject::fog[x][y].enable();
		}
	}
	Species::monsterSpecies.clear();
	Species::plantSpecies.clear();
	generatePlants();
	generateMonsters(true);
}
bool GameWindow::clickUI(int x1, int y1, int x2, int y2)
{
	bool clicking = false;
	if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
	{
		int mx = GetMouseX();
		int my = GetMouseY();
		printf("%d, %d\n",mx,my);
		clicking = (mx >= x1 && my >= y1 && mx <= x1+x2 && my <= y1+y2);
		printf("%d\n",clicking);
	}
	return clicking;
}
void GameWindow::setPoints(int newPoints)
{
	points = newPoints;
}
void GameWindow::doGeneration()
{
	if(GameObject::generation % 5 == 0)
	{
		points += pointIncrease+1;
	}
	GameObject::resetEvolution();
	for(uint i = 0; i<GameObject::objects.size();i++)
	{
		GameObject* temp = GameObject::objects[i];
		if(temp != nullptr)
		{
			if(temp->getName().compare("Ground") == 0 || temp->getName().compare("Plant") == 0 || temp->getName().compare("Monster") == 0|| temp->getName().compare("Meat") == 0)
			{
				temp->nextGeneration();
			}
		}
		if(temp != nullptr && temp->getName() == "Plant")
		{
			Plant* p = static_cast<Plant*>(temp);
			if(!(p->getAlive()))
			{
				delete(GameObject::objects[i]);
				GameObject::objects.erase(GameObject::objects.begin()+i);
			}
		}
		if(temp != nullptr && temp->getName() == "Monster")
		{
			Monster* p = static_cast<Monster*>(temp);
			if(!(p->getAlive()))
			{
				delete(GameObject::objects[i]);
				GameObject::objects.erase(GameObject::objects.begin()+i);
			}
		}
	}
	if(GameObject::generation == -1)
	{
		for(int a = 0; a < 3; a++)
		{
			for(int c = a == 0 ? 0 : 1; c < 10; c++)
			{
				bool created = false;
				int rx;
				int ry;
				while(!created)
				{
					int foundPlant = 0;
					bool foundLand = false;
					rx = (rand()%120)*8;
					ry = (rand()%120)*8;
					for(unsigned int i = 0; i < GameObject::objects.size(); i++)
					{
						if(GameObject::objects[i]->getName() == "Plant")
						{
							if(std::abs(GameObject::objects[i]->getX() - rx) <= 16 && std::abs(GameObject::objects[i]->getY() - ry) <= 16)
							{
								foundPlant++;
							}
						}
						if(GameObject::objects[i]->getName() == "Ground")
						{
							if(std::abs(GameObject::objects[i]->getX() - rx) == 0 && std::abs(GameObject::objects[i]->getY() - ry) == 0)
							{
								Ground* g = static_cast<Ground*>(GameObject::objects[i]);
								if(g->getBiome() != WATER && g->getBiome() != FRESHWATER)
								{
									foundLand = true;
								}
							}
						}
					}
					if (foundLand && Species::monsterSpecies[c].land && foundPlant>4)
					{
						created = true;
					}
					if(!foundLand && !Species::monsterSpecies[c].land)
					{
						created = true;
					}
				}
				int enemyNum = rand()%8+1;
				if(!Species::monsterSpecies[c].enemy)
				{
					Monster* m = new Monster(rx+48,ry,enemyNum,true);
					Monster* m1 = new Monster(rx+48,ry+8,enemyNum,true);
					Monster* m2 = new Monster(rx+8,ry+48,enemyNum,true);
					Monster* m3 = new Monster(rx+8,ry+48,enemyNum,true);
					GameObject::objects.push_back(m);
					GameObject::objects.push_back(m1);
					GameObject::objects.push_back(m2);
					GameObject::objects.push_back(m3);
				}
				Monster* m = new Monster(rx,ry,c,Species::monsterSpecies[c].enemy);
				Monster* m1 = new Monster(rx,ry+8,c,Species::monsterSpecies[c].enemy);
				Monster* m2 = new Monster(rx+8,ry+8,c,Species::monsterSpecies[c].enemy);
				Monster* m3 = new Monster(rx+8,ry,c,Species::monsterSpecies[c].enemy);
				if(!Species::monsterSpecies[c].enemy)
				{
					camera->zoom = 4.0f;
					camera->offset.x -= (m->getX()-64)*4;
					camera->offset.y -= (m->getY()-64)*4;
				}
				GameObject::objects.push_back(m);
				GameObject::objects.push_back(m1);
				GameObject::objects.push_back(m2);
				GameObject::objects.push_back(m3);
			}
		}
	}
	GameObject::generation++;
	genPhase = MOVE_PHASE;
	//GameObject::objects.shrink_to_fit();
}
void GameWindow::doMove()
{
	printf("Hi!!!!\n");
	for(uint i = 3500; i<GameObject::objects.size();i++)
	{
		GameObject* temp = GameObject::objects[i];
		if(temp && temp->getName() == "Monster")
		{
			temp->nextMove();
		}
		if(temp && temp->getName() == "Monster")
		{
			Monster* p = static_cast<Monster*>(temp);
			if(p && !(p->getAlive()))
			{
				delete(GameObject::objects[i]);
				GameObject::objects.erase(GameObject::objects.begin()+i);
			}
		}
	}

	genPhase = END_PHASE;
}
void GameWindow::runUI()
{
	if(clickUI(NEXT_GEN_X,NEXT_GEN_Y,128,32) && !UI::isOpen())
	{
		if(genPhase == MOVE_PHASE)
		{
			for(unsigned int i = 0; i < GameObject::objects.size(); i++)
			{
				if(GameObject::objects[i] != nullptr && GameObject::objects[i]->getName() == "Monster")
				{
					Monster* m = static_cast<Monster*>(GameObject::objects[i]);
					m->resetMovement();

				}
			}
			doMove();
		}
		else if(!moving)
		{
			doGeneration();
		}
	}
	if(!UI::isOpen())
	{
		monsterUIButton.tick();
		plantUIButton.tick();
		saveUIButton.tick();
		loadUIButton.tick();
	}
	else
	{
		bool clicking = false;
		if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
		{
			int mx = GetMouseX();
			int my = GetMouseY();
			clicking = (mx >= BACK_X && my >= BACK_Y && mx <= BACK_X+BACK_W && my <= BACK_Y+BACK_H);
		}
		if(clicking)
		{
			UI::close();
		}
	}
	plantUI.tick();
	monsterUI.tick();
	saveUI.tick();
	loadUI.tick();
}

void GameWindow::generatePlants()
{

	for(unsigned int i=0; i<10;i++)
	{
		PlantSpecies sp;
		sp.lifespan = (rand()%6)+1;
		sp.minDeath = 1;
		sp.maxDeath = 2;
		sp.minNew = 0;
		sp.maxNew = 4;
		sp.size = (rand()%2)+1;
		sp.toxicity =0;
		sp.nutrients = (rand()%2)+1;
		sp.population = 0;
		sp.groupSize = 10;

		if(rand()%10<5)
		{
			sp.land = true;
		}
		else
		{
			sp.land = false;
		}
		if(rand()%5<=1)
		{
			sp.image = PlantImg::entryLevel3;
		}
		else if(rand()%5<=1)
		{
			sp.image = PlantImg::entryLevel2;
		}
		else if(sp.size>2)
		{
			sp.image = PlantImg::entryLevel1;
		}
		else
		{
			sp.image = PlantImg::entryLevel0;
		}
		int r = rand()%(ObjectColors::plantColorsStem.size());
		sp.image = Texture(sp.image);
		sp.stemColor = ObjectColors::plantColorsStem[r];
		int s = rand()%(ObjectColors::plantColorsFlower.size());
		sp.flowerColor = ObjectColors::plantColorsFlower[s];
		int t = rand()%(ObjectColors::plantColorsHighlight.size());
		sp.highlightColor = ObjectColors::plantColorsHighlight[t];
		sp.image = Species::replaceColorsToImage(&sp.image,ObjectColors::PLANT_GREEN,sp.stemColor);
		sp.image = Species::replaceColorsToImage(&sp.image,ObjectColors::ROSE_RED,sp.flowerColor);
		sp.name = Species::generateName();
		Species::plantSpecies.push_back(sp);
	}
}
void GameWindow::generateMonsters(bool enemy)
{

	for(unsigned int i=0; i<1;i++)
	{
		MonsterSpecies sp;
		sp.lifespan = 4;
		sp.minDeath = 0;
		sp.maxDeath = 2;
		sp.minNew = 0;
		sp.maxNew = 4;
		sp.size = 1;
		sp.toxicity = 0;
		sp.speed = 1;
		sp.strength = 1;
		sp.population = 0;
		sp.groupSize = 10;
		sp.metabolism = 1;
		sp.resil = 1;
		sp.carnivore = false;
		sp.agression = 2;

		if(rand()%10<7)
		{
			sp.land = true;
		}
		else
		{
			sp.land = true;
		}
		if(rand()%5<=1)
		{
			sp.image = MonsterImg::miniscule0;
		}
		else if(rand()%5<=1)
		{
			sp.image = MonsterImg::miniscule1;
		}
		else
		{
			sp.image = MonsterImg::miniscule2;
		}
		int r = rand()%(ObjectColors::monsterColors.size());
		sp.bodyColor = ObjectColors::monsterColors[r];
		sp.image = Texture(sp.image);
		sp.image = Species::replaceColorsToImage(&sp.image,ObjectColors::PLANT_GREEN,sp.bodyColor);

		int s = rand()%(ObjectColors::monsterColorsEyes.size());
		sp.eyeColor = ObjectColors::monsterColorsEyes[s];
		sp.image = Species::replaceColorsToImage(&sp.image,BLACK,sp.eyeColor);

		int t = rand()%(ObjectColors::monsterColorsHighlight.size());
		sp.highlightColor = ObjectColors::monsterColorsHighlight[t];
		sp.image = Species::replaceColorsToImage(&sp.image,ObjectColors::CYAN_BLUE,sp.highlightColor);
		sp.name = Species::generateName();
		sp.enemy = false;
		Species::monsterSpecies.push_back(sp);
	}
	for(unsigned int i=1; i<10;i++)
		{
			MonsterSpecies sp;
			sp.lifespan = 4;
			sp.minDeath = 0;
			sp.maxDeath = 2;
			sp.minNew = 0;
			sp.maxNew = 4;
			sp.size = 1;
			sp.toxicity = 0;
			sp.speed = 3;
			sp.strength = 1;
			sp.population = 0;
			sp.groupSize = 10;
			sp.metabolism = 1;
			sp.resil = 1;
			sp.carnivore = false;
			sp.enemy = true;
			sp.agression = 4;

			if(rand()%10<5)
			{
				sp.land = true;
			}
			else
			{
				sp.land = false;
			}
			if(rand()%5<=1)
			{
				sp.image = MonsterImg::miniscule0;
			}
			else if(rand()%5<=1)
			{
				sp.image = MonsterImg::miniscule1;
			}
			else
			{
				sp.image = MonsterImg::miniscule2;
			}
			int r = rand()%(ObjectColors::monsterColors.size());
			sp.bodyColor = ObjectColors::monsterColors[r];
			sp.image = Texture(sp.image);
			sp.image = Species::replaceColorsToImage(&sp.image,ObjectColors::PLANT_GREEN,sp.bodyColor);

			int s = rand()%(ObjectColors::monsterColorsEyes.size());
			sp.eyeColor = ObjectColors::monsterColorsEyes[s];
			sp.image = Species::replaceColorsToImage(&sp.image,BLACK,sp.eyeColor);

			int t = rand()%(ObjectColors::monsterColorsHighlight.size());
			sp.highlightColor = ObjectColors::monsterColorsHighlight[t];
			sp.image = Species::replaceColorsToImage(&sp.image,ObjectColors::CYAN_BLUE,sp.highlightColor);
			sp.name = Species::generateName();
			sp.enemy = true;
			Species::monsterSpecies.push_back(sp);
		}
}
bool GameWindow::isMoving()
{
	for(unsigned int i = 0; i < GameObject::objects.size(); i++)
	{
		if(GameObject::objects[i] != nullptr && GameObject::objects[i]->getName() == "Monster" && genPhase == END_PHASE)
		{
			Monster* m = static_cast<Monster*>(GameObject::objects[i]);
			if(m->isMoving())
			{
				return true;
			}
		}
	}
	return false;
}
Camera2D* GameWindow::getCamera()
{
	return camera;
}
void GameWindow::showUpperText(std::string text)
{
	showingUpperText = true;
	upperText = text;
}


bool GameWindow::getClicking(int x, int y, int width, int height)
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

void GameWindow::setGameScreen()
{
	gameMode = GAME_SCREEN;
}

void GameWindow::setFileName(std::string name)
{
	fileName = name;
}

std::string GameWindow::getFileName()
{
	return fileName;
}

void GameWindow::tutorialMessages()
{
	if(GameObject::generation == 1 && !tutorial[0])
	{
		messageBox.enable("Finish Moving Button"
				"/If you click the Finish Moving button in"
				"/the bottom-left corner, your monsters"
				"/will finish moving.//"
				"If you don't click it, your monsters will/"
				"stand still forever. Who's the real/"
				"monster now?");
		tutorial[0] = true;
	}
	if(GameObject::generation == 2 && !tutorial[1])
	{
		messageBox.enable("Selecting Monsters/"
				"If you click a monster, you will be/"
				"able to select it.//"
				"Doing that will let you view helpful/"
				"information about it.");
		tutorial[1] = true;
	}
}


