/*
 * Civilizations.h
 *
 *  Created on: Jun 26, 2019
 *      Author: truttle1
 */

#ifndef CIVILIZED_CIVILIZATIONS_H_
#define CIVILIZED_CIVILIZATIONS_H_
#include <vector>
#include "../libraries/raylib.h"
typedef struct State
{
	int type;
	int monster;
	std::vector<bool> unlocks;
	int myColor;
	bool started;
	bool technologies[100];
} State;

typedef struct Tribe
{
	int monster;
	int baseFriendship;
	int friendshipTowardsPlayer[10];
	bool gotTech;
} Tribe;
class Civilizations {
public:
	Civilizations();
	virtual ~Civilizations();
	static std::vector<State> states;
	static std::vector<Tribe> tribes;
	static std::vector<Color> civColors;
	static void setStateColors();
};

#endif /* CIVILIZED_CIVILIZATIONS_H_ */
