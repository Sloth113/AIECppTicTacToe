#include "Application2D.h"
#include "Texture.h"
#include "Font.h"
#include "Input.h"
#include <iostream>
#include <string>


// My tictactoe game
// Uses aie bootstrap to build 2d application for the game
//  Button classes also made for this game
//
//Made by Scott Hart, AIE S171463, CIT215077, March 2017

const int menuSize = 3;
const int boardSize = 3;


Application2D::Application2D() {

}

Application2D::~Application2D() {

}

bool Application2D::startup() {

	m_2dRenderer = new aie::Renderer2D();

	m_font = new aie::Font("./font/consolas.ttf", 32);
	m_titleFont = new aie::Font("./font/consolas.ttf", 50);

	
	m_cameraX = 0;
	m_cameraY = 0;
	m_timer = 0;


	currentState = menu;
	menuButtons = new Button[menuSize];

	tttField = new tile*[boardSize];
	tttField[0] = new tile[boardSize];
	tttField[1] = new tile[boardSize];
	tttField[2] = new tile[boardSize];

	tttField[0][0] = _;
	tttField[0][1] = _;
	tttField[0][2] = _;
	tttField[1][0] = _;
	tttField[1][1] = _;
	tttField[1][2] = _;
	tttField[2][0] = _;
	tttField[2][1] = _;
	tttField[2][2] = _;


	tttButton = new Button*[boardSize];
	tttButton[0] = new Button[boardSize];
	tttButton[1] = new Button[boardSize];
	tttButton[2] = new Button[boardSize];

	///Buttons
	//PosX,PosY,Width,Height,String
	//Math 460 width, 230 center,
	//Width 20 per character, Height 34
	int posX = getWindowWidth() / 2 - 22 * 5 / 2;
	int posY = 86;
	int width = 20 * 5;
	int height = 34;
	menuButtons[0] = Button(posX, posY, width , height, "START");
	posX = 32;
	posY = 32;
	width = 22 * 2;
	menuButtons[1] = Button(posX,posY,width, height, "AI");
	width = 22 * 4;
	menuButtons[2] = Button(getWindowWidth() -posX - width, posY, width , height, "Quit");

	///ttt buttons
	for (int y = 0; y < 3; y++) {
		for (int x = 0; x < 3; x++) {
			//Fills the screen with the buttons 
			tttButton[y][x] = Button((x * getWindowWidth() / 3) + 6, getWindowHeight() + 6 - ((y + 1)*getWindowHeight() / 3), getWindowWidth() / 3, getWindowHeight() / 3, "-", x,y);
		}
	}


	ai = false;
	playerTurn = 1;
	p1Score = 0;
	p2Score = 0;

	return true;
}

void Application2D::shutdown() {

	delete m_2dRenderer;
	delete m_font;
	delete m_titleFont;

}

