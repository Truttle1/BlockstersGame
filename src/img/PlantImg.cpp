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
Texture2D PlantImg::small3;
Texture2D PlantImg::small4;
Texture2D PlantImg::medium0;
Texture2D PlantImg::medium1;
Texture2D PlantImg::medium2;
Texture2D PlantImg::medium3;
Texture2D PlantImg::medium4;
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
	small3 = LoadTexture("src/img/plants/small3.png");
	small4 = LoadTexture("src/img/plants/small4.png");


	medium0 = LoadTexture("src/img/plants/medium0.png");
	medium1 = LoadTexture("src/img/plants/medium1.png");
	medium2 = LoadTexture("src/img/plants/medium2.png");
	medium3 = LoadTexture("src/img/plants/medium3.png");
	medium4 = LoadTexture("src/img/plants/medium4.png");
}
