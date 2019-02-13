/*
 * Object.h
 *
 *  Created on: Jan 2, 2019
 *      Author: truttle1
 */

#ifndef OBJECTS_WORLD_Object_H_
#define OBJECTS_WORLD_Object_H_

#include "../GameObject.h"
#include "Plant.h"
#include "../../img/MonsterImg.h"
#include "../../GameWindow.h"
#include "../EyeCandy.h"
class Monster:public GameObject {
	public:
		Monster(int ix, int iy, int sp, bool e);
		virtual ~Monster();
		void tick();
		void render();
		void nextGeneration();
		void nextEat();
		void nextMove();
		Rectangle getBounds();
		int getSpecies();
		bool getAlive();
		void kill();
		bool isMoving();
		void resetMovement();
		bool isEnemy();
	private:
		int getNeighborhood();
		void killSameLocation();
		void evolve();
		Biome getBiome();
		void removeFog();
		void selectRandomTarget();
		void eatPlant(Plant* p);
		void attackMonsters();
		bool getClicking();

		bool hasEaten;
		int species;
		bool alive = true;
		int arbitraryPopNumber;
		int age;
		bool enemy;
		bool moved;
		int targetX;
		int targetY;
		int movementStage;
		int hp;
		MonsterSpecies monster;
		int mouseX;
		int mouseY;
		int flashTime;
		bool clickedHere;
};

#endif /* OBJECTS_WORLD_Object_H_ */
