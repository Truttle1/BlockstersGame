/*
 * ColorBox.h
 *
 *  Created on: Feb 18, 2019
 *      Author: truttle1
 */

#ifndef UI_MONSTERUI_COLORBOX_H_
#define UI_MONSTERUI_COLORBOX_H_
#include "../UI.h"
#include "../../species/Species.h"
#include <vector>
class ColorBox
{
public:
	ColorBox();
	~ColorBox();
	void init(int ix, int iy, Color icolor);
	void tick();
	void render();
	Color getColor();
	Texture replaceColorsToImage(Texture* image, Color c1, Color c2);
	bool getSelected();
private:
	Texture2D regular;
	Texture2D pressed;
	int x;
	int y;
	Color color;
	bool selected;

};

#endif /* UI_MONSTERUI_COLORBOX_H_ */
