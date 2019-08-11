/*
 * Shelter.h
 *
 *  Created on: Jun 18, 2019
 *      Author: truttle1
 */

#ifndef OBJECTS_WORLD_SHELTER_H_
#define OBJECTS_WORLD_SHELTER_H_
#include "../GameObject.h"
#include "../../GameWindow.h"
class Shelter:public GameObject
{
	public:
		Shelter(int ix, int iy, int iSpecies, int iType, int iFood, int iPop);
		virtual ~Shelter();
		void tick();
		void render();
		void nextGeneration();
		void nextEat();
		void nextMove();
		Rectangle getBounds();
		static Texture2D basic0;
		static Texture2D basic1;
		static Texture2D simple0;
		static Texture2D simple1;
		void add(int iFood, int iPopulation);
		bool getAlive();

		int getSpecies();
		int getType();
		int getFood();
		int getPopulation();
		void deClick();
		void kill();

	private:
		bool getClicking();
		void exit();
		bool enemy;
		bool alive;
		int species;
		int type;
		int food;
		int population;
		int flashTime;
		bool wasClicked;
		int exitTime;
		bool addedPop;
};

#endif /* OBJECTS_WORLD_SHELTER_H_ */
