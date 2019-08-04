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
	wasClicked = false;
	alive = true;
	name = MONSTER;
	species = sp;
	arbitraryPopNumber = (rand()%10)+1;
	Species::monsterSpecies[species].population += arbitraryPopNumber;
	age = 0;
	enemy = e;
	targetX = -1;
	targetY = -1;
	movementStage = 0;
	moved = false;
	hp = Species::monsterSpecies[species].metabolism+1;
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
	clusterX = (x / 16) / 6;
	clusterY = (y / 16) / 6;
	//std::cout << clusterX << "," << clusterY << endl;
	if(!enemy && monster.behaviors[Behaviors::SHELTER_1] && !GameWindow::tutorial[5])
	{
		GameWindow::getMessageBox()->enable("Shelters/"
				"Your newest monster, " + monster.name +
				",/is able to build SHELTERS!//"
				"Shelters protect your monsters from/"
				"the outside. To create one, you click the/"
				"\"Create Shelter\" button on the sidebar.//"
				"Monsters will often need to bring food/"
				"to shelters, otherwise they run out/"
				"and starve. By clicking a shelter, you/"
				"can have a monster leave it. If you place/"
				"a monster on top of a shelter, it may/enter.");
		GameWindow::tutorial[5] = true;
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
	if(!alive)
	{
		return;
	}

	int normX = (x/16);
	int normY = (y/16);
	if(!GameObject::fog[normX][normY].isVisible())
	{
		getClicking();
	}
	if(clickedHere && !UI::isOpen())
	{
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
		if(poison == 0 && alive && !UI::isOpen())
		{
			GameWindow::showUpperText(monster.name + "    " + rivalStatus + "    Group of " + to_string(arbitraryPopNumber) +
								"\nFOOD: " + to_string(hp) + "    Movements Left: " + to_string(monster.speed - movementStage)+ "    Age: " + to_string(age));
		}
		else if(!UI::isOpen())
		{
			GameWindow::showUpperText(monster.name + "    " + rivalStatus + "    Group of " + to_string(arbitraryPopNumber) +
								"\nFOOD: " + to_string(hp) + "    Movements Left: " + to_string(monster.speed - movementStage)+ "    POISON: -" + to_string(poison) + " HP/Gen");
		}

		if(monster.behaviors[Behaviors::SHELTER_1])
		{
			onShelter();
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
		if(monster.carnivore || monster.behaviors[Behaviors::WEAPON_1])
		{
			for(unsigned int i=3600; i<GameObject::objects.size();i++)
			{
				if(GameObject::objects[i] && GameObject::objects[i]->getName() == MEAT)
				{
					Meat* m = static_cast<Meat*>(GameObject::objects[i]);
					if(m && monster.carnivore && m->isAlive() && CheckCollisionRecs(m->getBounds(),this->getBounds()) && m->getSpecies() != species)
					{
						hp += m->eat();
					}
				}
				if(!killed && GameObject::objects[i] != this && GameObject::objects[i]->getName() == MONSTER && monster.behaviors[Behaviors::WEAPON_1])
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
								killed = true;
							}
							else if(monster.resil < ms.strength)
							{
								EyeCandy* ec;
								if(!isEnemy())
								{
									ec = new EyeCandy(getX(),getY(),2);
								}
								else if(!m->isEnemy())
								{
									ec = new EyeCandy(getX(),getY(),1);
								}
								else
								{
									ec = new EyeCandy(getX(),getY(),0);
								}
								objects.push_back(new Meat(getX(),getY(),Species::monsterSpecies[m->getSpecies()].size+1,m->getSpecies()));
								objects.push_back(ec);
								kill();
								killed = true;
							}
						}
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
			if(monster.behaviors[Behaviors::SHELTER_1])
			{
				if(onShelter())
				{
					GameWindow::setShelterButton(2);
				}
				else
				{
					GameWindow::setShelterButton(1);
				}
			}

			if(IsKeyPressed(KEY_W))
			{
				targetX = x;
				targetY = y-8;
				moved = false;
				movementStage++;
				killed = false;
			}
			if(IsKeyPressed(KEY_A))
			{
				targetX = x-8;
				targetY = y;
				moved = false;
				movementStage++;
				killed = false;
			}
			if(IsKeyPressed(KEY_S))
			{
				targetX = x;
				targetY = y+8;
				moved = false;
				movementStage++;
				killed = false;
			}
			if(IsKeyPressed(KEY_D))
			{
				targetX = x+8;
				targetY = y;
				moved = false;
				movementStage++;
				killed = false;
			}
			if(monster.behaviors[Behaviors::SHELTER_1])
			{
				if(IsKeyPressed(KEY_H) || GameWindow::getShelterButton() == 1)
				{
					createShelter();
					if(GameWindow::getShelterButton() > -1)
					{
						GameWindow::finishClick();
					}
				}
				if(IsKeyPressed(KEY_E) || GameWindow::getShelterButton() == 2)
				{
					enterShelter();
					if(GameWindow::getShelterButton() > -1)
					{
						GameWindow::finishClick();
					}
				}
			}

		}
		if(!moved && targetX != -1 && targetY != -1)
		{
			int normX = (x/16);
			int normY = (y/16);
			int normTX = (targetX/16);
			int normTY = (targetY/16);

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

	if(wasClicked && !clickedHere)
	{
		GameWindow::setShelterButton(0);
	}
	wasClicked = clickedHere;
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
		if(clicking && GetMouseX() < 480)
		{
			clickedHere = true;
		}
		else if(GetMouseX() < 480)
		{
			clickedHere = false;
		}
	}
	return clicking;
}

void Monster::render()
{
	if(!alive)
	{
		return;
	}
	int normX = (x/16);
	int normY = (y/16);

	if(GameObject::fog[normX][normY].isVisible())
	{
		return;
	}
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
						"monster to have a higher defense,/"
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
	killSameLocation();
	killed = false;
	movementStage = 0;
	hasEaten = false;
	bool onLand = true;
	targetX = -1;
	targetY = -1;
	x = (x/8)*8;
	y = (y/8)*8;
	moved = true;
	clickedHere = false;

	if(monster.behaviors[Behaviors::SHELTER_1] && shelterX == -1 && enemy)
	{
		if(rand()%100 < 50 && hp > monster.metabolism * 1.5)
		{
			createShelter();
		}
		if(rand()%100 < 74 && onShelter())
		{
			enterShelter();
		}
	}

	for(uint i = 0; i<GameObject::objects.size();i++)
	{
		GameObject* g = GameObject::objects[i];
		if(g->getName() == GROUND)
		{
			Ground* g2 = dynamic_cast<Ground*>(g);
			if(CheckCollisionRecs(g2->getBounds(),this->getBounds()))
			{
				if(g2->getBiome() == WATER || g2->getBiome() == FRESHWATER)
				{
					onLand = false;
				}
			}
			biome = g2->getBiome();
		}
	}
	if(!enemy)
	{
		removeFog();
	}
	if(!hasEaten && (hp < monster.size * 3 || monster.behaviors[Behaviors::SHELTER_1]))
	{
		if(!monster.carnivore)
		{
			for(unsigned int i = 3600; i < GameObject::objects.size(); i++)
			{
				if(GameObject::objects[i]->getName() == PLANT)
				{
					int px = GameObject::objects[i]->getX();
					int py = GameObject::objects[i]->getY();
					if(std::abs(px-x) <= 16 && std::abs(py-y) <= 16)
					{
						Plant* plant = static_cast<Plant*>(GameObject::objects[i]);
						if(true/*plant->getAlive()*/)
						{
							eatPlant(plant);
						}
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
	if(hp >= monster.metabolism * 1.5 && age >= 2 && gn<=monster.maxNew && gn>=monster.minNew && repValue<30)
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
		if(monster.evolvePass >= 0 && rand()%2000<50 && monster.enemy && alive)
		{
			if(evolutionOccuredYetMonst <  2 && monster.land)
			{
				evolve();
				evolutionOccuredYetMonst++;
			}
			else if(evolutionOccuredYetMonstWater <  2 && !monster.land)
			{

				evolve();
				evolutionOccuredYetMonstWater++;
			}
		}
		if(false && generation < 10 && objects.size() < 6000 && rand()%8000<4000/(getRemovedFog()+1) && alive && distanceToPlayer() < 256)
		{
			if(evolutionOccuredYetMonst <  1 && monster.land)
			{
				evolve();
				evolutionOccuredYetMonst++;
			}
			else if(evolutionOccuredYetMonstWater <  1 && !monster.land)
			{

				evolve();
				evolutionOccuredYetMonstWater++;
			}
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
	if(monster.behaviors[Behaviors::SWALK_1] && biome == FRESHWATER)
	{

	}
	else if((!monster.behaviors[Behaviors::SWALK_1]) || (monster.behaviors[Behaviors::SWALK_1] && !monster.behaviors[Behaviors::SWALK_2] && rand()%100<50) )
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
	else if(monster.behaviors[Behaviors::SWALK_2] && rand()%100<75)
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
	if(age>monster.lifespan && rand()%100 < 50)
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
	for(uint i = 0; i<GameObject::monsters.size();i++)
	{
		GameObject* temp = GameObject::monsters[i];
		int distX = std::abs((this->getX())-(temp->getX()));
		int distY = std::abs((this->getY())-(temp->getY()));
		if(distX <= 8 && distY <= 8 && temp != this && temp->getName() == MONSTER)
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
			if(targetX == -1  && shelterX != -1 && (hp > 3*monster.metabolism) && monster.behaviors[Behaviors::SHELTER_1])
			{
				shelterMovement();
			}
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

	if(monster.behaviors[Behaviors::WEAPON_2])
	{
		for(unsigned int i = 0; i < GameObject::shelters.size(); i++)
		{
			Shelter* shelt = static_cast<Shelter*>(GameObject::shelters[i]);
			if(CheckCollisionRecs(shelt->getBounds(),getBounds()) && shelt->getType() == 0)
			{
				if(Species::monsterSpecies[shelt->getSpecies()].resil < monster.strength && (Species::monsterSpecies[shelt->getSpecies()].enemy || isEnemy()))
				{
					EyeCandy* ec;
					if(!isEnemy())
					{
						ec = new EyeCandy(shelt->getX(),shelt->getY(),0);
					}
					else if(Species::monsterSpecies[shelt->getSpecies()].enemy)
					{
						ec = new EyeCandy(shelt->getX(),shelt->getY(),2);
					}
					else
					{
						ec = new EyeCandy(shelt->getX(),shelt->getY(),1);
					}
					shelt->kill();
					objects.push_back(ec);
				}
			}

		}
	}
	if(monster.carnivore || monster.behaviors[Behaviors::WEAPON_1])
	{
		//cout << "CARNIVORE" << endl;
		for(unsigned int i=3600; i<GameObject::objects.size();i++)
		{
			if(GameObject::objects[i] && GameObject::objects[i]->getName() == MEAT && monster.carnivore)
			{
				Meat* m = static_cast<Meat*>(GameObject::objects[i]);
				if(m && m->isAlive() && monster.carnivore && CheckCollisionRecs(m->getBounds(),this->getBounds()) && m->getSpecies() != species)
				{
					hp += m->eat();
				}
			}
			if(!killed && GameObject::objects[i] != this && GameObject::objects[i]->getName() == MONSTER && monster.behaviors[Behaviors::WEAPON_1])
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
							killed = true;
						}
						else if(monster.resil < ms.strength)
						{
							EyeCandy* ec;
							if(!isEnemy())
							{
								ec = new EyeCandy(getX(),getY(),2);
							}
							else if(!m->isEnemy())
							{
								ec = new EyeCandy(getX(),getY(),1);
							}
							else
							{
								ec = new EyeCandy(getX(),getY(),0);
							}
							objects.push_back(new Meat(getX(),getY(),Species::monsterSpecies[m->getSpecies()].size+1,m->getSpecies()));
							objects.push_back(ec);
							kill();
							killed = true;
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
		Species::monsterSpecies[species].population -= arbitraryPopNumber;
		alive = false;
	}
}

void Monster::killSameLocation()
{
	if(enemy && objects.size() > 10000)
	{
		for(unsigned int i = 0; i < objects.size(); i++)
		{
			if(objects[i]->getName() == MONSTER && objects[i] != this && objects[i]->getX() == x && objects[i]->getY() == y)
			{
				Monster* tempMonster = static_cast<Monster*>(objects[i]);
				if(Species::monsterSpecies[tempMonster->getSpecies()].size > monster.size)
				{
					kill();
				}
				else if(tempMonster->getHP() > hp)
				{
					kill();
				}
				else if(rand()%100 < 50)
				{
					kill();
				}
				else
				{
					kill();
				}
			}
		}
	}
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
	else if(plant.toxicity > monster.resil && plant.toxicity > monster.size && poison <= 0)
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
	monster.evolvePass = -2;
	if(rand()%100<40)
	{
		carnivore = !carnivore;
	}

	if(rand()%100<40)
	{
		minNew--;
		maxNew++;
		lifespan--;
	}
	else if(maxNew-minNew > 1 && rand()%100<40)
	{
		minNew++;
		maxNew++;
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
		maxDeath++;
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
	}
	if(rand()%100<50)
	{
		resil += 2;
	}

	size += 1;
	if(rand()%100<30)
	{
		strength -= 1;
	}
	if(rand()%100<30)
	{
		resil -= 1;
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
		agression+=2;
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

	bool replacedImage = false;
	replacedImage = true;
	if(newSp.size < 2)
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
	else if(newSp.size < 4)
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

	for(int i=0; i<100; i++)
	{
		newSp.behaviors[i] = monster.behaviors[i];
		if(rand()%100<15)
		{
			newSp.behaviors[i] = false;
		}
	}

	//BEHAVIORS
	if(monster.behaviors[Behaviors::SHELTER_1])
	{
		newSp.behaviors[Behaviors::SHELTER_1] = true;
	}
	if(monster.behaviors[Behaviors::SHELTER_2])
	{
		newSp.behaviors[Behaviors::SHELTER_2] = true;
	}
	if(monster.behaviors[Behaviors::WEAPON_1])
	{
		newSp.behaviors[Behaviors::WEAPON_1] = true;
	}
	if(monster.behaviors[Behaviors::WEAPON_2])
	{
		newSp.behaviors[Behaviors::WEAPON_2] = true;
	}
	if(GameObject::generation > -1)
	{
		if(!monster.behaviors[Behaviors::RUN_MONSTERS] && !monster.behaviors[Behaviors::TO_MONSTERS])
		{
			if(rand()%100 < 40)
			{
				newSp.behaviors[Behaviors::RUN_MONSTERS] = true;
			}
			else if(rand()%100 < 40)
			{
				newSp.behaviors[Behaviors::TO_MONSTERS] = true;
			}
		}
		if(!monster.behaviors[Behaviors::SPREAD] && !monster.behaviors[Behaviors::TOGETHER])
		{
			if(rand()%100 < 40)
			{
				newSp.behaviors[Behaviors::SPREAD] = true;
			}
			else if(rand()%100 < 40)
			{
				newSp.behaviors[Behaviors::TOGETHER] = true;
			}
		}
		if(monster.behaviors[Behaviors::RUN_MONSTERS] || monster.behaviors[Behaviors::TO_MONSTERS])
		{
			if(!monster.behaviors[Behaviors::TO_PLANTS] && !monster.behaviors[Behaviors::TO_MEAT])
			{
				if(rand()%100 < 40)
				{
					newSp.behaviors[Behaviors::TO_PLANTS] = true;
				}
				else if(rand()%100 < 40)
				{
					newSp.behaviors[Behaviors::TO_MEAT] = true;
				}
			}
		}
		if(monster.behaviors[Behaviors::TO_PLANTS])
		{
			if(!monster.behaviors[Behaviors::AWAY_MEAT])
			{
				newSp.behaviors[Behaviors::AWAY_MEAT] = true;
			}
		}
		if(newSp.carnivore && rand()%100<75)
		{
			newSp.behaviors[Behaviors::TO_MEAT] = true;
		}
		if(!newSp.carnivore && rand()%100<75)
		{
			newSp.behaviors[Behaviors::TO_MEAT] = false;
		}
		if(!newSp.behaviors[Behaviors::WEAPON_1] && (newSp.agression > 5 || newSp.carnivore))
		{
			if(generation > 35)
			{
				newSp.behaviors[Behaviors::WEAPON_1] = true;
				if(newSp.strength < 5)
				{
					newSp.strength = 7;
				}
			}
		}
		else if(newSp.resil > 4 && !newSp.behaviors[Behaviors::SHELTER_1])
		{
			if(newSp.complexity >= 3 && (generation > 40))
			{
				newSp.behaviors[Behaviors::SHELTER_1] = true;
			}
		}
		else if(newSp.behaviors[Behaviors::WEAPON_1] && (newSp.agression > 7 && rand()%20<8))
		{
			if(generation > 45)
			{
				newSp.behaviors[Behaviors::WEAPON_2] = true;
				if(newSp.strength < 9)
				{
					newSp.strength = 9;
				}
			}
		}
		else if(newSp.resil > 4)
		{
			if(newSp.complexity >= 3 && (generation > 50))
			{
				newSp.behaviors[Behaviors::SHELTER_2] = true;
			}
		}
	}

	if(generation > 20)
	{
		if(rand()%100<50)
		{
			newSp.behaviors[Behaviors::SWALK_1] = true;
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

	if(newSp.size > (generation/10)+3)
	{
		newSp.size = (generation/10)+3;
	}

	if(newSp.maxDeath > 5)
	{
		newSp.maxDeath = 5;
	}
	if(newSp.maxNew > 5)
	{
		newSp.maxNew = 5;
	}
	Species::monsterSpecies.push_back(newSp);
	int newX = ((rand()%5)*8)-16;
	int newY = ((rand()%5)*8)-16;
	Monster* p = new Monster(this->getX()+newX,this->getY()+newY,Species::monsterSpecies.size()-1,true);
	GameObject::objects.push_back(p);
	GameObject::monsters.push_back(p);
	int r = rand()%3;
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
		if(GameObject::monsters[i] && GameObject::monsters[i]->getName() == MONSTER)
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
					if(opponent.toxicity > monster.size)
					{
						setPoison(opponent.toxicity);
						poisoned = 1;
					}

					if(opponent.size < monster.toxicity)
					{
						m->setPoison(monster.toxicity);
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
	cout << "CloseFar" << endl;
	selectRandomTarget();
	if(monster.behaviors[0])
	{
		Monster* closestMonster = NULL;
		int shortestDist = 99999;
		for(unsigned int i=0; i<GameObject::monsters.size(); i++)
		{
			if(monsters[i]->getName() == MONSTER)
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
			if(monsters[i]->getName() == MONSTER)
			{
				Monster* monst = static_cast<Monster*>(monsters[i]);
				if(monst->getSpecies() < Species::monsterSpecies.size() && Species::monsterSpecies[monst->getSpecies()].enemy != monster.enemy && Species::monsterSpecies[monst->getSpecies()].land == monster.land)
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
	cout << "Group" << endl;
	if(monster.behaviors[2])
	{
		Monster* closestMonster = NULL;
		int shortestDist = 99999;
		for(unsigned int i=0; i<GameObject::monsters.size(); i++)
		{
			if(monsters[i]->getName() == MONSTER)
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
		for(int i=0; i<8; i++)
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
			if(monsters[i]->getName() == MONSTER)
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
		for(int i=0; i<8; i++)
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
	cout << "Plants" << endl;
	Plant* closestPlant = NULL;
	int shortestDist = 99999;
	for(unsigned int i=0; i<GameObject::cluster[clusterX][clusterY].size(); i++)
	{
		if(objects[i]->getName() == PLANT)
		{
			Plant* plnt = static_cast<Plant*>(GameObject::cluster[clusterX][clusterY][i]);
			if(Species::plantSpecies[plnt->getSpecies()].land == monster.land)
			{
				int dist = std::abs(distanceToFrom(plnt->getX(),plnt->getY(),x,y));

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


void Monster::shelterMovement()
{
	cout << "Shelter" << endl;
	if(x == shelterX && y == shelterY)
	{
		if(!onShelter())
		{
			createShelter();
		}
		else
		{
			cout << "Let's Go In" << endl;
			enterShelter();
		}
	}
	for(int i=0; i<100; i++)
	{
		targetX = -1;
		targetY = -1;
		selectRandomTarget();
		if(std::abs(distanceToFrom(shelterX,shelterY,x,y)) > std::abs(distanceToFrom(shelterX,shelterY,targetX,targetY)))
		{
			break;
		}
	}


}

void Monster::meatMovement()
{
	cout << "Meat" << endl;
	selectRandomTarget();
	Meat* closestMeat = NULL;
	int shortestDist = 99999;
	for(unsigned int i=0; i<GameObject::objects.size(); i++)
	{
		if(objects[i]->getName() == MEAT)
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

double Monster::distanceToPlayer()
{
	double dist = 99999999;
	for(unsigned int i = 0; i < monsters.size(); i++)
	{
		Monster* m = static_cast<Monster*>(monsters[i]);
		if(!m->isEnemy() && m != this)
		{
			double tempDist = std::sqrt(std::pow(x-m->getX(),2) + std::pow(x-m->getY(),2));
			if(tempDist < dist)
			{
				dist = tempDist;
			}
		}
	}
	return dist;
}

void Monster::setShelterLoc(int ix, int iy)
{
	shelterX = ix;
	shelterY = iy;
}

void Monster::createShelter()
{
	int newPop = 0;
	if(getPopulation() > hp)
	{
		newPop = rand()%((hp/2)+2);
	}
	else
	{
		newPop = getPopulation();
	}
	int type = 0;
	if(monster.behaviors[Behaviors::SHELTER_2])
	{
		type = 1;
	}
	Shelter* s = new Shelter(x,y,species,type,hp,(newPop/2)+1);
	objects.push_back(s);
	shelters.push_back(s);
	alive = false;
	Species::monsterSpecies[species].population -= arbitraryPopNumber;
}

void Monster::enterShelter()
{
	for(unsigned int i = 0; i < shelters.size(); i++)
	{
		if(shelters[i]->getX() == x && shelters[i]->getY() == y)
		{
			if(shelters[i]->getName() == SHELTER)
			{
				Shelter* shelter = static_cast<Shelter*>(shelters[i]);
				if(shelter->getSpecies() == species)
				{
					shelter->add(hp,getPopulation());
					alive = false;
					Species::monsterSpecies[species].population -= arbitraryPopNumber;
					break;
				}
			}
		}
	}
}

bool Monster::onShelter()
{
	for(unsigned int i = 0; i < shelters.size(); i++)
	{
		if(shelters[i]->getX() == x && shelters[i]->getY() == y)
		{
			if(shelters[i]->getName() == SHELTER)
			{
				Shelter* shelter = static_cast<Shelter*>(shelters[i]);
				if(shelter->getSpecies() == species && shelter->getAlive())
				{
					shelter->deClick();
					return true;
				}
			}
		}
	}
	return false;
}

