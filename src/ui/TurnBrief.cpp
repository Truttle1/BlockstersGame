/*
 * TurnBrief.cpp
 *
 *  Created on: Apr 8, 2019
 *      Author: truttle1
 */

#include "TurnBrief.h"
TurnBrief::TurnBrief()
{
}
void TurnBrief::init(Font iFont)
{
	font = iFont;

}

TurnBrief::~TurnBrief() {
	// TODO Auto-generated destructor stub
}


bool TurnBrief::getClicking(int x, int y, int width, int height)
{

	bool clicking = false;
	if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
	{
		int mx = GetMouseX();
		int my = GetMouseY();
		clicking = (mx >= x && my >= y && mx <= x+width && my <= y+height);
	}
	return clicking;
}

void TurnBrief::tick()
{
	if(visible)
	{
		if(getClicking(212,324,64,32))
		{
			visible = false;
		}
	}
}

void TurnBrief::render()
{
	if(visible)
	{
		DrawRectangle(32,80,448,320,{0,128,128,255});
		DrawRectangle(16,64,448,320,{255,255,255,255});
		DrawTextEx(font,"Turnly Brief",{32.0f,72.0f},48.0f,0.0f,BLACK);
		int offsetX = 20;
		int offsetY = 16;
		int offsetY2 = 0;
		Texture2D tex;


		DrawRectangle(212,324,64,32,BLACK);
		DrawTextEx(font,"OK",{232.0f,326.0f},24.0f,0.0f,WHITE);

		DrawRectangle(232,122,4,190,RED);
		//PLAYER
		DrawTextureEx(Species::monsterSpecies[oldest].image,{32,152},0.0,2,WHITE);
		DrawTextureEx(arrow,{128-offsetX,152-offsetY},0.0,2,WHITE);
		DrawTextEx(font,to_string(Species::monsterSpecies[oldest].oldPopulation).c_str(),{72.0f,152.0f},24.0f,0.0f,BLACK);
		DrawTextEx(font,to_string(Species::monsterSpecies[oldest].population).c_str(),{168.0f,152.0f},24.0f,0.0f,BLACK);
		if(Species::monsterSpecies[oldest].population > Species::monsterSpecies[oldest].oldPopulation)
		{
			tex = up;
		}
		else if(Species::monsterSpecies[oldest].population < Species::monsterSpecies[oldest].oldPopulation)
		{
			tex = down;
		}
		else
		{
			tex = stay;
		}
		DrawTextureEx(tex,{212,152-offsetY2},0.0,1,WHITE);

		DrawTextureEx(Species::monsterSpecies[newest].image,{32,200},0.0,2,WHITE);
		DrawTextureEx(arrow,{128-offsetX,200-offsetY},0.0,2,WHITE);
		DrawTextEx(font,to_string(Species::monsterSpecies[newest].oldPopulation).c_str(),{72.0f,200.0f},24.0f,0.0f,BLACK);
		DrawTextEx(font,to_string(Species::monsterSpecies[newest].population).c_str(),{168.0f,200.0f},24.0f,0.0f,BLACK);
		if(Species::monsterSpecies[newest].population > Species::monsterSpecies[newest].oldPopulation)
		{
			tex = up;
		}
		else if(Species::monsterSpecies[newest].population < Species::monsterSpecies[newest].oldPopulation)
		{
			tex = down;
		}
		else
		{
			tex = stay;
		}
		DrawTextureEx(tex,{212,200-offsetY2},0.0,1,WHITE);

		DrawTextureEx(Species::monsterSpecies[increase].image,{32,248},0.0,2,WHITE);
		DrawTextureEx(arrow,{128-offsetX,248-offsetY},0.0,2,WHITE);
		DrawTextEx(font,to_string(Species::monsterSpecies[increase].oldPopulation).c_str(),{72.0f,248.0f},24.0f,0.0f,BLACK);
		DrawTextEx(font,to_string(Species::monsterSpecies[increase].population).c_str(),{168.0f,248.0f},24.0f,0.0f,BLACK);
		if(Species::monsterSpecies[increase].population > Species::monsterSpecies[increase].oldPopulation)
		{
			tex = up;
		}
		else if(Species::monsterSpecies[increase].population < Species::monsterSpecies[increase].oldPopulation)
		{
			tex = down;
		}
		else
		{
			tex = stay;
		}
		DrawTextureEx(tex,{212,248-offsetY2},0.0,1,WHITE);

		DrawTextureEx(Species::monsterSpecies[decrease].image,{32,296},0.0,2,WHITE);
		DrawTextureEx(arrow,{128-offsetX,296-offsetY},0.0,2,WHITE);
		DrawTextEx(font,to_string(Species::monsterSpecies[decrease].oldPopulation).c_str(),{72.0f,296.0f},24.0f,0.0f,BLACK);
		DrawTextEx(font,to_string(Species::monsterSpecies[decrease].population).c_str(),{168.0f,296.0f},24.0f,0.0f,BLACK);
		if(Species::monsterSpecies[decrease].population > Species::monsterSpecies[decrease].oldPopulation)
		{
			tex = up;
		}
		else if(Species::monsterSpecies[decrease].population < Species::monsterSpecies[decrease].oldPopulation)
		{
			tex = down;
		}
		else
		{
			tex = stay;
		}
		DrawTextureEx(tex,{212,296-offsetY2},0.0,1,WHITE);

		int rivalOffset = 224;
		//RIVAL

		if(Species::monstersDiscovered.size() > 0)
		{
			DrawTextureEx(Species::monsterSpecies[oldestR].image,{32+rivalOffset,152},0.0,2,WHITE);
			DrawTextureEx(arrow,{128-offsetX+rivalOffset,152-offsetY},0.0,2,WHITE);
			DrawTextEx(font,to_string(Species::monsterSpecies[oldestR].oldPopulation).c_str(),{72.0f+rivalOffset,152.0f},24.0f,0.0f,BLACK);
			DrawTextEx(font,to_string(Species::monsterSpecies[oldestR].population).c_str(),{168.0f+rivalOffset,152.0f},24.0f,0.0f,BLACK);
			if(Species::monsterSpecies[oldestR].population > Species::monsterSpecies[oldestR].oldPopulation)
			{
				tex = up;
			}
			else if(Species::monsterSpecies[oldestR].population < Species::monsterSpecies[oldestR].oldPopulation)
			{
				tex = down;
			}
			else
			{
				tex = stay;
			}
			DrawTextureEx(tex,{212+rivalOffset,152-offsetY2},0.0,1,WHITE);

			DrawTextureEx(Species::monsterSpecies[newestR].image,{32+rivalOffset,200},0.0,2,WHITE);
			DrawTextureEx(arrow,{128-offsetX+rivalOffset,200-offsetY},0.0,2,WHITE);
			DrawTextEx(font,to_string(Species::monsterSpecies[newestR].oldPopulation).c_str(),{72.0f+rivalOffset,200.0f},24.0f,0.0f,BLACK);
			DrawTextEx(font,to_string(Species::monsterSpecies[newestR].population).c_str(),{168.0f+rivalOffset,200.0f},24.0f,0.0f,BLACK);
			if(Species::monsterSpecies[newestR].population > Species::monsterSpecies[newestR].oldPopulation)
			{
				tex = up;
			}
			else if(Species::monsterSpecies[newestR].population < Species::monsterSpecies[newestR].oldPopulation)
			{
				tex = down;
			}
			else
			{
				tex = stay;
			}
			DrawTextureEx(tex,{212+rivalOffset,200-offsetY2},0.0,1,WHITE);

			DrawTextureEx(Species::monsterSpecies[increaseR].image,{32+rivalOffset,248},0.0,2,WHITE);
			DrawTextureEx(arrow,{128-offsetX+rivalOffset,248-offsetY},0.0,2,WHITE);
			DrawTextEx(font,to_string(Species::monsterSpecies[increaseR].oldPopulation).c_str(),{72.0f+rivalOffset,248.0f},24.0f,0.0f,BLACK);
			DrawTextEx(font,to_string(Species::monsterSpecies[increaseR].population).c_str(),{168.0f+rivalOffset,248.0f},24.0f,0.0f,BLACK);
			if(Species::monsterSpecies[increaseR].population > Species::monsterSpecies[increaseR].oldPopulation)
			{
				tex = up;
			}
			else if(Species::monsterSpecies[increaseR].population < Species::monsterSpecies[increaseR].oldPopulation)
			{
				tex = down;
			}
			else
			{
				tex = stay;
			}
			DrawTextureEx(tex,{212+rivalOffset,248-offsetY2},0.0,1,WHITE);

			DrawTextureEx(Species::monsterSpecies[decreaseR].image,{32+rivalOffset,296},0.0,2,WHITE);
			DrawTextureEx(arrow,{128-offsetX+rivalOffset,296-offsetY},0.0,2,WHITE);
			DrawTextEx(font,to_string(Species::monsterSpecies[decreaseR].oldPopulation).c_str(),{72.0f+rivalOffset,296.0f},24.0f,0.0f,BLACK);
			DrawTextEx(font,to_string(Species::monsterSpecies[decreaseR].population).c_str(),{168.0f+rivalOffset,296.0f},24.0f,0.0f,BLACK);
			if(Species::monsterSpecies[decreaseR].population > Species::monsterSpecies[decreaseR].oldPopulation)
			{
				tex = up;
			}
			else if(Species::monsterSpecies[decreaseR].population < Species::monsterSpecies[decreaseR].oldPopulation)
			{
				tex = down;
			}
			else
			{
				tex = stay;
			}
			DrawTextureEx(tex,{212+rivalOffset,296-offsetY2},0.0,1,WHITE);
		}
	}
}


