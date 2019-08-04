/*
 * Civilizations.cpp
 *
 *  Created on: Jun 26, 2019
 *      Author: truttle1
 */

#include "Civilizations.h"
std::vector<State> Civilizations::states;
std::vector<Tribe> Civilizations::tribes;
std::vector<Color> Civilizations::civColors;
Civilizations::Civilizations()
{
	// TODO Auto-generated constructor stub

}

Civilizations::~Civilizations()
{
	// TODO Auto-generated destructor stub
}

void Civilizations::setStateColors()
{
	civColors.push_back(RED);
	civColors.push_back(ORANGE);
	civColors.push_back(YELLOW);
	civColors.push_back(GREEN);
	civColors.push_back({0,255,255,255});
	civColors.push_back(BLUE);
}
