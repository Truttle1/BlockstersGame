/*
 * ScienceButton.h
 *
 *  Created on: Apr 15, 2019
 *      Author: truttle1
 */

#ifndef UI_MONSTERUI_ScienceButton_H_
#define UI_MONSTERUI_ScienceButton_H_
#include "../../ui/UI.h"
#include "../../species/Species.h"
#include <vector>

class ScienceButton {
public:
	ScienceButton(int iX, int iY, int iCost);
	virtual ~ScienceButton();
	int getStatus();
	void init(Texture2D iTexture,std::vector<std::string> iText);
	void enable();
	void disable();
	void tick();
	void render();
	void setStatus(int iStatus);
	int getCost();
	std::vector<std::string> getText();
	void setTexture(bool tex);
	void setAltTexture(Texture2D iTexture,std::vector<std::string> iText);
	void setWarning(std::string iHeader, std::vector<std::string> iMessage);
	std::vector<std::string> getMessage();
	std::string getHeader();
private:
	bool getClicking(int nx, int ny, int wx, int wy);
	int status;
	bool altTexture = false;
	Texture2D texture;
	Texture2D texture2;
	bool visible = false;
	std::vector<std::string> text;
	std::vector<std::string> altText;
	std::vector<std::string> warningMessage;
	std::string messageHeader;
	int x;
	int y;
	int cost;
};

#endif /* UI_MONSTERUI_ScienceButton_H_ */
