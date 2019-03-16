/*
 * Object.h
 *
 *  Created on: Jan 2, 2019
 *      Author: truttle1
 */

#ifndef OBJECTS_WORLD_Object_H_
#define OBJECTS_WORLD_Object_H_

#include "../GameObject.h"
class Object:public GameObject {
	public:
		Object(int ix, int iy);
		virtual ~Object();
		void tick();
		void render();
		void nextGeneration();
		void nextEat();
		void nextMove();
		Rectangle getBounds();
	private:
};

#endif /* OBJECTS_WORLD_Object_H_ */
