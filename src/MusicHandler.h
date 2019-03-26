/*
 * MusicHandler.h
 *
 *  Created on: Mar 25, 2019
 *      Author: truttle1
 */

#ifndef MUSICHANDLER_H_
#define MUSICHANDLER_H_
#include "libraries/raylib.h"
class MusicHandler {
public:
	static Sound pirateKite;
	static Sound boyDog;
	static Sound metroCloud;
	static Sound burren;
	static Sound petRock;
	static Sound winter;
	static Sound dotWorld;
	static Sound curSong;
	static void loadMusic();
	static void handleMusic();
	static void playSong(Sound song);
	static void playFirstSong(Sound song);
};

#endif /* MUSICHANDLER_H_ */
