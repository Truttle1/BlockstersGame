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

	int evolvePass;
}PlantSpecies;
typedef struct MonsterSpecies
{
	bool land;
	bool carnivore;
	bool enemy;
	int minNew;
	int maxNew;
	int minDeath;
	int maxDeath;

	int metabolism;
	int lifespan;

	int groupSize;
	int speed;

	int size;
	int toxicity;

	int strength;
	int resil;
	int evolvePass;

	Texture2D image;
	int population;
	Color bodyColor;
	Color eyeColor;
	Color highlightColor;
	std::string name;

	int agression;
	bool behaviors[100];
	bool behaviorsUsed[100];
}MonsterSpecies;

class Species
{
	public:
		static std::vector<PlantSpecies> plantSpecies;
		static std::vector<MonsterSpecies> monsterSpecies;
		static std::vector<int> plantsDiscovered;
		static std::vector<int> plMonstersDiscovered;
		static std::vector<int> monstersDiscovered;

		void init();
		static std::string generateName();
		static void replaceColors(Texture* image, Color c1, Color c2);
		static Texture replaceColorsToImage(Texture* image, Color c1, Color c2);
};

#endif /* SPECIES_SPECIES_H_ */
