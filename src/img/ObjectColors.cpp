/*
 * ObjectColors.cpp
 *
 *  Created on: Jan 31, 2019
 *      Author: truttle1
 */

#include "ObjectColors.h"

Color ObjectColors::PLANT_GREEN = {0,192,0,255};
Color ObjectColors::ROSE_RED = {255,0,0,255};
Color ObjectColors::CYAN_BLUE = {0,255,255,255};
Color ObjectColors::SEA_GREEN = {0,255,128,255};
Color ObjectColors::ALT_GREEN = {0,255,0,255};
Color ObjectColors::DARK_GREEN = {0,128,0,255};
Color ObjectColors::STEM_BROWN = {128,128,0,255};
Color ObjectColors::SUN_YELLOW = {255,255,0,255};
Color ObjectColors::SKY_BLUE = {0,128,255,255};
Color ObjectColors::CRIMSON_RED = {128,20,5,255};
vector<Color> ObjectColors::plantColorsStem;
vector<Color> ObjectColors::plantColorsFlower;
vector<Color> ObjectColors::plantColorsHighlight;

ObjectColors::ObjectColors() {
	// TODO Auto-generated constructor stub

}

ObjectColors::~ObjectColors() {
	// TODO Auto-generated destructor stub
}
void ObjectColors::initColors()
{
	plantColorsStem.push_back(PLANT_GREEN);
	plantColorsStem.push_back(ALT_GREEN);
	plantColorsStem.push_back(DARK_GREEN);
	plantColorsStem.push_back(STEM_BROWN);

	plantColorsFlower.push_back(ROSE_RED);
	plantColorsFlower.push_back(CYAN_BLUE);
	plantColorsFlower.push_back(ALT_GREEN);
	plantColorsFlower.push_back(SUN_YELLOW);
	plantColorsFlower.push_back(SKY_BLUE);
	plantColorsFlower.push_back(CRIMSON_RED);

	plantColorsHighlight.push_back(ROSE_RED);
	plantColorsHighlight.push_back(CYAN_BLUE);
	plantColorsHighlight.push_back(ALT_GREEN);
	plantColorsHighlight.push_back(SUN_YELLOW);
	plantColorsHighlight.push_back(SKY_BLUE);
	plantColorsHighlight.push_back(CRIMSON_RED);
}

