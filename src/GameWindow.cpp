/*
 * GameWindow.cpp
 *
 *  Created on: Nov 6, 2018
 *      Author: truttle1
 */

#include "GameWindow.h"


GameWindow::GameWindow() {

}

GameWindow::~GameWindow() {
}

void GameWindow::init(Camera2D* camera)
{
	this->camera = camera;
	this->camera->offset = {0,0};
	this->camera->target = {0,0};
	this->camera->zoom = 0.5f;
	this->camera->rotation = 0.0f;


	SetTargetFPS(60);
	InitWindow(GameWindow::WINDOW_WIDTH,GameWindow::WINDOW_HEIGHT,"Blocksters - A Truttle1 Game");

	PlantImg::initTextures();
	PlantSpecies sp;
	ObjectColors::initColors();
	for(unsigned int i=0; i<10;i++)
	{
		sp.lifespan = (rand()%6)+1;
		sp.minDeath = 1;
		sp.maxDeath = 2;
		sp.minNew = 0;
		sp.maxNew = 4;
		sp.size = (rand()%3)+1;
		sp.toxicity =(rand()%3)+1;
		sp.nutrients = (rand()%3)+1;
		sp.population = 0;
		sp.groupSize = 10;
		if(rand()%10<7)
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

	setupLand();
	GameObject::font = LoadFontEx("src/SGK050.ttf",240,0,0);
	plantUI = PlantUI();
	plantUI.loadFonts();
	plantUI.init();
	plantUIButton = UIButton(496,48,32,32);
	plantUIButton.setImage(plantButton);
	plantUIButton.addUI(&plantUI);


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
	centerX = (240/camera->zoom)-(camera->offset.x/camera->zoom);
	centerY = (240/camera->zoom)-(camera->offset.y/camera->zoom);
	internalClock++;
	GameObject::setGroundArray(groundArray);
	for(uint i=0; i<GameObject::objects.size();i++)
	{
		vector<GameObject*> objects = GameObject::objects;
		GameObject* obj = GameObject::objects[i];
		obj->tick();
		obj->setInternalClock(internalClock);
	}

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
	if(IsKeyPressed(KEY_R))
	{
		reset();
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
void GameWindow::render()
{
	DrawRectangle(-100,-100,1500,1500,PURPLE);
	for(uint i=0; i<GameObject::objects.size();i++)
	{
		GameObject* obj = GameObject::objects[i];
		obj->render();
	}
	for(uint x=0; x<60; x++)
	{
		for(uint y=0; y<60; y++)
		{
			GameObject::fog[x][y].render();
		}

	}
}
void GameWindow::drawGUI()
{
	plantUI.render();
	DrawRectangle(480,0,160,480,WHITE);
	string genString = "Gen: " + to_string(GameObject::generation);

	plantUIButton.render();
	Vector2 genPos;
	genPos.x = 496;
	genPos.y = 16;
	DrawTextEx(GameObject::font,&genString[0],genPos,24,0.0f,BLACK);
	genPos.x = 497;
	genPos.y = 16;
	DrawTextEx(GameObject::font,&genString[0],genPos,24,0.0f,BLACK);

	DrawTexture(nextGenButton,NEXT_GEN_X,NEXT_GEN_Y,WHITE);
}
void GameWindow::reset()
{
	for(uint i=0; i<GameObject::objects.size();i++)
	{
		GameObject::objects.clear();
	}
	this->setupLand();
	internalClock = 0;
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
void GameWindow::doGeneration()
{
	printf("%d",Species::plantSpecies[0].land);
	GameObject::resetEvolution();
	for(uint i = 0; i<GameObject::objects.size();i++)
	{
		GameObject* temp = GameObject::objects[i];
		if(temp->getName() == "Ground" || temp->getName() == "Plant")
		{
			temp->nextGeneration();
		}
		if(temp->getName() == "Plant")
		{
			Plant* p = static_cast<Plant*>(temp);
			if(!(p->getAlive()))
			{
				GameObject::objects[i] = NULL;
				delete(GameObject::objects[i]);
				GameObject::objects.erase(GameObject::objects.begin()+i);
			}
		}
	}
	GameObject::generation++;
}
void GameWindow::runUI()
{
	if(clickUI(NEXT_GEN_X,NEXT_GEN_Y,128,32))
	{
		if(genPhase == MOVE_PHASE)
		{
			doMove();
		}
		else
		{
			doGeneration();
		}
	}
	plantUIButton.tick();
	plantUI.tick();
}

void GameWindow::doMove()
{

	for(uint i = 0; i<GameObject::objects.size();i++)
	{
		GameObject* temp = GameObject::objects[i];
		if(temp->getName() == "Monster")
		{
			temp->nextMove();
		}
		if(temp->getName() == "Monster")
		{
			Plant* p = static_cast<Plant*>(temp);
			if(!(p->getAlive()))
			{
				GameObject::objects[i] = NULL;
				delete(GameObject::objects[i]);
				GameObject::objects.erase(GameObject::objects.begin()+i);
			}
		}
	}
}


