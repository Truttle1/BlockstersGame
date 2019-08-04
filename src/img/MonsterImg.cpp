/*
 * MonsterImg.cpp
 *
 *  Created on: Feb 3, 2019
 *      Author: truttle1
 */

#include "MonsterImg.h"

Texture2D MonsterImg::basic0;
Texture2D MonsterImg::basic1;
Texture2D MonsterImg::basic2;
Texture2D MonsterImg::small0;
Texture2D MonsterImg::small1;
Texture2D MonsterImg::small2;
Texture2D MonsterImg::small3;
Texture2D MonsterImg::small4;
Texture2D MonsterImg::medium0;
Texture2D MonsterImg::medium1;
Texture2D MonsterImg::medium2;
Texture2D MonsterImg::miniscule0;
Texture2D MonsterImg::miniscule1;
Texture2D MonsterImg::miniscule2;
MonsterImg::MonsterImg() {
	// TODO Auto-generated constructor stub

}

MonsterImg::~MonsterImg() {
	// TODO Auto-generated destructor stub
}


void MonsterImg::initTextures()
{
	basic0 = LoadTexture("src/img/monsters/basicmonster0.png");
	basic1 = LoadTexture("src/img/monsters/basicmonster1.png");
	basic2 = LoadTexture("src/img/monsters/basicmonster2.png");
	miniscule0 = LoadTexture("src/img/monsters/miniscule0.png");
	miniscule1 = LoadTexture("src/img/monsters/miniscule1.png");
	miniscule2 = LoadTexture("src/img/monsters/miniscule2.png");
	small0 = LoadTexture("src/img/monsters/small0.png");
	small1 = LoadTexture("src/img/monsters/small1.png");
	small2 = LoadTexture("src/img/monsters/small2.png");
	small3 = LoadTexture("src/img/monsters/small3.png");
	small4 = LoadTexture("src/img/monsters/small4.png");
	medium0 = LoadTexture("src/img/monsters/medium0.png");
	medium1 = LoadTexture("src/img/monsters/medium1.png");
	medium2 = LoadTexture("src/img/monsters/medium2.png");
}
