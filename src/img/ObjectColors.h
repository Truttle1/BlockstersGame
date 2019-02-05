/*
 * ObjectColors.h
 *
 *  Created on: Jan 31, 2019
 *      Author: truttle1
 */

#ifndef IMG_OBJECTCOLORS_H_
#define IMG_OBJECTCOLORS_H_
#include "../libraries/raylib.h"
#include <vector>
using namespace std;
class ObjectColors {
public:
	ObjectColors();
	virtual ~ObjectColors();
	static Color PLANT_GREEN;
	static Color ROSE_RED;
	static Color CYAN_BLUE;
	static Color SEA_GREEN;
	static Color SUN_YELLOW;
	static Color ALT_GREEN;
	static Color DARK_GREEN;
	static Color STEM_BROWN;
	static Color SKY_BLUE;
	static Color CRIMSON_RED;
	static vector<Color> plantColorsStem;
	static vector<Color> plantColorsFlower;
	static vector<Color> plantColorsHighlight;
	static void initColors();
};

#endif /* IMG_OBJECTCOLORS_H_ */
