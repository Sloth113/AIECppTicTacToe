#pragma once
#include <string>
#include "Renderer2D.h"


class Button {
private:
	int m_posX, m_posY;
	std::string m_text;
	int m_width, m_height;
	bool m_over;
	int m_gridX, m_gridY;//For tictactoe or gridbased clicking things
public:
	Button();
	Button(int, int, int, int, std::string);
	Button(int, int, int, int, std::string,int ,int);
	~Button();
	void draw(aie::Renderer2D *, aie::Font *);
	bool isCollision(int , int );
	bool isOver();
	void setOver(bool);
	std::string getText();
	void setText(std::string);
	int getGridX();
	int getGridY();
	

};
