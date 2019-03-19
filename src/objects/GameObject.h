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
			string getName();
			void unClick();
			bool isClicked();

			static void setInternalClock(int clock);
			static void setGroundArray(GameObject* groundArray[60][60]);
			static vector<GameObject*> objects;
			static GameObject* groundArray[60][60];
			static int generation;
			static Font font;
			static void setMousePos(int x, int y);
			static Vector2 getMousePos();
			static void resetEvolution();
			static Fog fog[60][60];
		private:
			int stretchSize = 1;
		protected:
			static bool evolutionOccuredYet;
			int x = 0;
			int y = 0;
			int width = 0;
			int height = 0;
			string name;
			void setX(int x);
			void setY(int y);
			void setWidth(int w);
			void setHeight(int h);
			static int internalClock;
			int mouseX;
			int mouseY;
			bool clickedHere;
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
