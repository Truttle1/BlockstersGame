/*
 * RadioButton.h
 *
 *  Created on: Mar 3, 2019
 *      Author: truttle1
 */

#ifndef UI_MONSTERUI_RADIOBUTTON_H_
#define UI_MONSTERUI_RADIOBUTTON_H_
#include "../../libraries/raylib.h"
#include <string>
#include <vector>
#include <sstream>
using namespace std;

class RadioButton {
public:
	RadioButton();
	RadioButton(int ix, int iy, Font iFont);
	virtual ~RadioButton();
	void tick();
	void render();
	int getSelected();
	void addOption(string optionName, int optionCost);
private:
	int x;
	int y;
	Font font;
	Color color;
	int selected;
	vector<string> options;
	vector<int> optionCosts;
	bool getClicking(int nx, int ny);
};

#endif /* UI_MONSTERUI_RADIOBUTTON_H_ */
