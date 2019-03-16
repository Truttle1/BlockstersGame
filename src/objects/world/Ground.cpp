/*
 * Ground.cpp
 *
 *  Created on: Nov 23, 2018
 *      Author: truttle1
 */

#include "Ground.h"
typedef GameObject super;
const int LENGTH_OF_CREATE = 18;
Ground::Ground(int ix, int iy,int w, int h, bool newGame) : super(ix,iy,w,h)
{
	name = "Ground";
	if(rand()%300 < 1)
	{
		this->biome = DIRT;
	}
	else if(rand()%200 < 1)
	{
		this->biome = WATER;
	}
	else if(rand()%250 < 1)
	{
		this->biome = DESERT;
	}
	else if(rand()%300 < 1)
	{
		this->biome = MOUNTAIN;
	}
	else
	{
		this->biome = FRESHWATER;
	}

	if(newGame)
	{
		createTime = 0;
	}
	else
	{
		createTime = 30;
	}
}
void Ground::loadFile(Biome iBiome)
{
	biome = iBiome;
}
void Ground::setupWaterGraphics(Texture2D* img0,Texture2D* img1)
{
	waterImage[0] = img0;
	waterImage[1] = img1;
}
void Ground::setupFreshWaterGraphics(Texture2D* fwImg0,Texture2D* fwImg1)
{
	freshwaterImage[0] = fwImg0;
	freshwaterImage[1] = fwImg1;
}
void Ground::tick()
{
	if(internalClock<LENGTH_OF_CREATE && (biome == WATER || biome == FRESHWATER))
	{
		createTime++;
		createNewLand();
	}
	else if(internalClock == LENGTH_OF_CREATE)
	{
		biome = determineBiome();
		createTime++;
	}
	if(biome == DIRT || biome == DESERT)
	{
		createTime = LENGTH_OF_CREATE;
	}
	if(biome == FRESHWATER && GameObject::generation < 2)
	{
		if(rand()%100<10 && getSurroundingType(WATER)>=1)
		{
			biome = WATER;
		}
	}
	if(biome == WATER || biome == FRESHWATER)
	{
		if(this->internalClock%60==30)
		{
			this->animationFrame = 1;
		}
		if(this->internalClock%60==0)
		{
			this->animationFrame = 0;
		}
	}
}
void Ground::render()
{
	if(biome == WATER)
	{
		DrawTexture(*waterImage[animationFrame],x,y,WHITE);
	}
	if(biome == FRESHWATER)
	{
		DrawTexture(*freshwaterImage[animationFrame],x,y,WHITE);
	}
	if(biome == DIRT)
	{
		DrawTexture(*dirtImage,x,y,WHITE);
	}
	if(biome == BEACH)
	{
		DrawTexture(*beachImage,x,y,WHITE);
	}
	if(biome == TUNDRA)
	{
		DrawTexture(*tundraImage,x,y,WHITE);
	}
	if(biome == DESERT)
	{
		DrawTexture(*desertImage,x,y,WHITE);
	}
	if(biome == MOUNTAIN)
	{
		DrawTexture(*mountainImage,x,y,WHITE);
	}
	if(biome == SNOW)
	{
		DrawTexture(*snowImage,x,y,WHITE);
	}
}
Ground::~Ground() {
}
bool Ground::isSeen()
{
	return seen;
}
void Ground::createNewLand()
{
	int surroundingDirt = getSurroundingType(DIRT);
	int surroundingDesert = getSurroundingType(DESERT);
	int surroundingMtn = getSurroundingType(MOUNTAIN);
	if(rand()%120<surroundingDirt*25)
	{
		biome = DIRT;
	}
	if(rand()%420<surroundingDesert*25)
	{
		biome = DESERT;
	}
	if(rand()%420<surroundingMtn*25)
	{
		biome = MOUNTAIN;
	}
}
Biome Ground::getBiome()
{
	return biome;
}
Biome Ground::determineBiome()
{
	if(biome == DIRT)
	{
		if(y<128 || y>832)
		{
			return TUNDRA;
		}
		if(rand()%3<getSurroundingType(DESERT))
		{
			return DESERT;
		}
		if(rand()%3<getSurroundingType(MOUNTAIN))
		{
			return MOUNTAIN;
		}
	}
	if(biome == MOUNTAIN)
	{
		if(rand()%3<getSurroundingType(MOUNTAIN)-3)
		{
			return SNOW;
		}
	}
	if(biome == DESERT)
	{
		if(y<128 || y>832)
		{
			return TUNDRA;
		}
	}
	if(biome == WATER || biome == FRESHWATER || biome == DESERT || biome == MOUNTAIN)
	{
		return biome;
	}
	else
	{
		int surroundingWater = getSurroundingType(WATER,FRESHWATER);
		if(surroundingWater != 0)
		{
			return BEACH;
		}
	}
	return DIRT;
}
int Ground::getSurroundingType(Biome type)
{
	return getSurroundingType(type,type);
}
int Ground::getSurroundingTypeOld(Biome type, Biome type2)
{
	int surrounding = 0;
	vector<GameObject*> obj = objects;
		for(uint i=0;i<obj.size();i++)
		{
			GameObject* tempObject;
			tempObject = obj[i];
			if(tempObject->getName() == "Ground" && tempObject != this)
			{
				Ground* tempGround = static_cast<Ground*>(tempObject);
				if(tempGround->getBiome() == type||tempGround->getBiome() == type2)
				{
					if(tempObject->getX() == this->getX()-16 && tempObject->getY() == this->getY())
					{
						surrounding++;
					}
					if(tempObject->getX() == this->getX()+16 && tempObject->getY() == this->getY())
					{
						surrounding++;
					}
					if(tempObject->getX() == this->getX() && tempObject->getY() == this->getY()-16)
					{
						surrounding++;
					}

					if(tempObject->getX() == this->getX() && tempObject->getY() == this->getY()+16)
					{
						surrounding++;
					}
				}
			}
		}
		return surrounding;
}
int Ground::getSurroundingType(Biome type,Biome type2)
{
	int surrounding = 0;

	if(groundArray[59][59] != NULL)
	{
		Ground* tempGround;

		if(x != 0)
		{
			tempGround = static_cast<Ground*>(groundArray[(x/16)-1][y/16]);
			if(tempGround != NULL)
			{
				if(tempGround->biome == type || tempGround->biome == type2)
				{
					surrounding++;
				}
			}
		}
		if(y != 0)
		{
			tempGround = static_cast<Ground*>(groundArray[(x/16)][(y/16)-1]);
			if(tempGround != NULL)
			{
				if(tempGround->biome == type || tempGround->biome == type2)
				{
					surrounding++;
				}
			}
		}
		if(x/16 != 59)
		{
			tempGround = static_cast<Ground*>(groundArray[(x/16)+1][y/16]);
			if(tempGround != NULL)
			{
				if(tempGround->biome == type || tempGround->biome == type2)
				{
					surrounding++;
				}
			}
		}
		if(y/16 != 59)
		{
			tempGround = static_cast<Ground*>(groundArray[(x/16)][(y/16)+1]);
			if(tempGround != NULL)
			{
				if(tempGround->biome == type || tempGround->biome == type2)
				{
					surrounding++;
				}
			}
		}
	}
	return surrounding;
}
void Ground::setupLandGraphics(Texture2D* dirt, Texture2D* beach,Texture2D* tundra,Texture2D* desert,Texture2D* mountain,Texture2D* snow)
{
	this->beachImage = beach;
	this->dirtImage = dirt;
	this->tundraImage = tundra;
	this->desertImage = desert;
	this->mountainImage = mountain;
	this->snowImage = snow;
}
void Ground::nextGeneration()
{
	if(GameObject::generation == -14)
	{
		for(unsigned int i=0; i<10;i++)
		{
			if(rand()%100<5)
			{

				Plant* p = new Plant(x,y,i);
				GameObject::objects.push_back(p);
			}
		}
	}
	/*
	if(rand()%offset < 2)
	{
		if(biome == WATER || biome == FRESHWATER)
		{
			if(getSurroundingType(DESERT)>1 && rand()%offset<3)
			{
				this->biome = DESERT;
			}
			else if(getSurroundingType(MOUNTAIN)>1 && rand()%offset<3)
			{
				this->biome = MOUNTAIN;
			}
			else if(getSurroundingType(BEACH)>1)
			{
				this->biome = BEACH;
			}
			else if(getSurroundingType(DIRT)>1)
			{
				this->biome = BEACH;
			}
			else if(getSurroundingType(TUNDRA)>1)
			{
				this->biome = TUNDRA;
			}
		}
		else
		{

			if(y<128 || y>832)
			{
				biome = TUNDRA;
			}
			if(getSurroundingType(DESERT)>1 && rand()%offset<7)
			{
				this->biome = DESERT;
			}
			else if(getSurroundingType(MOUNTAIN)>1 && rand()%offset<3)
			{
				this->biome = MOUNTAIN;
			}
			else if(getSurroundingType(DIRT)>1 && rand()%offset<3)
			{
				this->biome = DIRT;
			}
			else if(biome == DIRT && getSurroundingType(FRESHWATER,WATER)>1)
			{
				this->biome = BEACH;
			}
			else if(getSurroundingType(FRESHWATER,WATER)>1 && rand()%offset*10<3)
			{
				this->biome = FRESHWATER;
			}
		}

	}*/
}
void Ground::nextMove()
{

}
void Ground::nextEat()
{

}
Rectangle Ground::getBounds()
{
	Rectangle r;
	r.x = x;
	r.y = y;
	r.height = 16;
	r.width = 16;
	return r;
}

