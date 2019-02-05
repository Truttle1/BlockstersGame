/*
 * PlantUIButton.h
 *
 *  Created on: Jan 23, 2019
 *      Author: truttle1
 */

#ifndef UI_PLANTUI_UIBUTTON_H_
#define UI_PLANTUI_UIBUTTON_H_
#include "../libraries/raylib.h"
#include "UI.h"
class UIButton
{
	public:
		UIButton();
		UIButton(int x, int y, int width, int height);
		virtual ~UIButton();
		void tick();
		void render();
		void clicked();
		void setImage(Texture img);
		void addUI(UI* ui);
		int getX();
		int getY();
		int getWidth();
		int getHeight();
	private:
		Texture img;
		int x;
		int y;
		int width;
		int height;
		UI* ui;
};

#endif /* UI_PLANTUI_UIBUTTON_H_ */
