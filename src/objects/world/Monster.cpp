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
	hp = Species::monsterSpecies[species].metabolism+Species::monsterSpecies[species].size;
	monster = Species::monsterSpecies[this->species];
	hasEaten = false;
	mouseX = 0;
	mouseY = 0;
	flashTime = 0;
	clickedHere = false;
	//at the same location die.
	killSameLocation();
	if(monster.metabolism < monster.size/2 && monster.enemy)
	{
		Species::monsterSpecies[species].metabolism = monster.size/2;
	}
}

//Loads monster data from a file.
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
		if(name != "Monster")
		{
			kill();
			name = "Monster";
		}
		Camera2D* cam = GameWindow::getCamera();
		int a = -GameWindow::getCamera()->offset.x / GameWindow::getCamera()->zoom;
		string rivalStatus = " ";
		if(enemy)
		{
			rivalStatus = "Rival Monster";

		}
		else
		{
			rivalStatus = "Player Monster";

			if(!GameWindow::tutorial[2] && !monster.carnivore)
			{
				GameWindow::getMessageBox()->enable("Moving Monsters/"
						"By using the W, A, S, and D keys as/"
						"directional keys, you are able to/"
						"move your monsters around the map.//"
						"This monster is an herbivore, meaning/"
						"it eats plants.//"
						"Because of that, it is recommended to/"
						"move your monsters closer to plants.");
				GameWindow::tutorial[2] = true;
				GameWindow::tutorial[1] = true;
			}
		}
		if(poison == 0 && alive)
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
						hp += m->eat()+4;
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
			int normX = (x/16)*16;
			int normY = (y/16)*16;
			int normTX = (targetX/16)*16;
			int normTY = (targetY/16)*16;

			if(!isMoving() && !GameObject::fog[normX][normY].isVisible() && !GameObject::fog[normTX][normTY].isVisible())
			{
				x = targetX;
				y = targetY;
			}

			int movement = 1;
			if(monster.speed > 3)
			{
				movement = 2;
			}
			if(monster.speed > 7)
			{
				movement = 4;
			}
			if(x < targetX)
			{
				x+=movement;
			}
			else if(x > targetX)
			{
				x-=movement;
			}
			else if(y < targetY)
			{
				y+=movement;
			}
			else if(y > targetY)
			{
				y-=movement;
			}
			else if(x == targetX && y == targetY)
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
		int my = GetMouseY() / GameWindow::getCamera()->zoom - GameWindow::getCamera()->offset.y / GameWindow::getCamera()->zoom;
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
			if(!GameWindow::tutorial[4] && GameObject::generation >= 5 )
			{
				GameWindow::getMessageBox()->enable("Poison/"
						"If you notice a purple background around/"
						"a monster, that means it is POISONED.//"
						"To avoid this, try evolving your/"
						"monster to have a higher size,/"
						"looking in the species menu to,/"
						"find anything toxic, or avoiding/"
						"getting into battles.");
				GameWindow::tutorial[4] = true;
			}
		}
		else
		{
			if(monster.carnivore)
			{
				DrawRectangle(x,y,8,8,{192,128,0,255});
			}
			else
			{
				DrawRectangle(x,y,8,8,{192,64,0,255});
			}
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

				if(!GameWindow::tutorial[3] && monster.enemy && GameObject::generation >= 4)
				{
					GameWindow::getMessageBox()->enable("Rival Monsters/"
							"Rival Monsters are monsters that you/"
							"are unable to influence or control./"
							"Normally, they just cause trouble.//"
							"You can tell which monsters are rivals/"
							"by their red backgrounds.//"
							"If you evolve a carnivore, they will be/"
							"able to eat these rival monsters.");
					GameWindow::tutorial[3] = true;
				}
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
			for(unsigned int i = 3600; i < GameObject::objects.size(); i++)
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


	int repValue = rand()%40;
	int gn = getNeighborhood();
	//Reproduce
	if(hp >= monster.size && age >= 2 && gn<=monster.maxNew && gn>=monster.minNew && repValue<30)
	{
		int newX = ((rand()%5)*8)-16;
		int newY = ((rand()%5)*8)-16;
		Monster* p = new Monster(this->getX()+newX,this->getY()+newY,this->getSpecies(),enemy);
		GameObject::objects.push_back(p);
		GameObject::monsters.push_back(p);
		//Monster* p1 = new Monster(this->getX()+newX+8,this->getY()+newY+8,this->getSpecies(),enemy);
		//GameObject::objects.push_back(p1);
		//GameObject::monsters.push_back(p1);
		hp -= monster.size/2;
		if(monster.size == 1)
		{
			hp -= 1;
		}
		int randNum = 0;
		randNum = 400/(4);
		if(randNum < 100)
		{
			randNum = 100;
		}
		if(rand()%2000<200 && monster.enemy && alive && evolutionOccuredYetMonst <  1)
		{
			evolve();
			evolutionOccuredYetMonst++;
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
	if((!monster.behaviors[Behaviors::SWALK_1]) || (monster.behaviors[Behaviors::SWALK_1] && rand()%100<50) )
	{
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
	}
	//die when they live longer than their lifespan.
	if(age>monster.lifespan)
	{
		this->kill();
	}
	//Death by overcrowding
	if(gn>monster.maxDeath && rand()%100<75)
	{
		this->kill();
	}
	//Death by lonliness
	if(gn<monster.minDeath && rand()%100<33)
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
	movementStage = 0;
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
		if(monster.speed > 3)
		{
			spd = 2;
		}
		if(monster.speed > 7)
		{
			spd = 4;
		}

		int amountOfOptions = 1;
		if(monster.behaviors[Behaviors::RUN_MONSTERS] || monster.behaviors[Behaviors::TO_MONSTERS])
		{
			amountOfOptions++;
		}
		if(monster.behaviors[Behaviors::SPREAD] || monster.behaviors[Behaviors::TOGETHER])
		{
			amountOfOptions++;
		}
		if(monster.behaviors[Behaviors::TO_PLANTS])
		{
			amountOfOptions++;
		}
		if(monster.behaviors[Behaviors::TO_MEAT] || monster.behaviors[Behaviors::AWAY_MEAT])
		{
			amountOfOptions++;
		}
		if(targetX == -1 && targetY == -1)
		{
			if(targetX == -1 && ((!monster.carnivore && hp < monster.size+(2*monster.metabolism)) || rand()%amountOfOptions<=3) && monster.behaviors[Behaviors::TO_PLANTS])
			{
				plantsMovement();
			}
			if(targetX == -1 && ((monster.carnivore && hp< monster.size+(2*monster.metabolism)) || rand()%amountOfOptions<=3) && monster.behaviors[Behaviors::TO_MEAT])
			{
				meatMovement();
			}
			if(targetX == -1 && rand()%amountOfOptions<=2 && (monster.behaviors[2] || monster.behaviors[3]))
			{
				groupingMovement();
			}
			if(targetX == -1 && (monster.behaviors[0] || monster.behaviors[1]))
			{
				closeFarMovement();
			}
			if(targetX == -1)
			{
				selectRandomTarget();
			}
		}
		if(!enemy)
		{
			removeFog();
		}
		Camera2D* cam = GameWindow::getCamera();

		int a = -GameWindow::getCamera()->offset.x / GameWindow::getCamera()->zoom;
		int b = -GameWindow::getCamera()->offset.y / GameWindow::getCamera()->zoom;
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
		if(x < a || x > a + GameWindow::getCamera()->zoom*480)
		{
			x = targetX;
			y = targetY;
		}
		else if(y < b || y > b + GameWindow::getCamera()->zoom*480)
		{
			x = targetX;
			y = targetY;
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
	if(monster.carnivore || monster.behaviors[Behaviors::WEAPON_1])
	{
		//cout << "CARNIVORE" << endl;
		for(unsigned int i=3600; i<GameObject::objects.size();i++)
		{
			if(GameObject::objects[i] && GameObject::objects[i]->getName() == "Meat" && monster.carnivore)
			{
				Meat* m = static_cast<Meat*>(GameObject::objects[i]);
				if(m && monster.carnivore && CheckCollisionRecs(m->getBounds(),this->getBounds()) && m->getSpecies() != species)
				{
					hp += m->eat();
				}
			}
			if(GameObject::objects[i] && GameObject::objects[i]->getName() == "Meat" && monster.behaviors[Behaviors::WEAPON_1])
			{
				Monster* m = static_cast<Monster*>(GameObject::objects[i]);
				if(CheckCollisionRecs(m->getBounds(),this->getBounds()) && m->getSpecies() != species)
				{
					MonsterSpecies ms = Species::monsterSpecies[m->getSpecies()];
					if(m->isEnemy() || isEnemy())
					{
						if(monster.strength > ms.resil)
						{
							EyeCandy* ec;
							if(!isEnemy())
							{
								ec = new EyeCandy(m->getX(),m->getY(),0);
							}
							else if(!m->isEnemy())
							{
								ec = new EyeCandy(m->getX(),m->getY(),1);
							}
							else
							{
								ec = new EyeCandy(m->getX(),m->getY(),2);
							}
							objects.push_back(new Meat(m->getX(),m->getY(),Species::monsterSpecies[m->getSpecies()].size+1,m->getSpecies()));
							objects.push_back(ec);
							m->kill();
						}
						else if(monster.resil < ms.strength)
						{
							EyeCandy* ec;
							if(!isEnemy())
							{
								ec = new EyeCandy(m->getX(),m->getY(),2);
							}
							else if(!m->isEnemy())
							{
								ec = new EyeCandy(m->getX(),m->getY(),1);
							}
							else
							{
								ec = new EyeCandy(m->getX(),m->getY(),0);
							}
							objects.push_back(new Meat(getX(),getY(),Species::monsterSpecies[m->getSpecies()].size+1,m->getSpecies()));
							objects.push_back(ec);
							kill();
						}
					}
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
	if(monster.behaviors[Behaviors::VIEW_1])
	{
		GameObject::fog[normX-1][normY].disable();
		GameObject::fog[normX+1][normY].disable();
		GameObject::fog[normX][normY+1].disable();
		GameObject::fog[normX][normY-1].disable();
	}
	if(monster.behaviors[Behaviors::VIEW_2])
	{
		GameObject::fog[normX-1][normY-1].disable();
		GameObject::fog[normX-1][normY+1].disable();
		GameObject::fog[normX+1][normY-1].disable();
		GameObject::fog[normX+1][normY+1].disable();
	}
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
	else if(plant.toxicity-2 > monster.size)
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

	if(rand()%100<20)
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
	if(rand()%100<20)
	{
		minDeath--;
		maxDeath++;
		lifespan--;
	}
	else if(maxDeath-minDeath > 1 && rand()%100<20)
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
	else if(toxicity > 0 && rand()%100<50)
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
		speed += 1;
	}
	else if(rand()%100<40)
	{
		metabolism-=2;
		speed--;
	}

	if(rand()%100<50)
	{
		strength += 2;
		resil--;
	}
	if(rand()%100<50)
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
	if(rand()%100<60)
	{
		agression++;
		strength++;
	}
	else if(rand()%100<50)
	{
		agression--;
		resil++;
	}
	if(agression < 0)
	{
		agression = 0;
	}
	if(agression > 10)
	{
		agression = 10;
	}
	if(rand()%100<50)
	{
		groupSize+=10;
	}
	if(rand()%100<50 && groupSize > 10)
	{
		groupSize-=10;
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

	newSp.complexity = monster.complexity+1;


	if(newSp.carnivore)
	{
		newSp.agression += 4;
	}
	newSp.image = monster.image;
	newSp.name = Species::generateName();
	newSp.bodyColor = monster.bodyColor;
	newSp.eyeColor = monster.eyeColor;
	newSp.highlightColor = monster.highlightColor;
	newSp.enemy = true;

	for(int i=0; i<100; i++)
	{
		newSp.behaviors[i] = monster.behaviors[i];
		if(rand()%100<15)
		{
			newSp.behaviors[i] = false;
		}
	}
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
	else if(newSp.size < 8)
	{

		if(rand()%5<=2)
		{
			newSp.image = MonsterImg::small0;
		}
		else if(rand()%5<=2)
		{
			newSp.image = MonsterImg::small2;
		}
		else if(rand()%5<=2)
		{
			newSp.image = MonsterImg::small1;
		}
		else if(rand()%5<=2)
		{
			newSp.image = MonsterImg::small3;
		}
		else
		{
			newSp.image = MonsterImg::small4;
		}
	}
	else
	{

		if(rand()%7<=2)
		{
			newSp.image = MonsterImg::basic0;
		}
		else if(rand()%7<=2)
		{
			newSp.image = MonsterImg::basic1;
		}
		else if(rand()%7<=2)
		{
			newSp.image = MonsterImg::medium0;
		}
		else if(rand()%7<=2)
		{
			newSp.image = MonsterImg::medium1;
		}
		else if(rand()%7<=2)
		{
			newSp.image = MonsterImg::medium2;
		}
		else
		{
			newSp.image = MonsterImg::basic2;
		}
	}

	if(GameObject::generation > -1)
	{
		if(!monster.behaviors[0] && !monster.behaviors[1])
		{
			if(rand()%100 < 40)
			{
				newSp.behaviors[0] = true;
			}
			else if(rand()%100 < 40)
			{
				newSp.behaviors[1] = true;
			}
		}
		if(!monster.behaviors[2] && !monster.behaviors[3])
		{
			if(rand()%100 < 40)
			{
				newSp.behaviors[2] = true;
			}
			else if(rand()%100 < 40)
			{
				newSp.behaviors[3] = true;
			}
		}
		if(monster.behaviors[0] || monster.behaviors[1])
		{
			if(!monster.behaviors[4] && !monster.behaviors[5])
			{
				if(rand()%100 < 40)
				{
					newSp.behaviors[4] = true;
				}
				else if(rand()%100 < 40)
				{
					newSp.behaviors[5] = true;
				}
			}
		}
		if(monster.behaviors[4])
		{
			if(!monster.behaviors[6])
			{
				newSp.behaviors[6] = true;
			}
		}
		if(newSp.carnivore && rand()%100<75)
		{
			newSp.behaviors[5] = true;
		}
		if(!newSp.carnivore && rand()%100<75)
		{
			newSp.behaviors[5] = false;
		}
		if(newSp.strength >= 5 && newSp.complexity >= 4)
		{
			newSp.behaviors[Behaviors::WEAPON_1] = true;
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
	GameObject::monsters.push_back(p);
	int r = rand()%2;
	for(int i=0; i<(r)+1;i++)
	{
		newX = ((rand()%6)*8)-32;
		newY = ((rand()%6)*8)-32;
		Monster* p = new Monster(this->getX()+newX,this->getY()+newY,Species::monsterSpecies.size()-1,true);
		Monster* p1 = new Monster(this->getX()+newX,this->getY()+newY+8,Species::monsterSpecies.size()-1,true);
		GameObject::objects.push_back(p);
		GameObject::monsters.push_back(p);
		GameObject::objects.push_back(p1);
		GameObject::monsters.push_back(p1);
		Monster* p2 = new Monster(this->getX()+newX+8,this->getY()+newY,Species::monsterSpecies.size()-1,true);
		Monster* p3 = new Monster(this->getX()+newX+8,this->getY()+newY+8,Species::monsterSpecies.size()-1,true);
		GameObject::objects.push_back(p2);
		GameObject::monsters.push_back(p2);
		GameObject::objects.push_back(p3);
		GameObject::monsters.push_back(p3);
	}
}
void Monster::attackMonsters()
{
	Monster* m;
	for(unsigned int i=0; i < GameObject::monsters.size(); i++)
	{
		if(GameObject::monsters[i] && GameObject::monsters[i]->getName() == "Monster")
		{
			if(sqrt(pow(GameObject::monsters[i]->getX()-x,2)+pow(GameObject::monsters[i]->getY()-y,2)) <= 12)
			{
				bool ok = true;
				m = static_cast<Monster*>(GameObject::monsters[i]);
				if(m == this)
				{
					ok = false;
				}
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
					if(opponent.toxicity - 2 > monster.size)
					{
						setPoison(opponent.toxicity - monster.size);
						poisoned = 1;
					}

					if(opponent.size + 2 < monster.toxicity)
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
							EyeCandy* ec;
							if(m->isEnemy())
							{
								ec = new EyeCandy(m->getX(),m->getY(),1);
							}
							else
							{
								ec = new EyeCandy(m->getX(),m->getY(),2);
							}
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
							objects.push_back(ec);
						}
						else if(poisoned == 2)
						{
							EyeCandy* ec = new EyeCandy(m->getX(),m->getY(),1);
							objects.push_back(ec);
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

int Monster::distanceToFrom(int ex, int ey, int sx, int sy)
{
	return std::sqrt(std::pow(std::abs(sx-ex),2) + std::pow(std::abs(sy-ey),2));
}

void Monster::closeFarMovement()
{
	selectRandomTarget();
	if(monster.behaviors[0])
	{
		Monster* closestMonster = NULL;
		int shortestDist = 99999;
		for(unsigned int i=0; i<GameObject::monsters.size(); i++)
		{
			if(monsters[i]->getName() == "Monster")
			{
				Monster* monst = static_cast<Monster*>(monsters[i]);
				if(Species::monsterSpecies[monst->getSpecies()].enemy != monster.enemy && Species::monsterSpecies[monst->getSpecies()].land == monster.land)
				{
					int dist = std::abs(distanceToFrom(monsters[i]->getX(),monsters[i]->getY(),x,y));

					if(shortestDist > dist)
					{
						shortestDist = dist;
						closestMonster = monst;
					}
				}
			}
		}
		for(int i=0; i<100; i++)
		{
			if(!closestMonster)
			{
				break;
			}
			/*
			if(std::abs(distanceToFrom(closestMonster->getX(),closestMonster->getY(),x,y)) > 64)
			{
				targetX = -1;
				targetY = -1;
				return;
			}*/
			targetX = -1;
			targetY = -1;
			selectRandomTarget();
			if(std::abs(distanceToFrom(closestMonster->getX(),closestMonster->getY(),x,y)) < std::abs(distanceToFrom(closestMonster->getX(),closestMonster->getY(),targetX,targetY)))
			{
				break;
			}
		}
	}
	if(monster.behaviors[1])
	{
		Monster* closestMonster = NULL;
		int shortestDist = 99999;
		for(unsigned int i=0; i<GameObject::monsters.size(); i++)
		{
			if(monsters[i]->getName() == "Monster")
			{
				Monster* monst = static_cast<Monster*>(monsters[i]);
				if(Species::monsterSpecies[monst->getSpecies()].enemy != monster.enemy && Species::monsterSpecies[monst->getSpecies()].land == monster.land)
				{
					int dist = std::abs(distanceToFrom(monsters[i]->getX(),monsters[i]->getY(),x,y));
					if(shortestDist > dist)
					{
						shortestDist = dist;
						closestMonster = monst;
					}
				}
			}
		}
		std::cout << "s:" << shortestDist << endl;
		for(int i=0; i<100; i++)
		{
			if(!closestMonster)
			{
				break;
			}
			/*
			if(std::abs(distanceToFrom(closestMonster->getX(),closestMonster->getY(),x,y)) > 64)
			{
				targetX = -1;
				targetY = -1;
				return;
			}*/
			targetX = -1;
			targetY = -1;
			selectRandomTarget();
			if(std::abs(distanceToFrom(closestMonster->getX(),closestMonster->getY(),x,y)) > std::abs(distanceToFrom(closestMonster->getX(),closestMonster->getY(),targetX,targetY)))
			{
				break;
			}
		}
	}
}

void Monster::groupingMovement()
{
	selectRandomTarget();
	cout << "HERE" << endl;
	if(monster.behaviors[2])
	{
		Monster* closestMonster = NULL;
		int shortestDist = 99999;
		for(unsigned int i=0; i<GameObject::monsters.size(); i++)
		{
			if(monsters[i]->getName() == "Monster")
			{
				Monster* monst = static_cast<Monster*>(monsters[i]);
				if(monst->getSpecies() == species && monst != this)
				{
					int dist = std::abs(distanceToFrom(monsters[i]->getX(),monsters[i]->getY(),x,y));

					if(shortestDist > dist)
					{
						shortestDist = dist;
						closestMonster = monst;
					}
				}
			}
		}
		for(int i=0; i<100; i++)
		{
			if(!closestMonster)
			{
				break;
			}
			targetX = -1;
			targetY = -1;
			selectRandomTarget();
			if(std::abs(distanceToFrom(closestMonster->getX(),closestMonster->getY(),x,y)) < std::abs(distanceToFrom(closestMonster->getX(),closestMonster->getY(),targetX,targetY)))
			{
				break;
			}
		}
	}
	if(monster.behaviors[3])
	{
		Monster* closestMonster = NULL;
		int shortestDist = 99999;
		for(unsigned int i=0; i<GameObject::monsters.size(); i++)
		{
			if(monsters[i]->getName() == "Monster")
			{
				Monster* monst = static_cast<Monster*>(monsters[i]);
				if(monst->getSpecies() == species && monst != this)
				{
					int dist = std::abs(distanceToFrom(monsters[i]->getX(),monsters[i]->getY(),x,y));
					if(shortestDist > dist)
					{
						shortestDist = dist;
						closestMonster = monst;
					}
				}
			}
		}
		for(int i=0; i<100; i++)
		{
			if(!closestMonster)
			{
				break;
			}
			targetX = -1;
			targetY = -1;
			selectRandomTarget();
			if(std::abs(distanceToFrom(closestMonster->getX(),closestMonster->getY(),x,y)) > std::abs(distanceToFrom(closestMonster->getX(),closestMonster->getY(),targetX,targetY)))
			{
				break;
			}
		}
	}
}

void Monster::plantsMovement()
{
	selectRandomTarget();
	Plant* closestPlant = NULL;
	int shortestDist = 99999;
	for(unsigned int i=0; i<GameObject::objects.size(); i++)
	{
		if(objects[i]->getName() == "Plant")
		{
			Plant* plnt = static_cast<Plant*>(objects[i]);
			if(Species::plantSpecies[plnt->getSpecies()].land == monster.land)
			{
				int dist = std::abs(distanceToFrom(objects[i]->getX(),objects[i]->getY(),x,y));

				if(shortestDist > dist)
				{
					shortestDist = dist;
					closestPlant = plnt;
				}
			}
		}
	}
	for(int i=0; i<100; i++)
	{
		if(!closestPlant)
		{
			break;
		}
		targetX = -1;
		targetY = -1;
		selectRandomTarget();
		if(std::abs(distanceToFrom(closestPlant->getX(),closestPlant->getY(),x,y)) > std::abs(distanceToFrom(closestPlant->getX(),closestPlant->getY(),targetX,targetY)))
		{
			break;
		}
	}
}

void Monster::meatMovement()
{
	selectRandomTarget();
	Meat* closestMeat = NULL;
	int shortestDist = 99999;
	for(unsigned int i=0; i<GameObject::objects.size(); i++)
	{
		if(objects[i]->getName() == "Meat")
		{
			Meat* meat = static_cast<Meat*>(objects[i]);
			if(Species::monsterSpecies[meat->getSpecies()].land == monster.land)
			{
				int dist = std::abs(distanceToFrom(meat->getX(),meat->getY(),x,y));

				if(shortestDist > dist)
				{
					if(monster.behaviors[Behaviors::TO_MEAT] && meat->getSpecies() != species)
					{
						shortestDist = dist;
						closestMeat = meat;
					}
				}
			}
		}
	}
	for(int i=0; i<100; i++)
	{
		if(!closestMeat)
		{
			break;
		}
		targetX = -1;
		targetY = -1;
		selectRandomTarget();
		if(monster.behaviors[Behaviors::TO_MEAT])
		{
			if(std::abs(distanceToFrom(closestMeat->getX(),closestMeat->getY(),x,y)) > std::abs(distanceToFrom(closestMeat->getX(),closestMeat->getY(),targetX,targetY)))
			{
				break;
			}
		}
		else if(monster.behaviors[Behaviors::AWAY_MEAT])
		{
			if(std::abs(distanceToFrom(closestMeat->getX(),closestMeat->getY(),x,y)) < std::abs(distanceToFrom(closestMeat->getX(),closestMeat->getY(),targetX,targetY)))
			{
				break;
			}
		}
	}
}
