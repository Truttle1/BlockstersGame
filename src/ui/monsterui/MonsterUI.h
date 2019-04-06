/*
 * PlantUI.h
 *
 *  Created on: Jan 24, 2019
 *      Author: truttle1
 */

#ifndef UI_MONSTERUI_PLANTUI_H_
#define UI_MONSTERUI_PLANTUI_H_
#include "../UI.h"
#include "../../species/Species.h"
#include "TextBox.h"
#include "ColorBox.h"
#include "RadioButton.h"
#include <vector>
class MonsterUI : public UI
{
	public:
		MonsterUI();
		virtual ~MonsterUI();
		void tick();
		void render();
		void close();
		bool getRunning();
		void  toggle();
		void init();
		void initEditor(int species);
	private:
		bool running;
		bool editing;
		int speciesEditing;
		unsigned int curViewing = 0;
		float startX = 128.0f;
		float startY = 128.0f;
		float size = 16.0f;
		Rectangle srcRect = {0.0f,0.0f,8.0f,8.0f};
		Rectangle destRect = {startX,startY,startX+size,startY+size};
		Vector2 origin = {startX,startY};
		void drawStats();
		Texture2D leftButton;
		Texture2D rightButton;

		int leftButtonX = 16;
		int leftButtonY = 432;
		int rightButtonX = 432;
		int rightButtonY = 432;

		float saveButtonX = 360;
		float saveButtonY = 432;

		void clickLeft();
		void clickRight();
		void drawEditScreen();
		void tickEditScreen();
		Color grid[8][8];
		Color drawingColor = {0,0,0,255};
		std::vector<ColorBox> colors;
		TextBox textBox;

		RadioButton birthChanceButton;
		RadioButton immuneSystemButton;
		RadioButton sizeButton;
		RadioButton sizeButton2;
		RadioButton speedButton;
		RadioButton strengthButton;
		RadioButton carnivoreButton;
		RadioButton hostilityButton;
		int page = 0;
		int maxPage = 3;

		int minNewUpdate;
		int maxNewUpdate;
		int minDeathUpdate;
		int maxDeathUpdate;
		int lifespanUpdate;
		int toxicityUpdate;
		int sizeUpdate;
		int speedUpdate;
		int strengthUpdate;
		int resilUpdate;
		int metaUpdate;
		int hostilityUpdate;
		bool carnivoreUpdate;

		void calculateUpdates();
		void saveMonster();

		int editButtonX = 300;
		int editButtonY = 432;

		float switchButtonX = 128;
		float switchButtonY = 432;

		int currentCost;

		bool lookingAtPlayer;
		int index;
};

#endif /* UI_MONSTERUI_PLANTUI_H_ */
