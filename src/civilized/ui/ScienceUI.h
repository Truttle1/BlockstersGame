/*
 * ScienceUI.h
 *
 *  Created on: Jul 19, 2019
 *      Author: truttle1
 */

#ifndef CIVILIZED_UI_SCIENCEUI_H_
#define CIVILIZED_UI_SCIENCEUI_H_

#include "../../ui/UI.h"
#include "CityItems.h"
#include <vector>
#include "ScienceButton.h"
#include <string>
#include <iostream>
#include "../Techs.h"
#include "../Civilizations.h"
#include "../CivHandler.h"

class ScienceUI : public UI
{
public:
	ScienceUI();
	virtual ~ScienceUI();
	void toggle();
	void init();
	void tick();
	void render();
	bool getRunning();
	void setColor(Color iColor);
private:
	bool getClicking(int x, int y, int width, int height);
	void setupButtons();
	void closeButtons();
	bool running = false;
	Color color;
	std::vector<ScienceButton> sciButtons;
	std::vector<std::string> addTexts;
	std::vector<std::string> sciTexts;
	int behave;
	int RESEARCH_X = 224;
	int RESEARCH_Y = 416;
};

#endif /* CIVILIZED_UI_SCIENCEUI_H_ */
