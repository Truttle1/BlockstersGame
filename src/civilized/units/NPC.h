/*
 * NPC.h
 *
 *  Created on: Jul 24, 2019
 *      Author: truttle1
 */

#ifndef CIVILIZED_UNITS_NPC_H_
#define CIVILIZED_UNITS_NPC_H_
#include "Unit.h"
#include "../Territory.h"
class NPC : public Unit{
public:
	NPC(int ix, int iy);
	virtual ~NPC();
	void render();
	void tick();
	void nextGeneration();
	void nextEat();
	void finalize();
	void nextMove();

private:
	int startX;
	int startY;
};

#endif /* CIVILIZED_UNITS_NPC_H_ */
