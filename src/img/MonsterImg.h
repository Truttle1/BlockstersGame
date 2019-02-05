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
};

#endif /* IMG_MONSTERIMG_H_ */
