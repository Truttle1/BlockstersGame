/*
 * Object.cpp
 *
 *  Created on: Jan 2, 2019
 *      Author: truttle1
 */

#include "Monster.h"
#include <algorithm>
Monster::Monster(int ix, int iy, int sp, bool e) : GameObject(ix,iy,8,8)
{
	alive = true;
	name = "Monster";
	species = sp;
	arbitraryPopNumber = (rand()%10)+1;
	Species::monsterSpecies[species].population += arbitraryPopNumber;
	age = 0;
	enemy = e;
	targetX = -1;
	targetY = -1;
	movementStage = 0;
	moved = false;
	hp = Species::monsterSpecies[species].size*2;
	monster = Species::monsterSpecies[this->species];
	hasEaten = false;
	mouseX = 0;
	mouseY = 0;
	flashTime = 0;
	clickedHere = false;
}
void Monster::loadFromFile(int iAge, int iHp, int population)
{
	age = iAge;
	hp = iHp;
	Species::monsterSpecies[species].population -= arbitraryPopNumber;
	arbitraryPopNumber = population;
	Species::monsterSpecies[species].population += arbitraryPopNumber;
	targetX = -1;
	targetY = -1;

}
Monster::~Monster()
{

}
int Monster::getPopulation()
{
	return arbitraryPopNumber;
}
void Monster::tick()
{
	getClicking();
	if(clickedHere && !UI::isOpen())
	{
		string rivalStatus = " ";
		if(enemy)
		{
			rivalStatus = "Rival Monster";

		}
		else
		{
			rivalStatus = "Player Monster";
		}
		if(poison == 0)
		{
			GameWindow::showUpperText(monster.name + "    " + rivalStatus + "    Group of " + to_string(arbitraryPopNumber) +
								"\nHP: " + to_string(hp) + "    Movements Left: " + to_string(monster.speed - movementStage)+ "    Age: " + to_string(age));
		}
		else
		{
			GameWindow::showUpperText(monster.name + "    " + rivalStatus + "    Group of " + to_string(arbitraryPopNumber) +
								"\nHP: " + to_string(hp) + "    Movements Left: " + to_string(monster.speed - movementStage)+ "    POISON: -" + to_string(poison) + " HP/Gen");
		}
	}
	if(clickedHere)
	{
		flashTime++;
		if(flashTime>30)
		{
			flashTime = 0;
		}
	}
	else
	{
		flashTime = 0;
	}
	if(clickedHere && !enemy)
	{
		removeFog();
		if(monster.carnivore)
		{
			for(unsigned int i=3600; i<GameObject::objects.size();i++)
			{
				if(GameObject::objects[i] && GameObject::objects[i]->getName() == "Meat")
				{
					Meat* m = static_cast<Meat*>(GameObject::objects[i]);
					if(m && monster.carnivore && CheckCollisionRecs(m->getBounds(),this->getBounds()) && m->getSpecies() != species)
					{
						hp += m->eat();
					}
				}
			}
		}
		if(IsKeyPressed(KEY_DELETE))
		{
			kill();
		}
		if(targetX == -1 && targetY == -1 && movementStage < monster.speed && moved)
		{
			if(IsKeyPressed(KEY_W))
			{
				targetX = x;
				targetY = y-8;
				moved = false;
				movementStage++;
			}
			if(IsKeyPressed(KEY_A))
			{
				targetX = x-8;
				targetY = y;
				moved = false;
				movementStage++;
			}
			if(IsKeyPressed(KEY_S))
			{
				targetX = x;
				targetY = y+8;
				moved = false;
				movementStage++;
			}
			if(IsKeyPressed(KEY_D))
			{
				targetX = x+8;
				targetY = y;
				moved = false;
				movementStage++;
			}

		}
		if(!moved && targetX != -1 && targetY != -1)
		{
			if(x < targetX)
			{
				x++;
			}
			if(x > targetX)
			{
				x--;
			}
			if(y < targetY)
			{
				y++;
			}
			if(y > targetY)
			{
				y--;
			}
			if(x == targetX && y == targetY)
			{
				moved = true;
				targetX = -1;
				targetY = -1;
			}

		}
	}
}

bool Monster::getClicking()
{

	bool clicking = false;
	if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
	{
		int mx = GetMouseX() / GameWindow::getCamera()->zoom - GameWindow::getCamera()->offset.x / GameWindow::getCamera()->zoom;
		int my = GetMouseY() / GameWindow::getCamera()->zoom - GameWindow::getCamera()->offset.y / GameWindow::getCamera()->zoom ;
		mouseX = mx;
		mouseY = my;
		clicking = (mx >= x && my >= y && mx <= x+width && my <= y+height);
		if(clicking)
		{
			clickedHere = true;
		}
		else
		{
			clickedHere = false;
		}
	}
	return clicking;
}

