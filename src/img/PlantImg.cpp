/*
 * PlantImg.cpp
 *
 *  Created on: Jan 22, 2019
 *      Author: truttle1
 */

#include "PlantImg.h"

Texture2D PlantImg::entryLevel0;
Texture2D PlantImg::entryLevel1;
Texture2D PlantImg::entryLevel2;
Texture2D PlantImg::entryLevel3;
Texture2D PlantImg::small0;
Texture2D PlantImg::small1;
Texture2D PlantImg::small2;
PlantImg::PlantImg() {
	// TODO Auto-generated constructor stub

}

PlantImg::~PlantImg() {
	// TODO Auto-generated destructor stub
}

void PlantImg::initTextures()
{
	entryLevel0 = LoadTexture("src/img/plants/entrylevel0.png");
	entryLevel1 = LoadTexture("src/img/plants/entrylevel1.png");
	entryLevel2 = LoadTexture("src/img/plants/entrylevel2.png");
	entryLevel3 = LoadTexture("src/img/plants/entrylevel3.png");

	small0 = LoadTexture("src/img/plants/small0.png");
	small1 = LoadTexture("src/img/plants/small1.png");
	small2 = LoadTexture("src/img/plants/small2.png");
}
