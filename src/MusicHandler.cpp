/*
 * MusicHandler.cpp
 *
 *  Created on: Mar 25, 2019
 *      Author: truttle1
 */

#include "MusicHandler.h"
#include <random>
Sound MusicHandler::pirateKite;
Sound MusicHandler::boyDog;
Sound MusicHandler::metroCloud;
Sound MusicHandler::burren;
Sound MusicHandler::petRock;
Sound MusicHandler::winter;
Sound MusicHandler::curSong;
Sound MusicHandler::dotWorld;
void MusicHandler::handleMusic()
{
	if(IsSoundPlaying(curSong))
	{
		if(rand()%200000 <= 2)
		{
			StopSound(curSong);
		}
	}
	else
	{
		if(rand()%200 < 10)
		{
			playSong(pirateKite);
		}
		if(rand()%200 < 10)
		{
			playSong(boyDog);
		}
		if(rand()%200 < 10)
		{
			playSong(metroCloud);
		}
		if(rand()%200 < 10)
		{
			playSong(burren);
		}
		if(rand()%200 < 10)
		{
			playSong(petRock);
		}
		/*
		if(rand()%200 < 10)
		{
			playSong(winter);
		}*/
		if(rand()%200 < 10)
		{
			playSong(dotWorld);
		}
	}
}
void MusicHandler::loadMusic()
{
	pirateKite = LoadSound("src/sound/PirateKite.wav");
	boyDog = LoadSound("src/sound/BoyAndHisDog.wav");
	metroCloud = LoadSound("src/sound/MetroCloud.wav");
	burren = LoadSound("src/sound/TheBurren.wav");
	petRock = LoadSound("src/sound/PetRock.wav");
	winter = LoadSound("src/sound/Winter.wav");
	dotWorld = LoadSound("src/sound/DotWorld.wav");
}

void MusicHandler::playSong(Sound song)
{
	StopSound(curSong);
	PlaySound(song);
	curSong = song;
}
void MusicHandler::playFirstSong(Sound song)
{
	PlaySound(song);
	curSong = song;
}