void Monster::render()
{
	if(flashTime < 15 && clickedHere)
	{
		DrawRectangle(x,y,8,8,GREEN);
	}
	else if(enemy)
	{
		if(poison > 0)
		{
			DrawRectangle(x,y,8,8,{128,64,128,255});
		}
		else
		{
			DrawRectangle(x,y,8,8,{192,64,0,255});
		}
	}
	else
	{
		if(poison > 0)
		{
			DrawRectangle(x,y,8,8,{200,0,200,255});
		}
	}
	if(alive)
	{
		DrawTexture(Species::monsterSpecies[this->species].image,x,y,WHITE);
	}

	int normX = x/16;
	int normY = y/16;
	if(normX < 60 && normY < 60 && normX > -1 && normY > -1 && !GameObject::fog[normX][normY].isVisible())
	{
		if(enemy)
		{
			if(!(std::find(Species::monstersDiscovered.begin(),Species::monstersDiscovered.end(),species) != Species::monstersDiscovered.end()))
			{
				Species::monstersDiscovered.push_back(species);
			}
		}
		else
		{

			if(!(std::find(Species::plMonstersDiscovered.begin(),Species::plMonstersDiscovered.end(),species) != Species::plMonstersDiscovered.end()))
			{
				Species::plMonstersDiscovered.push_back(species);
			}
		}
	}

}
void Monster::nextGeneration()
{
	movementStage = 0;
	hasEaten = false;
	bool onLand = true;
	targetX = -1;
	targetY = -1;
	x = (x/8)*8;
	y = (y/8)*8;
	moved = true;

	for(uint i = 0; i<GameObject::objects.size();i++)
	{
		GameObject* g = GameObject::objects[i];
		if(g->getName().compare("Ground")==0)
		{
			Ground* g2 = dynamic_cast<Ground*>(g);
			if(CheckCollisionRecs(g2->getBounds(),this->getBounds()))
			{
				if(g2->getBiome() == WATER || g2->getBiome() == FRESHWATER)
				{
					onLand = false;
				}
			}
		}
	}
	if(!enemy)
	{
		removeFog();
	}
	if(!hasEaten)
	{
		if(!monster.carnivore)
		{
			for(unsigned int i = 0; i < GameObject::objects.size(); i++)
			{
				if(GameObject::objects[i]->getName() == "Plant")
				{
					int px = GameObject::objects[i]->getX();
					int py = GameObject::objects[i]->getY();
					if(std::abs(px-x) <= 16 && std::abs(py-y) <= 16)
					{
						Plant* plant = static_cast<Plant*>(GameObject::objects[i]);
						eatPlant(plant);
						if(hasEaten)
						{
							break;
						}
					}
				}
			}
		}
	}


	int repValue = 0;
	//Reproduce
	if(hp >= monster.size && age >= 2 && getNeighborhood()<=monster.maxNew && getNeighborhood()>=monster.minNew && repValue<15)
	{
		int newX = ((rand()%5)*8)-16;
		int newY = ((rand()%5)*8)-16;
		Monster* p = new Monster(this->getX()+newX,this->getY()+newY,this->getSpecies(),enemy);
		GameObject::objects.push_back(p);
		hp -= monster.size/2;
		if(rand()%2000<10 && monster.enemy && alive && !evolutionOccuredYetMonst)
		{
			evolve();
			evolutionOccuredYetMonst = true;
		}
	}
	if(x<0 || x>=960)
	{
		this->kill();
	}
	if(y<0 || y>=960)
	{
		this->kill();
	}
	if(!monster.land && onLand)
	{
		this->kill();
		//printf("LAND IS BAD\nSPECIES %d HAS LAND VALUE OF %d\n",this->species,Species::plantSpecies[this->species].land);
	}
	else if(monster.land && !onLand)
	{
		this->kill();
		//printf("WATER IS BAD\nSPECIES %d HAS LAND VALUE OF %d\n",this->species,Species::plantSpecies[this->species].land);
	}
	//at the same location die.
	killSameLocation();
	//die when they live longer than their lifespan.
	if(age>monster.lifespan)
	{
		this->kill();
	}
	//Death by overcrowding
	if(getNeighborhood()>monster.maxDeath && rand()%100<75)
	{
		this->kill();
	}
	//Death by lonliness
	if(getNeighborhood()<monster.minDeath && rand()%100<33)
	{
		this->kill();
	}
	attackMonsters();
	//Age goes up.
	age++;

	hp -= monster.metabolism;
	if(hp <= 0)
	{
		kill();
	}

	targetX = -1;
	targetY = -1;
}

