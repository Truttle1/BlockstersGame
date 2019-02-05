/*
 * UI.h
 *
 *  Created on: Jan 27, 2019
 *      Author: truttle1
 */

#ifndef UI_UI_H_
#define UI_UI_H_
#include "../libraries/raylib.h"

class UI {
	public:
		UI();
		virtual ~UI();
		virtual void toggle()=0;
		void loadFonts();
	protected:
		Font font;
		Font fontBig;
		bool getClicking(int x, int y, int width, int height);

	private:
		bool running;
};

#endif /* UI_UI_H_ */
