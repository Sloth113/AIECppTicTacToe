#include "Application2D.h"
#include "Texture.h"
#include "Font.h"
#include "Input.h"
#include <iostream>
#include <string>


const int menuSize = 4;



Button* Application2D::buttonCollision(Button* checkIn, int size, int x, int y) {
	for (int i = 0; i < size; i++) {
		if (x > (*(checkIn + i)).getPosX() && x < (*(checkIn + i)).getPosX() + (*(checkIn + i)).getWidth() && y >(*(checkIn + i)).getPosY() &&  y < (*(checkIn + i)).getPosY()+ (*(checkIn + i)).getHeight()) {
			return (checkIn + i);
		}
	}
	return nullptr;
}

Button * Application2D::buttonCollision(Button ** checkIn, int rows, int col, int x, int y)
{
	
	for (int i = 0; i < rows; i++) {
		if(buttonCollision(checkIn[i], col, x, y) != nullptr)
			return buttonCollision(checkIn[i], col, x, y);
	}
	return nullptr;
}

bool Application2D::isCollision(Button* checkIn, int x, int y) {
	if (x >(*(checkIn)).getPosX() && x < (*(checkIn )).getPosX() + (*(checkIn )).getWidth() && y >(*(checkIn)).getPosY() &&  y < (*(checkIn )).getPosY() + (*(checkIn)).getHeight()) {
		return true;
	}
	return false;
}


Application2D::Application2D() {

}

Application2D::~Application2D() {

}

bool Application2D::startup() {

	m_2dRenderer = new aie::Renderer2D();

	m_font = new aie::Font("./font/consolas.ttf", 32);

	
	m_cameraX = 0;
	m_cameraY = 0;
	m_timer = 0;


	currentState = menu;
	menuButtons = new Button[menuSize];

	tttField = new int*[3];
	tttField[0] = new int[3];
	tttField[1] = new int[3];
	tttField[2] = new int[3];

	tttField[0][0] = 0;
	tttField[0][1] = 0;
	tttField[0][2] = 0;
	tttField[1][0] = 0;
	tttField[1][1] = 0;
	tttField[1][2] = 0;
	tttField[2][0] = 0;
	tttField[2][1] = 0;
	tttField[2][2] = 0;


	tttButton = new Button*[3];
	tttButton[0] = new Button[3];
	tttButton[1] = new Button[3];
	tttButton[2] = new Button[3];

	///Buttons
	/*
	menuButtons[0].posX = 34;
	menuButtons[0].posY = 32;
	menuButtons[0].widthX = 32 * 3 + 2;
	menuButtons[0].heightY = 34;
	//std::strcpy(menuButtons[0].text, "START");
	menuButtons[0].text = "START";
	


	menuButtons[1].posX = getWindowWidth() - (32 * 8 + 2) - 32 -16;
	menuButtons[1].posY = 32;
	menuButtons[1].widthX = 32 + 16;
	menuButtons[1].heightY = 34;
	//std::strcpy(menuButtons[1].text, "AI");
	menuButtons[1].text = "AI";

	menuButtons[2].posX = getWindowWidth() - (32 * 8 + 2);
	menuButtons[2].posY = 32;
	menuButtons[2].widthX = 32 * 7 + 2;
	menuButtons[2].heightY = 34;
	//std::strcpy(menuButtons[2].text, "PLAYER 2 = X");
	menuButtons[2].text = "PLAYER 2 = X";

	menuButtons[3].posX = getWindowWidth() - (32 * 8 + 2);
	menuButtons[3].posY = 74;
	menuButtons[3].widthX = 32 * 7 + 2;
	menuButtons[3].heightY = 34;
	//std::strcpy(menuButtons[3].text, "PLAYER 1 = O");
	menuButtons[3].text = "PLAYER 1 = O";
	*/

	//PosX,PosY,Width,Height,String
	menuButtons[0] = Button(34, 32, 32 * 3 + 2, 34, "START");
	menuButtons[1] = Button(getWindowWidth() - (32 * 8 + 2) - 32 - 16,32,32+16, 34, "AI");
	menuButtons[2] = Button(getWindowWidth() - (32 * 8 + 2), 32, 32 * 7 + 2, 34, "PLAYER 2 = X");
	menuButtons[3] = Button(getWindowWidth() - (32 * 8 + 2), 74, 32 * 7 + 2, 34, "PLAYER 1 = O");

	///ttt buttons
	for (int y = 0; y < 3; y++) {
		for (int x = 0; x < 3; x++) {
			/*
			tttButton[y][x].posX = (x * getWindowWidth() / 3) + 6;
			tttButton[y][x].posY = getWindowHeight() +6 - ((y + 1)*getWindowHeight() / 3);
			//std::strcpy(tttButton[y][x].text,"-");
			tttButton[y][x].text=  "-";
			tttButton[y][x].widthX = getWindowWidth() / 3;
			tttButton[y][x].heightY = getWindowHeight() / 3;
			tttButton[y][x].over = false;
			tttButton[y][x].gridY = y;
			tttButton[y][x].gridX = x;
			*/
			std::string posTag;// = "Pos:" + x + "," + "y";
			posTag = "pos:" + x;
			posTag += "," + y;
			tttButton[y][x] = Button((x * getWindowWidth() / 3) + 6, getWindowHeight() + 6 - ((y + 1)*getWindowHeight() / 3), getWindowWidth() / 3, getWindowHeight() / 3, "-", posTag, x,y);



		}
	}


	ai = false;
	playerTurn = 1;
	difficulty = 0;
	p1Score = 0;
	p2Score = 0;

	return true;
}

