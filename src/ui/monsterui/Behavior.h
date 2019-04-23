/*
 * Behavior.h
 *
 *  Created on: Apr 15, 2019
 *      Author: truttle1
 */

#ifndef UI_MONSTERUI_BEHAVIOR_H_
#define UI_MONSTERUI_BEHAVIOR_H_
#include "../UI.h"
#include "../../species/Species.h"
#include <vector>

class Behavior {
public:
	Behavior(int iX, int iY, int iCost);
	virtual ~Behavior();
	int getStatus();
	void init(Texture2D iTexture,std::vector<std::string> iText);
	void enable();
	void disable();
	void tick();
	void render();
	void setStatus(int iStatus);
	int getCost();
	std::vector<std::string> getText();
private:
	bool getClicking(int nx, int ny, int wx, int wy);
	int status;
	Texture2D texture;
	bool visible = false;
	std::vector<std::string> text;
	int x;
	int y;
	int cost;
};

#endif /* UI_MONSTERUI_BEHAVIOR_H_ */
