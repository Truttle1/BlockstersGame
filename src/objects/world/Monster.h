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
#include "Shelter.h"
#include "../../img/MonsterImg.h"
#include "../../GameWindow.h"
#include "../EyeCandy.h"
#include "../../ui/UI.h"
#include "../../species/Behaviors.h"
class Monster:public GameObject {
	public:
		Monster(int ix, int iy, int sp, bool e);
		virtual ~Monster();
		void tick();
		void loadFromFile(int iAge, int iHp, int population);
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
		int getHP();
		int getAge();
		int getPopulation();
		void setPoison(int amount);
		void setShelterLoc(int ix, int iy);
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
		void closeFarMovement();
		void groupingMovement();
		void plantsMovement();
		void meatMovement();
		void shelterMovement();
		double distanceToPlayer();
		int distanceToFrom(int ex, int ey, int sx, int sy);
		void createShelter();
		void enterShelter();
		bool onShelter();
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
		bool killed = false;
		int poison = 0;
		int clusterX;
		int clusterY;
		Biome biome = DIRT;
		int shelterX = -1;
		int shelterY = -1;
		bool wasClicked;

};

#endif /* OBJECTS_WORLD_Object_H_ */