void Application2D::update(float deltaTime) {
	
	// input example
	aie::Input* input = aie::Input::getInstance();


	
	//Reset all 'over' states
	for (int i = 0; i < menuSize; i++) 	{
		menuButtons[i].setOver(false);
	}
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			tttButton[i][j].setOver(false);
		}
	}
	Button * buttonOver = nullptr;
	//Check over for buttons
	if (currentState == menu) {
		//check menu buttons for over
		for (int i = 0; i < menuSize; i++) {
			if (menuButtons[i].isCollision(input->getMouseX(), input->getMouseY())) {
				buttonOver = &menuButtons[i];
			}
		}
		if (buttonOver != nullptr)
			(*buttonOver).setOver(true);
	}
	else if (currentState == playing) {
		//Check ttt field for button over
		for (int x = 0; x < boardSize; x++) {
			for (int y = 0; y < boardSize; y++) {
				if (tttButton[x][y].isCollision(input->getMouseX(), input->getMouseY())) {
					buttonOver = &tttButton[x][y];
				}
			}
		}
		if (buttonOver != nullptr)
			(*buttonOver).setOver(true);
	}

		if (currentState == menu) {

			if (input->wasMouseButtonPressed(0)) {
				//Menu options
					//Check what the mouse is over
				if (buttonOver != nullptr) {
					if ((*buttonOver).getText() == "START") {
						currentState = playing;
					}
					else if ((*buttonOver).getText() == "AI") {
						if (ai) {
							ai = false;
						}
						else ai = true;
					}
					else if ((*buttonOver).getText() == "Quit") {
						quit();
					}
				}
			}
		}
		else if (currentState == playing) {


			//Ais turn
			//'Difficult' but beatable.. Uses check winner code to find a spot to win, first trying to win, stopping a win then placing it a blank space
			if (playerTurn == 2 && ai) {
				if (!tryWin(tttField)) {
					if (!counterWin(tttField)) {
						if (placeInRandPos(tttField)) {
						}
					}
				}
				playerTurn = 1;
				//Check if AI wins
				if (checkWinner(tttField) == 1 || checkWinner(tttField) == 2 || checkWinner(tttField) == -1) {
					currentState = over;
				}

			}
			else {

				//Players input checks 
				if (input->wasMouseButtonPressed(0)) {
					//Check that the mouse is on a button and it is a selectable square
					if (buttonOver != nullptr && (*buttonOver).getText() == "-") {
						if (playerTurn == 1) {
							//Set the field to player 1 then change turn  
							tttField[(*buttonOver).getGridY()][(*buttonOver).getGridX()] = O;
							playerTurn = 2;
						}
						else {
							//set  the field to player 2 (X) then change turn
							tttField[(*buttonOver).getGridY()][(*buttonOver).getGridX()] = X;
							playerTurn = 1;
						}
						//Check for winner
						if (checkWinner(tttField) == 1 || checkWinner(tttField) == 2 || checkWinner(tttField) == -1) {
							currentState = over;
						}

					}

				}
			}


			//Set text on button to O and X
			for (int x = 0; x < 3; x++) {
				for (int y = 0; y < 3; y++) {
					if (tttField[x][y] == 1) tttButton[x][y].setText("O");
					if (tttField[x][y] == 2) tttButton[x][y].setText("X");
					if (tttField[x][y] == 0) tttButton[x][y].setText("-");
				}
			}





		}
		//Game over check for space input, and reset fields 
		if (currentState == over) {

			if (input->isKeyDown(aie::INPUT_KEY_SPACE)) {
				currentState = menu;
				if (checkWinner(tttField) == 2) {
					p2Score += 10;
				}
				else if (checkWinner(tttField) == 1) {
					p1Score += 10;
				}

				for (int y = 0; y < 3; y++) {
					//Reset field
					for (int x = 0; x < 3; x++) {
						tttField[y][x] = _;
						tttButton[y][x].setText("-");
						//std::strcpy(tttButton[y][x].text, "-");
					}
					playerTurn = 1;
				}
			}
	
	}


	// exit the application
	if (input->isKeyDown(aie::INPUT_KEY_ESCAPE))
		quit();
}

