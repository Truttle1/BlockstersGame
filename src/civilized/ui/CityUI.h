/*
 * CityUI.h
 *
 *  Created on: Jun 30, 2019
 *      Author: truttle1
 */

#ifndef CIVILIZED_UI_CITYUI_H_
#define CIVILIZED_UI_CITYUI_H_

#include "../../ui/UI.h"
#include "CityItems.h"
#include <vector>
#include "CityButton.h"
#include <string>
#include <iostream>
class CityUI : public UI
{
public:
	CityUI();
	virtual ~CityUI();
	void tick();
	void render();
	void close();
	bool getRunning();
	void toggle();
	void init();
	void setColor(Color iColor);
	std::vector<CityButton> getCityButtons();
	int getDemand(int demandVal);
	void setDemand(int demandVal, int amount);
	void nextGeneration();

private:
	void setupButtons();
	void closeButtons();
	bool getClicking(int x, int y, int width, int height);
	Color color;
	bool running = false;
	std::vector<CityButton> cityButtons;
	std::vector<std::string> addTexts;
	std::vector<std::string> cityTexts;

	std::vector<int> demands;
};

#endif /* CIVILIZED_UI_CITYUI_H_ */
