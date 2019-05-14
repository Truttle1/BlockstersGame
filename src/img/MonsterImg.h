/*
 * MonsterImg.h
 *
 *  Created on: Feb 3, 2019
 *      Author: truttle1
 */

#ifndef IMG_MONSTERIMG_H_
#define IMG_MONSTERIMG_H_
#include "../libraries/raylib.h"
class MonsterImg {
public:
	MonsterImg();
	virtual ~MonsterImg();
	static void initTextures();
	static Texture2D basic0;
	static Texture2D basic1;
	static Texture2D basic2;
	static Texture2D small0;
	static Texture2D small1;
	static Texture2D small2;
	static Texture2D small3;
	static Texture2D small4;
	static Texture2D medium0;
	static Texture2D medium1;
	static Texture2D medium2;
	static Texture2D miniscule0;
	static Texture2D miniscule1;
	static Texture2D miniscule2;
};

#endif /* IMG_MONSTERIMG_H_ */
