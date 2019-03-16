/*
 * Meat.h
 *
 *  Created on: Feb 16, 2019
 *      Author: truttle1
 */

#ifndef OBJECTS_WORLD_MEAT_H_
#define OBJECTS_WORLD_MEAT_H_
#include "../GameObject.h"
class Meat : public GameObject{
public:
	Meat(int ix, int iy, int iNutrients);
	virtual ~Meat();
	static void setMeatTexture(Texture2D img);
	void tick();
	void render();
	void nextGeneration();
	void nextMove();
	void nextEat();
	bool isAlive();
	Rectangle getBounds();
	int eat();
private:
	int timeLeft;
	int nutrients;
	static Texture2D image;
	bool alive;
};

#endif /* OBJECTS_WORLD_MEAT_H_ */
