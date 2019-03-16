/*
 * TextBox.h
 *
 *  Created on: Feb 23, 2019
 *      Author: truttle1
 */

#ifndef UI_MONSTERUI_TEXTBOX_H_
#define UI_MONSTERUI_TEXTBOX_H_
#include "../../libraries/raylib.h"
#include <string>
class TextBox {
	public:
		TextBox();
		TextBox(int ix, int iy, std::string iText, Font iFont);
		void tick();
		void render();
		std::string getText();
		virtual ~TextBox();
	private:
		int x;
		int y;
		void type();
		std::string text;
		static const int MAX_LENGTH = 13;
		bool getClicking(int x, int y, int width, int height);
		bool typing;
		Font font;
};

#endif /* UI_MONSTERUI_TEXTBOX_H_ */
