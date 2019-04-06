/*
 * FileUI.h
 *
 *  Created on: Jan 24, 2019
 *      Author: truttle1
 */

#ifndef UI_FileUI_FileUI_H_
#define UI_FileUI_FileUI_H_
#include "../UI.h"
#include "../../species/Species.h"
#include "../../objects/GameObject.h"
#include "../../objects/world/Ground.h"
#include "../../objects/world/Monster.h"
#include "../monsterui/TextBox.h"
#include <fstream>
#include <sstream>
class FileUI : public UI
{
	public:
		FileUI();
		virtual ~FileUI();
		void tick();
		void render();
		void close();
		bool getRunning();
		void toggle();
		void init(bool iSaving);
		void lighten();
	private:
		bool running;
		bool saving;
		unsigned int curViewing = 0;
		float startX = 128.0f;
		float startY = 128.0f;
		float size = 16.0f;
		Rectangle srcRect = {0.0f,0.0f,8.0f,8.0f};
		Rectangle destRect = {startX,startY,startX+size,startY+size};
		Vector2 origin = {startX,startY};

		Texture water0;
		Texture water1;
		Texture freshwater0;
		Texture freshwater1;
		Texture dirt;
		Texture beach;
		Texture jungle;
		Texture grass;
		Texture tundra;
		Texture mountain;
		Texture snow;
		Texture desert;
		TextBox fileName;
		Texture2D leftButton;
		Texture2D rightButton;
		int selection = 0;
		void save(std::string filename);
		bool load(std::string filename);
		void saveUI();
		void loadUI();
		bool dark = true;

		int backX = 420;
		int backY = 320;

};

#endif /* UI_FileUI_FileUI_H_ */
