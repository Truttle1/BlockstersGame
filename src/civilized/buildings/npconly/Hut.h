/*
 * Hut.h
 *
 *  Created on: Jul 24, 2019
 *      Author: truttle1
 */

#ifndef CIVILIZED_BUILDINGS_NPCONLY_HUT_H_
#define CIVILIZED_BUILDINGS_NPCONLY_HUT_H_
#include "../Building.h"
#include "../../units/NPC.h"
class Hut : public Building
{
public:
	Hut(int ix, int iy);
	virtual ~Hut();
	void tick();
	void render();
	void nextGeneration();
	void nextMove();
	void nextEat();
	void finalize();
	static void setImage(Texture2D iImage);
private:
	static Texture2D image;
	static bool loadedImages;
};

#endif /* CIVILIZED_BUILDINGS_NPCONLY_HUT_H_ */
