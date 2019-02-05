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
MonsterImg::MonsterImg() {
	// TODO Auto-generated constructor stub

}

MonsterImg::~MonsterImg() {
	// TODO Auto-generated destructor stub
}


void MonsterImg::initTextures()
{
	basic0 = LoadTexture("src/img/plants/basicmonster0.png");
	basic1 = LoadTexture("src/img/plants/basicmonster1.png");
	basic2 = LoadTexture("src/img/plants/basicmonster2.png");
}
