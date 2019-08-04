/*
 * Unit.h
 *
 *  Created on: Jul 24, 2019
 *      Author: truttle1
 */

#ifndef CIVILIZED_UNITS_UNIT_H_
#define CIVILIZED_UNITS_UNIT_H_
#include "../../objects/GameObject.h"
#include "../Civilizations.h"
class Unit : public GameObject
{
	public:
		Unit(int ix, int iy);
		virtual ~Unit();
		virtual void tick();
		virtual void render()=0;
		void nextGeneration();
		virtual void nextMove();
		virtual void nextEat()=0;
		virtual void finalize()=0;
		void setOwner(int iOwner);
		Rectangle getBounds();
		int getOwner();
		bool getTribal();
		bool isMoving();
		void resetMovement();

	protected:
		int owner;
		bool tribal;
		int targetX;
		int targetY;
		bool moved;
		void selectRandomTarget();
		int movementStage;

	private:

};

#endif /* CIVILIZED_UNITS_UNIT_H_ */
