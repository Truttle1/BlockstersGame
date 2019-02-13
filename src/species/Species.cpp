/*
 * Species.cpp
 *
 *  Created on: Jan 19, 2019
 *      Author: truttle1
 */

#include "Species.h"
std::vector<PlantSpecies> Species::plantSpecies;
std::vector<MonsterSpecies> Species::monsterSpecies;


std::string Species::generateName()
{
	std::string name;
	if(rand()%26==1){name+="A";}
	else if(rand()%26==1){name+="B";}
	else if(rand()%20==1){name+="C";}
	else if(rand()%16==1){name+="D";}
	else if(rand()%26==1){name+="E";}
	else if(rand()%26==1){name+="F";}
	else if(rand()%20==1){name+="G";}
	else if(rand()%16==1){name+="H";}
	else if(rand()%26==1){name+="I";}
	else if(rand()%26==1){name+="J";}
	else if(rand()%18==1){name+="K";}
	else if(rand()%16==1){name+="L";}
	else if(rand()%20==1){name+="M";}
	else if(rand()%16==1){name+="N";}
	else if(rand()%16==1){name+="O";}
	else if(rand()%20==1){name+="P";}
	else if(rand()%26==1){name+="Qu";}
	else if(rand()%16==1){name+="R";}
	else if(rand()%16==1){name+="S";}
	else if(rand()%10==1){name+="T";}
	else if(rand()%26==1){name+="U";}
	else if(rand()%26==1){name+="V";}
	else if(rand()%26==1){name+="W";}
	else if(rand()%26==1){name+="X";}
	else if(rand()%26==1){name+="Y";}
	else{name+="Z";}

	for(int i=0; i < (rand()%2)+2; i++)
	{
		if(rand()%5==1){name += "a";}
		else if(rand()%5==1){name += "e";}
		else if(rand()%5==1){name += "i";}
		else if(rand()%5==1){name += "o";}
		else{name += "u";}

		if(rand()%40==1){name += "b";}
		else if(rand()%40==1){name += "c";}
		else if(rand()%20==1){name += "d";}
		else if(rand()%40==1){name += "f";}
		else if(rand()%30==1){name += "g";}
		else if(rand()%20==1){name += "h";}
		else if(rand()%40==1){name += "j";}
		else if(rand()%30==1){name += "k";}
		else if(rand()%20==1){name += "l";}
		else if(rand()%30==1){name += "m";}
		else if(rand()%20==1){name += "n";}
		else if(rand()%30==1){name += "p";}
		else if(rand()%30==1){name += "q";}
		else if(rand()%20==1){name += "r";}
		else if(rand()%20==1){name += "s";}
		else if(rand()%20==1){name += "t";}
		else if(rand()%40==1){name += "v";}
		else if(rand()%40==1){name += "w";}
		else if(rand()%40==1){name += "x";}
		else if(rand()%40==1){name += "y";}
		else if(rand()%40==1){name += "z";}

	}
	return name;
}

void Species::replaceColors(Texture* image, Color c1, Color c2)
{

	Color* pixels = (Color*)(GetImageData(GetTextureData(*image)));
	for(unsigned int i = 0; i<64; i++)
	{
		Color c = pixels[i];
		if(c.r == c1.r && c.g == c1.g && c.b == c1.b)
		{
			printf("%d__%d\n",c.g,i);
			pixels[i] = c2;
		}
		UpdateTexture(*image,pixels);
	}
}
Texture Species::replaceColorsToImage(Texture* image, Color c1, Color c2)
{
	Texture ret = LoadTextureFromImage(GetTextureData(*image));
	Color* pixels = (Color*)(GetImageData(GetTextureData(ret)));
	for(unsigned int i = 0; i<64; i++)
	{
		Color c = pixels[i];
		if(c.r == c1.r && c.g == c1.g && c.b == c1.b && c.a == c1.a)
		{
			printf("%d__%d\n",c.g,i);
			pixels[i] = c2;
		}
		UpdateTexture(ret,pixels);
	}
	return ret;
}
