/*
 * GameObject.h
 *
 *  Created on: Nov 4, 2018
 *      Author: truttle1
 */
#ifndef RAYLIB
#define RAYLIB
#include "../libraries/raylib.h"
#include "../img/PlantImg.h"
#endif
#include <vector>
#include <string>
#include <cstdlib>
#include <iostream>
;using namespace std;
typedef unsigned int uint;
#ifndef OBJECTS_GAMEOBJECT_H_
	#define OBJECTS_GAMEOBJECT_H_
	#include "Fog.h"
	typedef enum Biome{WATER,DIRT,BEACH,DESERT,GRASS,JUNGLE,TUNDRA,MOUNTAIN,SNOW,FRESHWATER,NIL} Biome;
	typedef enum ObjectType{PLANT,GROUND,MONSTER,MEAT,EYECANDY,SHELTER,TERRITORY,BUILDING,UNIT} ObjectType;
	typedef enum BuildingType{NONE,ROAD,RES,FARM,NPC_HUT,COM,IND,CAMP,EDU} BuildingType;
	typedef enum UnitType{NONE_UNIT,MILITIA,TRIBENPC} UnitType;

	class GameObject {
		public:
			GameObject(int ix, int iy,int w, int h);
			virtual ~GameObject();
			virtual void tick()=0;
			virtual void render()=0;
			virtual void nextGeneration()=0;
			virtual void nextMove()=0;
			virtual void nextEat()=0;
			virtual Rectangle getBounds()=0;
			void setStretchSize();
			int getStretchSize();
			int getX();
			int getY();
			int getWidth();
			int getHeight();
			ObjectType getName();
			void unClick();
			bool isClicked();
			bool isBuilding();
			bool isUnit();

			BuildingType getBuilding();
			UnitType getUnit();

			static void setInternalClock(int clock);
			static void setGroundArray(GameObject* groundArray[60][60]);
			static vector<GameObject*> objects;
			static vector<GameObject*> monsters;
			static vector<GameObject*> shelters;
			static GameObject* groundArray[60][60];
			static int generation;
			static Font font;
			static void setMousePos(int x, int y);
			static Vector2 getMousePos();
			static void resetEvolution();
			static Fog fog[60][60];
			static int getRemovedFog();
			static vector<vector<vector<GameObject*>>> cluster;

		private:
			int stretchSize = 1;
		protected:
			static int evolutionOccuredYet;
			static int evolutionOccuredYetWater;
			static int evolutionOccuredYetMonst;
			static int evolutionOccuredYetMonstWater;
			int x = 0;
			int y = 0;
			int width = 0;
			int height = 0;
			ObjectType name;
			BuildingType buildingType = NONE;
			UnitType unitType = NONE_UNIT;
			void setX(int x);
			void setY(int y);
			void setWidth(int w);
			void setHeight(int h);
			static int internalClock;
			int mouseX;
			int mouseY;
			bool clickedHere;
			bool building = false;
			bool unit = false;
			Color darken(Color original, int amt);

			//@return the pointer of the object at location [i] in the vector
			GameObject* getObject(uint i)
			{
				vector<GameObject*> tempVect;
				tempVect = objects;
				return tempVect[i];
			}
			static int worldMouseX;
			static int worldMouseY;
			bool clicked;
			bool getClicking();



	};

#include "../species/Species.h"
#endif /* OBJECTS_GAMEOBJECT_H_ */