bool TurnBrief::getVisible()
{
	return visible;
}

void TurnBrief::enable()
{
	oldest = -1;
	newest = 0;
	increase = 0;
	int increaseVal = -9999;
	decrease = 0;
	int decreaseVal = 9999;
	oldestR = -1;
	newestR = 0;
	increaseR = 0;
	int increaseValR = -9999;
	decreaseR = 0;
	int decreaseValR = 9999;
	for(unsigned i = 0; i < Species::monsterSpecies.size(); i++)
	{
		if(!Species::monsterSpecies[i].enemy && Species::monsterSpecies[i].oldPopulation > 0)
		{
			if(oldest == -1)
			{
				oldest = i;
			}
			if(newest < i)
			{
				newest = i;
			}
			if(increaseVal < (Species::monsterSpecies[i].population-Species::monsterSpecies[i].oldPopulation))
			{
				increaseVal = (Species::monsterSpecies[i].population-Species::monsterSpecies[i].oldPopulation);
				increase = i;
			}
			if(decreaseVal > (Species::monsterSpecies[i].population-Species::monsterSpecies[i].oldPopulation))
			{
				decreaseVal = (Species::monsterSpecies[i].population-Species::monsterSpecies[i].oldPopulation);
				decrease = i;
			}
		}
	}

	for(unsigned i = 0; i < Species::monstersDiscovered.size(); i++)
	{
		if(Species::monstersDiscovered[i] < Species::monsterSpecies.size() && Species::monsterSpecies[Species::monstersDiscovered[i]].oldPopulation > 0)
		{
			if(oldestR == -1)
			{
				oldestR = Species::monstersDiscovered[i];
			}
			if(newestR < Species::monstersDiscovered[i])
			{
				newestR = Species::monstersDiscovered[i];
			}
			if(increaseValR < (Species::monsterSpecies[Species::monstersDiscovered[i]].population-Species::monsterSpecies[Species::monstersDiscovered[i]].oldPopulation))
			{
				increaseValR = (Species::monsterSpecies[Species::monstersDiscovered[i]].population-Species::monsterSpecies[Species::monstersDiscovered[i]].oldPopulation);
				increaseR = Species::monstersDiscovered[i];
			}
			if(decreaseValR > (Species::monsterSpecies[Species::monstersDiscovered[i]].population-Species::monsterSpecies[Species::monstersDiscovered[i]].oldPopulation))
			{
				decreaseValR = (Species::monsterSpecies[Species::monstersDiscovered[i]].population-Species::monsterSpecies[Species::monstersDiscovered[i]].oldPopulation);
				decreaseR = Species::monstersDiscovered[i];
			}
		}
	}
	if(!loaded)
	{

		stay = LoadTexture("src/img/ui/stay.png");
		up = LoadTexture("src/img/ui/up.png");
		down = LoadTexture("src/img/ui/down.png");
		arrow = LoadTexture("src/img/ui/arrow.png");
		loaded = true;
	}
	visible = true;
}

void TurnBrief::disable()
{
	visible = false;
}

