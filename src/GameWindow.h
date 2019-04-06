/*
 * Game.h
 *
 *  Created on: Nov 6, 2018
 *      Author: truttle1
 */

#ifndef GAMEWINDOW_H_
#define GAMEWINDOW_H_
#include "libraries/raylib.h"
#include "objects/GameObject.h"
#include "objects/world/Ground.h"
#include "objects/world/Plant.h"
#include "objects/world/Monster.h"
#include "species/Species.h"
#include "img/PlantImg.h"
#include "img/MonsterImg.h"
#include "ui/plantui/PlantUI.h"
#include "ui/monsterui/MonsterUI.h"
#include "MusicHandler.h"
#include <vector>
#include <iostream>
#include <cmath>
#include <string>

#include "ui/UIButton.h"
#include "libraries/raylib.h"
#include "stdio.h"
#include "species/Species.h"
#include "img/PlantImg.h"
#include "img/ObjectColors.h"
#include "objects/EyeCandy.h"
#include "objects/world/Meat.h"
#include "ui/fileui/FileUI.h"
using namespace std;
class GameWindow {

	typedef enum {TITLE_SCREEN,GAME_SCREEN} GameMode;
public:
	GameWindow();
	virtual ~GameWindow();
	void init(Camera2D* cam);
	void render();
	void tick();
	void drawGUI();
	void reset();
	const int WINDOW_WIDTH = 640;
	const int WINDOW_HEIGHT = 480;
	static Camera2D* getCamera();
	static void showUpperText(std::string text);
	static int getPoints();
	static void removePoints(int removePoints);
	static void setPoints(int newPoints);
	static int pointIncrease;
	static void setGameScreen();
	static void setFileName(std::string name);
	static std::string getFileName();

private:
	void gameTick();
	void titleScreenTick();
	void gameRender();
	void titleScreenRender();
	void gameDrawGUI();
	void titleScreenDrawGUI();
	static GameMode gameMode;
	GameObject* groundArray[60][60];
	static std::string fileName;
	Texture water0;
	Texture water1;
	Texture freshwater0;
	Texture freshwater1;
	Texture dirt;
	Texture beach;
	Texture jungle;
	Texture grass;
	Texture tundra;
	Texture mountain;
	Texture snow;
	Texture desert;
	//BUTTONS
	Texture nextGenButton;
	Texture eatButton;
	Texture moveButton;
	Texture plantButton;
	UIButton plantUIButton;
	Texture monsterButton;
	UIButton monsterUIButton;
	Texture saveButton;
	Texture loadButton;
	UIButton saveUIButton;
	UIButton loadUIButton;
	PlantUI plantUI;
	MonsterUI monsterUI;
	Texture titleScreen;

	static Camera2D* camera;
	int internalClock;
	void setupLand();
	bool clickUI(int x1, int y1, int x2, int y2);
	void doGeneration();
	void doMove();
	void runUI();
	int centerX = 0;
	int centerY = 0;
	static int points;
	const int NEXT_GEN_X = 496;
	const int NEXT_GEN_Y = 432;
	const int MOVE_PHASE = 0;
	const int END_PHASE = 1;
	int genPhase = 0;
	void generatePlants();
	void generateMonsters(bool enemy);
	bool isMoving();
	bool moving;
	int offsetTime = 0;
	const int wait = 60;
	static bool showingUpperText;
	static std::string upperText;

	const int BACK_X = 496;
	const int BACK_Y = 48;
	const int BACK_W = 112;
	const int BACK_H = 64;

	const int playX = 64;
	const int playY = 192;

	const int loadX = 64;
	const int loadY = 320;

	int spacer = 0;
	int spaceTime = 5;

	bool getClicking(int x, int y, int width, int height);


};

#endif /* GAMEWINDOW_H_ */
