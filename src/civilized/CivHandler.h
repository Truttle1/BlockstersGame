/*
 * CivHandler.h
 *
 *  Created on: Jun 26, 2019
 *      Author: truttle1
 */

#ifndef CIVILIZED_CIVHANDLER_H_
#define CIVILIZED_CIVHANDLER_H_
#include "../libraries/raylib.h"
#include "Civilizations.h"
#include "../ui/UIButton.h"
#include "ui/CityUI.h"
#include "ui/ScienceUI.h"
#include "buildings/Building.h"

#include <iostream>
class CivHandler
{
	public:
		CivHandler();
		virtual ~CivHandler();
		static void init();
		static void tick();
		static void render();
		static void drawGUI();
		static Color getColor();
		static void addCivilization(bool enemy, int monster, int color);
		static CityUI getCityUI();
		static int getCameraZoom();
		static int getOffsetX();
		static int getOffsetY();
		static void setOffsets(int iZoom, int iX, int iY);
		static void removeDolurz(int remove);
		static int getDolurz();
		static void setDolurz(int set);
		static void addPopulation(int add);
		static int getPopulation();
		static void doMove();
		static void doTurn();
		static void payTaxes(int money);
		static void spend(double money);
		static void setDemand(int demandVal, int amount);
		static int getDemand(int demandVal);
		static void doGeneration();

	private:
		static Texture2D cityButton;
		static Texture2D scienceButton;
		static UIButton cityUIButton;
		static UIButton scienceUIButton;
		static CityUI cityUI;
		static bool getClicking(int x, int y, int width, int height);
		static const int BACK_X = 496;
		static const int BACK_Y = 48;
		static const int BACK_W = 112;
		static const int BACK_H = 64;
		static int zoom;
		static int x;
		static int y;
		static int dolurz;
		static int population;
		static int taxes;
		static double expenses;
		static double expenseRate;
		static double taxRate;


		static void addTaxMoney();
		static void addExpenses();

};

#endif /* CIVILIZED_CIVHANDLER_H_ */
