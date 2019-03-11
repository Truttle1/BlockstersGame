/*
 * Ground.h
 *
 *  Created on: Nov 23, 2018
 *      Author: truttle1
 */
#ifndef OBJECTS_WORLD_GROUND_H_
#define OBJECTS_WORLD_GROUND_H_
#include "../GameObject.h"
#include "Plant.h"
class Ground :public GameObject{
	public:
		Ground(int ix, int iy,int w, int h,bool newGame);
		void loadFile(Biome iBiome);
		virtual ~Ground();
		void tick();
		void render();
		void nextGeneration();
		void nextEat();
		void nextMove();
		bool isSeen();
		void setupWaterGraphics(Texture2D* img0,Texture2D* img1);
		void setupLandGraphics(Texture2D* dirt,Texture2D* beach,Texture2D* tundra,Texture2D* desert,Texture2D* mountain,Texture2D* snow);
		void setupFreshWaterGraphics(Texture2D* fwImg0,Texture2D* fwImg1);
		Rectangle getBounds();
		Biome getBiome();
	private:
		Biome biome = FRESHWATER;
		Biome determineBiome();
		int getSurroundingType(Biome type);
		int getSurroundingType(Biome type,Biome type2);
		int getSurroundingTypeOld(Biome type,Biome type2);
		int createTime = 0;
		int animationFrame = 0;
		int maxAnimationFrame = 1;
		Texture2D* waterImage[2];
		Texture2D* freshwaterImage[2];
		Texture2D* beachImage = NULL;
		Texture2D* desertImage = NULL;
		Texture2D* tundraImage = NULL;
		Texture2D* jungleImage = NULL;
		Texture2D* dirtImage = NULL;
		Texture2D* grassImage = NULL;
		Texture2D* mountainImage = NULL;
		Texture2D* snowImage = NULL;
		bool seen = false;
		void createNewLand();
		int offset = (rand()%15)+1;

};

#endif /* OBJECTS_WORLD_GROUND_H_ */