void Application2D::draw() {

	// wipe the screen to the background colour
	clearScreen();

	// set the camera position before we begin rendering
	m_2dRenderer->setCameraPos(m_cameraX, m_cameraY);

	// begin drawing sprites
	m_2dRenderer->begin();


	if (currentState == menu) {

		for (int i = 0; i < menuSize; i++) {
			//Print buttons
			menuButtons[i].draw(m_2dRenderer, m_font);
		}
		//Title
		m_2dRenderer->setRenderColour(1.0f, 1.0f, 1.0f, 1.0f);
		m_2dRenderer->drawText(m_titleFont, "TicTacToe", (0.0f), getWindowHeight() - 64.0f);
		//Player info
		m_2dRenderer->setRenderColour(1.0f, 1.0f, 1.0f, 0.5f);
		m_2dRenderer->drawText(m_font, "Player 1 = O", (0.0f), 150.0f);
		//AI darken
		if (ai) {
			m_2dRenderer->setRenderColour(0.8f, 0.2f, 0.2f, 0.5f);
			m_2dRenderer->drawText(m_font, "Player 2 = Computer", (0.0f), 125.0f);
		}
		else {
			m_2dRenderer->setRenderColour(1.0f, 1.0f, 1.0f, 0.5f);
			m_2dRenderer->drawText(m_font, "Player 2 = X", (0.0f),  125.0f);
		}

		


	}
	else if (currentState == playing || currentState == over) {
		//Print out buttons, grid and ui

		//Lines for grid
		//Horiz
		m_2dRenderer->drawLine(0.0f, getWindowHeight() / 3.0f, getWindowWidth()*1.0f, getWindowHeight() / 3.0f, 4.0f, 1.0f);
		m_2dRenderer->drawLine(0.0f, 2.0f * getWindowHeight() / 3.0f, getWindowWidth()*1.0f, 2.0f * getWindowHeight() / 3.0f, 4.0f, 1.0f);
		//Vert
		m_2dRenderer->drawLine(getWindowWidth() / 3.0f, 0.0f, getWindowWidth() / 3.0f, getWindowHeight()*1.0f, 4.0f, 1.0f);
		m_2dRenderer->drawLine(2.0f * getWindowWidth() / 3.0f, 0.0f, 2.0f * getWindowWidth() / 3.0f, getWindowHeight()*1.0f, 4.0f, 1.0f);
		

		//DRAW X and Os
		float posXCenter = 0;
		float posYCenter = 0;
		for (int y = 0; y < 3; y++) {
			for (int x = 0; x < 3; x++) {
				//           Displacement                  top left position
				posXCenter = (x * getWindowWidth() / 3.0f) + (getWindowWidth() / 3.0f - (getWindowWidth() / 3.0f / 2.0f));
				//			 -Displaced					  top left position
				posYCenter = getWindowWidth() - (y*getWindowHeight() / 3) - (getWindowWidth() / 3.0f / 2.0f);

				if (tttButton[y][x].getText() == "-") {
					//DOT
					m_2dRenderer->setRenderColour(1.0f, 1.0f, 1.0f, 1.0f);
					m_2dRenderer->drawCircle(posXCenter, posYCenter, 5.0f, 0.5f);
				}
				else if (tttButton[y][x].getText() == "O") {
					//O
					m_2dRenderer->setRenderColour(0.0f, 0.0f, 1.0f, 1.0f);
					m_2dRenderer->drawCircle(posXCenter, posYCenter, 50.0f, 0.5f);
					m_2dRenderer->setRenderColour(0.0f, 0.0f, 0.0f, 1.0f);
					m_2dRenderer->drawCircle(posXCenter, posYCenter, 30.0f, 0.5f);
					//Reset render colour to white
					m_2dRenderer->setRenderColour(1.0f, 1.0f, 1.0f, 1.0f);

				}
				else if (tttButton[y][x].getText() == "X") {
					//X
					int spacer = 32;
					m_2dRenderer->setRenderColour(1.0f, 0.0f, 0.0f, 1.0f);
					m_2dRenderer->drawLine(posXCenter - (getWindowWidth() / 3.0f / 2.0f) + spacer, posYCenter - (getWindowHeight() / 3.0f / 2.0f) + spacer, posXCenter + (getWindowWidth() / 3.0f / 2.0f) - spacer, posYCenter + (getWindowHeight() / 3.0f / 2.0f) - spacer, 20.0f, 0.5f);
					m_2dRenderer->drawLine(posXCenter - (getWindowWidth() / 3.0f / 2.0f) + spacer, posYCenter + (getWindowHeight() / 3.0f / 2.0f) - spacer, posXCenter + (getWindowWidth() / 3.0f / 2.0f) - spacer, posYCenter - (getWindowHeight() / 3.0f / 2.0f) + spacer, 20.0f, 0.5f);

				}

				tttButton[y][x].draw(m_2dRenderer, nullptr);
			}
		}

		//Print over the finished field
		if (currentState == over) {
			std::string gameOverText ="";
			m_2dRenderer->setRenderColour(1.0f, 1.0f, 1.0f, 1.0f);
			if (checkWinner(tttField) == -1) {
				gameOverText += "No one won!";
			}else if (checkWinner(tttField) == 1) {
				gameOverText += "Player one won!";
			}
			else {
				gameOverText += "Player two won!";
			}
			m_2dRenderer->drawText(m_font, gameOverText.c_str(), 12.0f, 64.0f,0.0f);
			m_2dRenderer->drawText(m_font,"Press space to play again!", 0.0f, 12.0f, 0.0f);
		}
	}
	else {


	}
	// done drawing sprites
	m_2dRenderer->end();
}



