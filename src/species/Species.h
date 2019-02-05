/*
 * PlantSpecies.h
 *
 *  Created on: Dec 24, 2018
 *      Author: truttle1
 */
#include <vector>
#include <string>
#ifndef RAYLIB
#define RAYLIB
#include "../libraries/raylib.h"
#endif
#ifndef SPECIES_SPECIES_H_
#define SPECIES_SPECIES_H_

typedef struct PlantSpecies
{
	int minNew;
	int maxNew;
	int minDeath;
	int maxDeath;
	int lifespan;
	int toxicity;
	int size;
	int nutrients;
	int groupSize;
	bool land;
	std::string name;
	Texture2D image;
	int population;
	Color stemColor;
	Color flowerColor;
	Color highlightColor;
}PlantSpecies;
typedef struct MonsterSpecies
{
	int minNew;
	int maxNew;
	int minDeath;
	int maxDeath;
	int lifespan;
	int movement;
	int metabolism;
	int size;
	int nutrients;
	int strength;
	Texture2D image;
}MonsterSpecies;

class Species
{
	public:
		static std::vector<PlantSpecies> plantSpecies;
		static std::vector<MonsterSpecies> monsterSpecies;
		static std::vector<MonsterSpecies> enemyMonsterSpecies;

		void init();
		static std::string generateName();
		static void replaceColors(Texture* image, Color c1, Color c2);
		static Texture replaceColorsToImage(Texture* image, Color c1, Color c2);
};

#endif /* SPECIES_SPECIES_H_ */
