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
	private:
		bool running;
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
		void clickLeft();
		void clickRight();
};

#endif /* UI_MONSTERUI_PLANTUI_H_ */