//Checks all possible win conditions and if all are filled. Returns the player that won 1,2 or -1 if no draw
int Application2D::checkWinner(tile ** field) {
	//1,1 checks
	int checking = field[0][0];
	if (checking != 0) {
		//V
		if (field[1][0] == checking && field[2][0] == checking)
			return checking;
		//H
		if (field[0][1] == checking && field[0][2] == checking)
			return checking;
		//D
		if (field[1][1] == checking && field[2][2] == checking)
			return checking;
	}
	//1,2 check
	checking = field[0][1];
	if (checking != 0) {
		//V
		if (field[1][1] == checking && field[2][1] == checking)
			return checking;
	}
	//1,3
	checking = field[0][2];
	if (checking != 0) {
		//V
		if (field[1][2] == checking && field[2][2] == checking)
			return checking;
	}
	//2,1
	checking = field[1][0];
	if (checking != 0) {
		//H
		if (field[1][1] == checking && field[1][2] == checking)
			return checking;
	}
	//3,1
	checking = field[2][0];
	if (checking != 0) {
		//H
		if (field[2][1] == checking && field[2][2] == checking)
			return checking;
		//D
		if (field[1][1] == checking && field[0][2] == checking)
			return checking;
	}
	if (   field[0][0] != 0 && field[0][1] != 0 && field[0][2] != 0 
		&& field[1][0] != 0 && field[1][1] != 0 && field[1][2] != 0 
		&& field[2][0] != 0 && field[2][1] != 0 && field[2][2] != 0) {
		return -1;
	}
	return 0;
}

//Make a temp field, and use checkWinner function to test if it can win in any of the 9 positions
bool Application2D::tryWin(tile ** field)
{
	tile ** tmp = new tile*[3];
	tmp[0] = new tile[3];
	tmp[1] = new tile[3];
	tmp[2] = new tile[3];
	for (int x = 0; x < 3; x++) {
		for (int y = 0; y < 3; y++) {
			tmp[x][y] = field[x][y];
		}
	}
	for (int x = 0; x < 3; x++) {
		for (int y = 0; y < 3; y++) {
			if (tmp[x][y] == 0) {
				tmp[x][y] = X;
				if (checkWinner(tmp) == 2) {
					field[x][y] = X;
					return true;
				}
				tmp[x][y] = _;
			}
		}
	}
	return false;
}

//Make a tmp field and use checkWinner function to test if player one can win at any position, if so take it
bool Application2D::counterWin(tile ** field)
{
	tile ** tmp = new tile*[3];
	tmp[0] = new tile[3];
	tmp[1] = new tile[3];
	tmp[2] = new tile[3];
	for (int x = 0; x < 3; x++) {
		for (int y = 0; y < 3; y++) {
			tmp[x][y] = field[x][y];
		}
	}
	for (int x = 0; x < 3; x++) {
		for (int y = 0; y < 3; y++) {
			if (tmp[x][y] == 0) {
				tmp[x][y] = O;
				if (checkWinner(tmp) == 1) {
					field[x][y] = X;
					return true;
				}
				tmp[x][y] = _;
			}
		}
	}
	return false;
}

//Place somewhere avaliable on board
bool Application2D::placeInRandPos(tile ** field)
{
	//Not rand just usng for tests
	for (int x = 0; x < 3; x++) {
		for (int y = 0; y < 3; y++) {
			if (field[x][y] == 0) {
				field[x][y] = X;
				return true;
			}
		}
	}
	return false;
}

