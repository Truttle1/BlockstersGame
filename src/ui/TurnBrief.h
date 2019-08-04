/*
 * TurnBrief.h
 *
 *  Created on: Apr 8, 2019
 *      Author: truttle1
 */

#ifndef UI_TurnBrief_H_
#define UI_TurnBrief_H_
#include <string>
#include "../libraries/raylib.h"
#include "../species/Species.h"
#include <sstream>
#include <vector>
using namespace std;
class TurnBrief {
public:
	TurnBrief();
	virtual ~TurnBrief();
	void init(Font iFont);
	bool getVisible();
	void enable();
	void tick();
	void render();
	void disable();
private:
	bool getClicking(int x, int y, int width, int height);
	bool visible;
	Font font;
	Texture2D stay;
	Texture2D up;
	Texture2D down;
	Texture2D arrow;
	bool loaded = false;

	int oldest;
	int newest;
	int increase;
	int decrease;

	int oldestR;
	int newestR;
	int increaseR;
	int decreaseR;
};

#endif /* UI_TurnBrief_H_ */
