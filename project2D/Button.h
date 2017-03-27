#pragma once
#include <string>


class Button {
private:
	int m_posX, m_posY;
	std::string m_text;
	std::string m_tag;
	int m_width, m_height;
	bool m_over;
	int m_gridX, m_gridY;//For tictactoe or gridbased clicking things
public:
	Button();
	Button(int, int, int, int, std::string);
	Button(int, int, int, int, std::string,std::string,int ,int);
	~Button();
	int getPosX();
	int getPosY();
	int getWidth();
	int getHeight();
	bool isOver();
	void setOver(bool);
	std::string getText();
	void setText(std::string);
	std::string getTag();
	int getGridX();
	int getGridY();
	

};