void Application2D::shutdown() {

	delete m_2dRenderer;

	delete m_font;

//	delete menuButtons;
//	for (int i = 0; i < 3; i++) {
//		(*tttButton[i]).text.clear();
//		delete tttButton[i];
//	}
//	delete[] tttButton;
	delete tttField;
}

void Application2D::update(float deltaTime) {

	//m_timer += deltaTime;

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

	if (currentState == menu) {
		//Menu options
		Button * pressedButtom = buttonCollision(menuButtons, menuSize, input->getMouseX(), input->getMouseY());
		if (pressedButtom != nullptr)
			(*pressedButtom).setOver(true);

		if (input->wasMouseButtonPressed(0)) {
			Button * pressedButtom = buttonCollision(menuButtons, menuSize, input->getMouseX(), input->getMouseY());
			if (pressedButtom != nullptr)
				/*
				if (std::strcmp((*pressedButtom).text, "START") == 0) {
				*/
				if ((*pressedButtom).getText() == "START") {
					currentState = playing;
				}
				else if ((*pressedButtom).getText() == "AI") {
				//else if (std::strcmp((*pressedButtom).text, "AI") == 0) {
					if (ai) {
						ai = false;
						difficulty = 0;
					}
					else ai = true;
				}
				/*else if (std::strcmp((*pressedButtom).text, "PLAYER 2 = X") == 0) {
				}
				else if (std::strcmp((*pressedButtom).text, "PLAYER 1 = O") == 0){
					
				}else{
				
				}
				*/
		}
	}
	else if (currentState == playing) {
		if (playerTurn == 2 && ai) {
			//Ais turn
			if (tryWin(tttField)) {
				playerTurn = 1;
			}
			else {
				if (counterWin(tttField)) {
					playerTurn = 1;
				}
				else {
					if (placeInRandPos(tttField)) {
						playerTurn = 1;
					}
				}
			}
			if (checkWinner(tttField) == 1 || checkWinner(tttField) == 2 || checkWinner(tttField) == -1) {
				currentState = over;
			}




		}
		else {

			//Players input checks 
			Button * pressedButtom = buttonCollision(tttButton, 3, 3, input->getMouseX(), input->getMouseY());

			if (pressedButtom != nullptr)(*pressedButtom).setOver(true);

			if (input->wasMouseButtonPressed(0)) {
				Button * pressedButtom = buttonCollision(tttButton, 3, 3, input->getMouseX(), input->getMouseY());
				//if (pressedButtom != nullptr && std::strcmp((*pressedButtom).text, "-") == 0) {
				if (pressedButtom != nullptr && (*pressedButtom).getText() == "-") {
					if (playerTurn == 1) {

						//std::strcpy(tttButton[(*pressedButtom).gridY][(*pressedButtom).gridX].text, "O");
						//tttButton[(*pressedButtom).getGridY()][(*pressedButtom).getGridX()].setText("O");
						tttField[(*pressedButtom).getGridY()][(*pressedButtom).getGridX()] = 1;
						playerTurn = 2;
					}
					else {
						//std::strcpy(tttButton[(*pressedButtom).gridY][(*pressedButtom).gridX].text, "X");
						//tttButton[(*pressedButtom).getGridY()][(*pressedButtom).getGridX()].setText("X");
						playerTurn = 1;
						tttField[(*pressedButtom).getGridY()][(*pressedButtom).getGridX()] = 2;
					}
					if (checkWinner(tttField) == 1 || checkWinner(tttField) == 2 || checkWinner(tttField) == -1) {
						currentState = over;
					}

				}
			}
		}

		for (int x = 0; x < 3; x++) {
			for (int y = 0; y < 3; y++) {
				if(tttField[x][y] == 1) tttButton[x][y].setText("O");
				if (tttField[x][y] == 2) tttButton[x][y].setText("X");
				if (tttField[x][y] == 0) tttButton[x][y].setText("-");
			}
		}
		



	}



	if (currentState == over) {
		
		if (input->isKeyDown(aie::INPUT_KEY_SPACE)) {
			currentState = menu;
			if (checkWinner(tttField) == 2) {
				p2Score += 10;
			}else if(checkWinner(tttField) == 1){
				p1Score += 10;
				if (ai) {
					difficulty++;
				}
			}
			
			for (int y = 0; y < 3; y++) {
				//Reset field
				for (int x = 0; x < 3; x++) {
					tttField[y][x] = 0;
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
			//char * stringToChar = menuButtons[i].text;
			
			m_2dRenderer->setRenderColour(0.5f, 0.5f, 0.5f, 0.5f);
			m_2dRenderer->drawBox(menuButtons[i].getPosX() + menuButtons[i].getWidth() / 2 - 5.0f, menuButtons[i].getPosY() + menuButtons[i].getHeight() / 2 - 5.0f, menuButtons[i].getWidth()*1.0f, menuButtons[i].getHeight()*1.0f , 0.0f);
			
			//Mouse over box
			if (menuButtons[i].isOver()) {
				m_2dRenderer->setRenderColour(0.7f, 0.7f, 0.7f, 0.5f);
				m_2dRenderer->drawBox(menuButtons[i].getPosX() + menuButtons[i].getWidth() / 2 - 5.0f, menuButtons[i].getPosY() + menuButtons[i].getHeight() / 2 - 5.0f, menuButtons[i].getWidth()*1.0f, menuButtons[i].getHeight()*1.0f, 0.0f);
			}
			//Darken AI button to show selection 
			//if (std::strcmp(menuButtons[i].text, "AI") == 0 && ai) {
			if (menuButtons[i].getText() == "AI" && ai) {
				m_2dRenderer->setRenderColour(0.8f, 0.2f, 0.2f, 0.5f);
				m_2dRenderer->drawBox(menuButtons[i].getPosX() + menuButtons[i].getWidth() / 2 - 5, menuButtons[i].getPosY() + menuButtons[i].getHeight() / 2 - 5, menuButtons[i].getWidth(), menuButtons[i].getHeight(), 0.0f);
			}
			//Darken player 2 to help show AI on.
			if (menuButtons[i].getText() == "PLAYER 2 = X"  && ai) {
				m_2dRenderer->setRenderColour(0.0f, 0.f, 0.f, 0.9f);
				m_2dRenderer->drawBox(menuButtons[i].getPosX() + menuButtons[i].getWidth() / 2 - 5, menuButtons[i].getPosY() + menuButtons[i].getHeight() / 2 - 5, menuButtons[i].getWidth(), menuButtons[i].getHeight(), 0);
			}
			//Text & text colour
			m_2dRenderer->setRenderColour(1, 1, 1, 1);
			m_2dRenderer->drawText(m_font, menuButtons[i].getText().c_str(), menuButtons[i].getPosX(), menuButtons[i].getPosY());


		}
		//Title
		m_2dRenderer->drawText(m_font, "TicTacToe", 0, getWindowHeight() - 32);

		


	}
	else if (currentState == playing || currentState == over) {
		//Print out buttons, grid and ui

		//Lines for grid
		//Horiz
		m_2dRenderer->drawLine(0, getWindowHeight() / 3, getWindowWidth(), getWindowHeight() / 3, 4, 1);
		m_2dRenderer->drawLine(0, 2 * getWindowHeight() / 3, getWindowWidth(), 2 * getWindowHeight() / 3, 4, 1);
		//Vert
		m_2dRenderer->drawLine(getWindowWidth() / 3, 0, getWindowWidth() / 3, getWindowHeight(), 4, 1);
		m_2dRenderer->drawLine(2 * getWindowWidth() / 3, 0, 2 * getWindowWidth() / 3, getWindowHeight(), 4, 1);
		


		int posXCenter = 0;
		int posYCenter = 0;
		for (int y = 0; y < 3; y++) {
			for (int x = 0; x < 3; x++) {
				//           Displacement                  top left position
				posXCenter = (x * getWindowWidth() / 3) + (getWindowWidth() / 3 - (getWindowWidth() / 3 / 2));
				//			 -Displaced					  top left position
				posYCenter = getWindowWidth() - (y*getWindowHeight() / 3) - (getWindowWidth() / 3 / 2);

				//if (std::strcmp(tttButton[y][x].text, "-") == 0) {
				if (tttButton[y][x].getText() == "-") {
					//DOT

					m_2dRenderer->setRenderColour(1, 1, 1, 1);
					m_2dRenderer->drawCircle(posXCenter, posYCenter, 5, 0.5f);
				//}else if(std::strcmp(tttButton[y][x].text, "O") == 0){
				}
				else if (tttButton[y][x].getText() == "O") {
					//O
					m_2dRenderer->setRenderColour(0, 0, 1, 1);
					m_2dRenderer->drawCircle(posXCenter, posYCenter, 50, 0.5f);
					m_2dRenderer->setRenderColour(0, 0, 0, 1);
					m_2dRenderer->drawCircle(posXCenter, posYCenter, 30, 0.5f);
					//Reset render colour to white
					m_2dRenderer->setRenderColour(1, 1, 1, 1);

				//}else if(std::strcmp(tttButton[y][x].text, "X") == 0){
				}
				else if (tttButton[y][x].getText() == "X") {
					//X
					int spacer = 32;
					m_2dRenderer->setRenderColour(1, 0, 0, 1);
					m_2dRenderer->drawLine(posXCenter - (getWindowWidth() / 3 / 2) + spacer, posYCenter - (getWindowHeight() / 3 / 2) + spacer, posXCenter + (getWindowWidth() / 3 / 2) - spacer, posYCenter + (getWindowHeight() / 3 / 2) - spacer, 20.0f, 0.5f);
					m_2dRenderer->drawLine(posXCenter - (getWindowWidth() / 3 / 2) + spacer, posYCenter + (getWindowHeight() / 3 / 2) - spacer, posXCenter + (getWindowWidth() / 3 / 2) - spacer, posYCenter - (getWindowHeight() / 3 / 2) + spacer, 20.0f, 0.5f);

				}else{
				 //Something should never get here 
				}
				if (tttButton[y][x].isOver())m_2dRenderer->setRenderColour(1, 1, 1, 0.5);
				else m_2dRenderer->setRenderColour(1, 1, 1, 0.2f);
				m_2dRenderer->drawBox(tttButton[y][x].getPosX() + tttButton[y][x].getWidth() / 2 - 5, tttButton[y][x].getPosY() + tttButton[y][x].getHeight() / 2 - 5, tttButton[y][x].getWidth(), tttButton[y][x].getHeight(), 0, 0);

			}
		}

		//Print over the field
		if (currentState == over) {
			std::string gameOverText ="";
			m_2dRenderer->setRenderColour(1, 1, 1, 1);
			if (checkWinner(tttField) == -1) {
				gameOverText += "No one won!";
			}else if (checkWinner(tttField) == 1) {
				gameOverText += "Player one won!";
			}
			else {
				gameOverText += "Player two won!";
			}
			m_2dRenderer->drawText(m_font, gameOverText.c_str(), 12, 64,0);
			m_2dRenderer->drawText(m_font,"Press space to play again!", 0, 12, 0);
		}
	}
	else {


	}
	// done drawing sprites
	m_2dRenderer->end();
}



int Application2D::checkWinner(int ** field) {
	//Checks all possible win conditions and if all are filled. Returns the player that won 1,2 or -1 if no draw
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

bool Application2D::tryWin(int ** field)
{
	int ** tmp = new int*[3];
	tmp[0] = new int[3];
	tmp[1] = new int[3];
	tmp[2] = new int[3];
	for (int x = 0; x < 3; x++) {
		for (int y = 0; y < 3; y++) {
			tmp[x][y] = field[x][y];
		}
	}
	for (int x = 0; x < 3; x++) {
		for (int y = 0; y < 3; y++) {
			if (tmp[x][y] == 0) {
				tmp[x][y] = 2;
				if (checkWinner(tmp) == 2) {
					field[x][y] = 2;
					return true;
				}
				tmp[x][y] = 0;
			}
		}
	}
	return false;
}

bool Application2D::counterWin(int ** field)
{
	int ** tmp = new int*[3];	
	tmp[0] = new int[3];
	tmp[1] = new int[3];
	tmp[2] = new int[3];
	for (int x = 0; x < 3; x++) {
		for (int y = 0; y < 3; y++) {
			tmp[x][y] = field[x][y];
		}
	}
	for (int x = 0; x < 3; x++) {
		for (int y = 0; y < 3; y++) {
			if (tmp[x][y] == 0) {
				tmp[x][y] = 1;
				if (checkWinner(tmp) == 1) {
					field[x][y] = 2;
					return true;
				}
				tmp[x][y] = 0;
			}
		}
	}
	return false;
}

bool Application2D::placeInGoodPos(int ** field)
{
	return false;
}

bool Application2D::placeInRandPos(int ** field)
{
	//Not rand just usng for tests
	for (int x = 0; x < 3; x++) {
		for (int y = 0; y < 3; y++) {
			if (field[x][y] == 0) {
				field[x][y] = 2;
				return true;
			}
		}
	}
	return false;
}