int Monster::getNeighborhood()
{
	int c = 0;
	for(uint i = 0; i<GameObject::objects.size();i++)
	{
		GameObject* temp = GameObject::objects[i];
		int distX = std::abs((this->getX())-(temp->getX()));
		int distY = std::abs((this->getY())-(temp->getY()));
		if(distX <= 8 && distY <= 8 && temp != this && temp->getName() == "Monster")
		{
			//printf("%d, %d :: %d, %d, :: %d, %d\n",x,y,temp->getX(),temp->getY(),distX,distY);
			c++; //GOT EM
		}
	}
	return c;
}
Rectangle Monster::getBounds()
{
	Rectangle r;
	r.x = x+1;
	r.y = y+1;
	r.height = 6;
	r.width = 6;
	return r;
}
void Monster::resetMovement()
{
	moved = false;
}
void Monster::nextMove()
{
	hasEaten = false;
	if(!enemy)
	{
		removeFog();
	}
	if(!moved && movementStage < Species::monsterSpecies[species].speed)
	{
		int spd = 1;
		selectRandomTarget();
		if(!enemy)
		{
			removeFog();
		}

		if(enemy)
		{
			spd = ((monster.speed/2)/4)*4;
			if(spd < 1)
			{
				spd = 1;
			}
			if(spd > 8)
			{
				spd = 8;
			}
		}
		if(targetX > x)
		{
			x+=spd;
		}
		else if(targetX < x)
		{
			x-=spd;
		}
		if(targetY > y)
		{
			y+=spd;
		}
		else if(targetY < y)
		{
			y-=spd;
		}
		if(x == targetX && y == targetY)
		{
			movementStage++;
			targetX = -1;
			targetY = -1;
		}
	}
	else
	{
		moved = true;
		targetX = -1;
		targetY = -1;
	}
	if(monster.carnivore)
	{
		cout << "CARNIVORE" << endl;
		for(unsigned int i=3600; i<GameObject::objects.size();i++)
		{
			if(GameObject::objects[i] && GameObject::objects[i]->getName() == "Meat")
			{
				Meat* m = static_cast<Meat*>(GameObject::objects[i]);
				if(m && monster.carnivore && CheckCollisionRecs(m->getBounds(),this->getBounds()) && m->getSpecies() != species)
				{
					hp += m->eat();
				}
			}
		}
	}
	hp -= poison;
	poison -= monster.size;
	if(poison < 0)
	{
		poison = 0;
	}
}
void Monster::nextEat()
{

}
bool Monster::getAlive()
{
	return alive;
}
int Monster::getSpecies()
{
	return species;
}
void Monster::kill()
{
	if(alive)
	{
		alive = false;
		Species::monsterSpecies[species].population -= arbitraryPopNumber;
	}
}
void Monster::killSameLocation()
{
}
void Monster::removeFog()
{
	int normX = x/16;
	int normY = y/16;
	GameObject::fog[normX][normY].disable();
}
bool Monster::isMoving()
{
	return !moved;
}
void Monster::selectRandomTarget()
{
	if(targetX == -1)
	{
		targetX = x;
		targetX += (-1+(rand()%3))*8;
	}
	if(targetY == -1)
	{
		targetY = y;
		targetY += (-1+(rand()%3))*8;
	}
}
void Monster::eatPlant(Plant* p)
{
	PlantSpecies plant = Species::plantSpecies[p->getSpecies()];
	if(plant.size <= monster.size+1 && plant.toxicity <= monster.size)
	{
		if(plant.size <= monster.groupSize/8 * (monster.strength+1))
		{
			hp += p->getEaten(monster.metabolism);
			if(hp>monster.metabolism)
			{
				hasEaten = true;
			}
		}
	}
	else if(plant.toxicity > monster.size)
	{
		poison += (plant.toxicity-monster.size);
	}
}

