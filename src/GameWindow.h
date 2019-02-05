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
#include "species/Species.h"
#include "img/PlantImg.h"
#include "ui/plantui/PlantUI.h"
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
using namespace std;
class GameWindow {
public:
	GameWindow();
	virtual ~GameWindow();
	void init(Camera2D* camera);
	void render();
	void tick();
	void drawGUI();
	void reset();
	const int WINDOW_WIDTH = 640;
	const int WINDOW_HEIGHT = 480;

private:
	GameObject* groundArray[60][60];
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

	PlantUI plantUI;

	Camera2D* camera;
	int internalClock;
	void setupLand();
	bool clickUI(int x1, int y1, int x2, int y2);
	void doGeneration();
	void doMove();
	void runUI();
	int centerX = 0;
	int centerY = 0;
	const int NEXT_GEN_X = 496;
	const int NEXT_GEN_Y = 432;
	const int MOVE_PHASE = 0;
	int genPhase = 0;
};

#endif /* GAMEWINDOW_H_ */