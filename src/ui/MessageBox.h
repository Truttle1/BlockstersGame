/*
 * MessageBox.h
 *
 *  Created on: Apr 8, 2019
 *      Author: truttle1
 */

#ifndef UI_MESSAGEBOX_H_
#define UI_MESSAGEBOX_H_
#include <string>
#include "../libraries/raylib.h"
#include <sstream>
#include <vector>
using namespace std;
class MessageBox {
public:
	MessageBox();
	void enable(std::string iText);
	virtual ~MessageBox();
	void init(Font iFont);
	bool getVisible();
	void tick();
	void render();
	void disable();
private:
	bool getClicking(int x, int y, int width, int height);
	bool visible;
	std::string text;
	Font font;
};

#endif /* UI_MESSAGEBOX_H_ */
