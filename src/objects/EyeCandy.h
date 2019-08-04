/*
 * EyeCandy.h
 *
 *  Created on: Feb 12, 2019
 *      Author: truttle1
 */

#ifndef OBJECTS_EYECANDY_H_
#define OBJECTS_EYECANDY_H_
#include "GameObject.h"
class EyeCandy : public GameObject
{
	public:
		EyeCandy(int ix, int iy, int iImage);
		virtual ~EyeCandy();
		void tick();
		void render();
		void nextGeneration();
		void nextEat();
		void nextMove();
		Rectangle getBounds();
		static void setBoomR(Texture2D img);
		static void setBoomY(Texture2D img);
		static void setBoomO(Texture2D img);
		int getTimeRemaining();
	private:
		int image;
		static Texture2D boom_r;
		static Texture2D boom_y;
		static Texture2D boom_o;
		int timeRemaining;
};

#endif /* OBJECTS_EYECANDY_H_ */
