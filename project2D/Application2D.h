#pragma once

#include "Application.h"
#include "Renderer2D.h"
#include "Audio.h"
#include "Button.h"
#include <string>


class Application2D : public aie::Application {
public:
	enum gameState {
		menu,
		playing,
		over
	};



	Application2D();
	virtual ~Application2D();

	virtual bool startup();
	virtual void shutdown();

	virtual void update(float deltaTime);
	virtual void draw();



protected:

	aie::Renderer2D *	m_2dRenderer;
	aie::Font *	m_font;
	float m_cameraX, m_cameraY;
	float m_timer;

	gameState currentState;

	int ** tttField;
	bool ai;
	int playerTurn;
	int difficulty;
	int p1Score;
	int p2Score;



	Button ** tttButton;
	Button * menuButtons;
	

	Button * buttonCollision(Button * checkIn, int size, int x, int y);
	Button * buttonCollision(Button ** checkIn, int rows, int col, int x, int y);
	bool isCollision(Button * checkIn, int x, int y);

	int checkWinner(int ** field);

	//AI Functions 
	
	bool tryWin(int ** field);
	bool counterWin(int ** field);
	bool placeInGoodPos(int ** field);
	bool placeInRandPos(int ** field);
	

};