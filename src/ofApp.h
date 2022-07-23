#pragma once

#include "ofMain.h"
#include "GameSettings.hpp"
#include "GameFlow.hpp"
#include "World.hpp"
#include "Coin.hpp"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
		void exit();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);

		enum class gameState { START, GAME, END };
		gameState game_state;

		GameFlow* game;
		GameSettings* game_settings;
		World* world;
		Coin* coin;

		bool mouse_pressed;
		int mouse_pressed_button, mouse_pressed_x, mouse_pressed_y;
};