void Monster::evolve()
{
	printf("MONSTER EVOLVE!\n");
	int minNew = monster.minNew;
	int maxNew = monster.maxNew;
	int minDeath = monster.minDeath;
	int maxDeath = monster.maxDeath;
	int metabolism = monster.metabolism;
	int speed = monster.speed;

	int resil = monster.resil;
	int strength = monster.strength;

	int size = monster.size;
	int toxicity = monster.toxicity;
	int groupSize = monster.groupSize;
	int lifespan = monster.lifespan;
	int agression = monster.agression;
	bool carnivore = monster.carnivore;

	if(rand()%100<30)
	{
		carnivore = !carnivore;
	}

	if(rand()%100<20)
	{
		minNew--;
		maxNew++;
		lifespan--;
	}
	else if(maxNew-minNew > 1 && rand()%100<20)
	{
		minNew++;
		maxNew--;
		lifespan+=2;
	}
	if(rand()%100<40)
	{
		minDeath--;
		maxDeath++;
		lifespan--;
	}
	else if(maxDeath-minDeath > 1 && rand()%100<40)
	{
		minDeath++;
		maxDeath--;
		lifespan+=2;
	}

	if(rand()%100<40)
	{
		toxicity+=2;
		lifespan--;
	}
	else if(toxicity > 0 && rand()%100<40)
	{
		toxicity--;
		lifespan+=2;
	}
	if(rand()%100<40)
	{
		size+=2;
		lifespan++;
		toxicity--;
	}
	else if(size > 0 && rand()%100<40)
	{
		size--;
		toxicity+=2;
	}
	else if(rand()%100<80)
	{
		size++;
	}

	if(rand()%100<40)
	{
		metabolism++;
		speed += 2;
	}
	else if(rand()%100<40)
	{
		metabolism-=2;
		speed--;
	}

	if(rand()%100<40)
	{
		strength += 2;
		resil--;
	}
	else if(rand()%100<40)
	{
		resil += 2;
		strength--;
	}

	if(minNew<0)
	{
		minNew = 0;
	}
	if(minDeath<0)
	{
		minDeath = 0;
	}
	if(lifespan<1)
	{
		lifespan = 1;
	}
	if(metabolism < 1)
	{
		metabolism = 1;
	}
	if(speed < 1)
	{
		speed = 1;
	}
	if(strength < 1)
	{
		strength = 1;
	}
	if(resil < 1)
	{
		resil = 1;
	}
	if(rand()%100<70)
	{
		agression++;
	}
	else if(rand()%100<40)
	{
		agression--;
	}
	if(carnivore && agression < 7)
	{
		agression = 7;
	}
	if(agression < 0)
	{
		agression = 0;
	}
	if(agression > 10)
	{
		agression = 10;
	}
	MonsterSpecies newSp = MonsterSpecies();
	newSp.land = monster.land;
	newSp.toxicity = toxicity;
	newSp.size = size;
	newSp.lifespan = lifespan;
	newSp.groupSize = groupSize;
	newSp.minNew = minNew;
	newSp.maxNew = maxNew;
	newSp.minDeath = minDeath;
	newSp.maxDeath = maxDeath;

	newSp.resil = resil;
	newSp.strength = strength;
	newSp.speed = speed;
	newSp.metabolism = metabolism;
	newSp.agression = agression;
	newSp.carnivore = carnivore;


	newSp.image = monster.image;
	newSp.name = Species::generateName();
	newSp.bodyColor = monster.bodyColor;
	newSp.eyeColor = monster.eyeColor;
	newSp.highlightColor = monster.highlightColor;
	newSp.enemy = true;
	bool replacedImage = false;
	replacedImage = true;
	if(newSp.size < 3)
	{

		if(rand()%5<=2)
		{
			newSp.image = MonsterImg::miniscule0;
		}
		else if(rand()%5<=2)
		{
			newSp.image = MonsterImg::miniscule1;
		}
		else
		{
			newSp.image = MonsterImg::miniscule2;
		}
	}
	else if(newSp.size < 6)
	{

		if(rand()%5<=2)
		{
			newSp.image = MonsterImg::small0;
		}
		else
		{
			newSp.image = MonsterImg::small1;
		}
	}
	else
	{

		if(rand()%5<=2)
		{
			newSp.image = MonsterImg::basic0;
		}
		else if(rand()%5<=2)
		{
			newSp.image = MonsterImg::basic1;
		}
		else
		{
			newSp.image = MonsterImg::basic2;
		}
	}
	if(rand()%100<20)
	{
		int r = rand()%ObjectColors::monsterColorsEyes.size();
		newSp.eyeColor = ObjectColors::monsterColorsEyes[r];
	}
	if(rand()%100<80)
	{
		int h = rand()%ObjectColors::monsterColorsHighlight.size();
		newSp.highlightColor = ObjectColors::monsterColorsHighlight[h];
	}
	if(replacedImage)
	{
		cout << "REPLACING IMAGE IN MONSTER" << endl;
		int r = rand()%ObjectColors::monsterColorsEyes.size();
		newSp.eyeColor = ObjectColors::monsterColorsEyes[r];
		int h = rand()%ObjectColors::monsterColorsHighlight.size();
		newSp.highlightColor = ObjectColors::monsterColorsHighlight[h];
		newSp.image = Species::replaceColorsToImage(&newSp.image,ObjectColors::PLANT_GREEN,newSp.bodyColor);
		newSp.image = Species::replaceColorsToImage(&newSp.image,ObjectColors::ROSE_RED,newSp.highlightColor);
		newSp.image = Species::replaceColorsToImage(&newSp.image,ObjectColors::DARK_BLACK,newSp.eyeColor);

		newSp.image = Species::replaceColorsToImage(&newSp.image,monster.highlightColor,newSp.highlightColor);
		newSp.image = Species::replaceColorsToImage(&newSp.image,monster.eyeColor,newSp.eyeColor);
	}
	else
	{
	}
	Species::monsterSpecies.push_back(newSp);
	int newX = ((rand()%5)*8)-16;
	int newY = ((rand()%5)*8)-16;
	Monster* p = new Monster(this->getX()+newX,this->getY()+newY,Species::monsterSpecies.size()-1,true);
	GameObject::objects.push_back(p);
	int r = rand()%5;
	for(int i=0; i<(r)+1;i++)
	{
		newX = ((rand()%6)*8)-32;
		newY = ((rand()%6)*8)-32;
		Monster* p = new Monster(this->getX()+newX,this->getY()+newY,Species::monsterSpecies.size()-1,true);
		Monster* p1 = new Monster(this->getX()+newX,this->getY()+newY+8,Species::monsterSpecies.size()-1,true);
		GameObject::objects.push_back(p);
		GameObject::objects.push_back(p1);
	}
}
void Monster::attackMonsters()
{
	Monster* m;
	for(unsigned int i=0; i < GameObject::objects.size(); i++)
	{
		if(GameObject::objects[i] && GameObject::objects[i]->getName() == "Monster")
		{
			if(sqrt(pow(GameObject::objects[i]->getX()-x,2)+pow(GameObject::objects[i]->getY()-y,2)) <= 12)
			{
				bool ok = true;
				m = static_cast<Monster*>(GameObject::objects[i]);
				if(m->getSpecies() == species)
				{
					ok = false;
				}
				if(rand()%10 >= monster.agression)
				{
					ok = false;
				}
				if(m->getAge() < 2 || age < 1)
				{
					ok = false;
				}
				if(!enemy && !m->isEnemy())
				{
					ok = false;
				}
				if(ok)
				{
					int poisoned = 0;
					MonsterSpecies opponent = Species::monsterSpecies[m->getSpecies()];
					if(opponent.toxicity > monster.size)
					{
						setPoison(opponent.toxicity - monster.size);
						poisoned = 1;
					}

					if(opponent.size < monster.toxicity)
					{
						m->setPoison(monster.toxicity - opponent.size);
						poisoned = 2;
					}

					if(monster.strength >= Species::monsterSpecies[m->getSpecies()].resil && m->getAge())
					{
						if(!isEnemy())
						{
							EyeCandy* ec = new EyeCandy(m->getX(),m->getY(),0);
							objects.push_back(new Meat(m->getX(),m->getY(),Species::monsterSpecies[m->getSpecies()].size+1,m->getSpecies()));
							objects.push_back(ec);
						}
						else
						{
							EyeCandy* ec = new EyeCandy(m->getX(),m->getY(),2);
							objects.push_back(new Meat(m->getX(),m->getY(),Species::monsterSpecies[m->getSpecies()].size+1,m->getSpecies()));
							objects.push_back(ec);
						}
						m->kill();
					}
					else
					{
						if(poisoned == 1)
						{
							EyeCandy* ec = new EyeCandy(getX(),getY(),1);
						}
						else if(poisoned == 2)
						{
							EyeCandy* ec = new EyeCandy(m->getX(),m->getY(),1);
						}
					}
					/*
					else if(monster.resil <= Species::monsterSpecies[m->getSpecies()].strength)
					{
						EyeCandy* ec = new EyeCandy(getX(),getY(),1);
						objects.push_back(new Meat(getX(),getY(),Species::monsterSpecies[getSpecies()].size+1,getSpecies()));
						objects.push_back(ec);
						kill();
					}*/
				}
			}
		}
	}
}
bool Monster::isEnemy()
{
	return enemy;
}

int Monster::getAge()
{
	return age;
}

int Monster::getHP()
{
	return hp;
}

void Monster::setPoison(int amount)
{
	poison = amount;
}


