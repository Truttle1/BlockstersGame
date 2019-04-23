/*
 * PlantImg.h
 *
 *  Created on: Jan 22, 2019
 *      Author: truttle1
 */

#ifndef IMG_PLANTIMG_H_
#define IMG_PLANTIMG_H_
#include "../libraries/raylib.h"
class PlantImg {
public:
	PlantImg();
	virtual ~PlantImg();
	static Texture2D entryLevel0;
	static Texture2D entryLevel1;
	static Texture2D entryLevel2;
	static Texture2D entryLevel3;

	static Texture2D small0;
	static Texture2D small1;
	static Texture2D small2;
	static Texture2D small3;

	static Texture2D medium0;
	static Texture2D medium1;
	static Texture2D medium2;
	static void initTextures();
};

#endif /* IMG_PLANTIMG_H_ */
