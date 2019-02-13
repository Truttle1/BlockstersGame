/*
 * Fog.h
 *
 *  Created on: Feb 3, 2019
 *      Author: truttle1
 */

#ifndef OBJECTS_FOG_H_
#define OBJECTS_FOG_H_
#include "../libraries/raylib.h"
class Fog {
	public:
		Fog();
		Fog(int x, int y);
		virtual ~Fog();
		void disable();
		void render();
		bool isVisible();

	private:
		bool visible;
		int x;
		int y;

};

#endif /* OBJECTS_FOG_H_ */
