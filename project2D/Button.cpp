#include "Button.h"

Button::Button()
{

	m_posX = 0;
	m_posY = 0;
	m_width = 1;
	m_height = 1;
	m_text = "";
	m_tag = "";
	m_over = false;
}

Button::Button(int x, int y, int width, int height, std::string text)
{
	m_posX = x;
	m_posY = y;
	m_width = width;
	m_height = height;
	m_text = text;
	m_tag = text;
	m_over = false;
}

Button::Button(int x, int y, int width, int height, std::string text, std::string tag, int gridX, int gridY)
{

	m_posX = x;
	m_posY = y;
	m_width = width;
	m_height = height;
	m_text = text;
	m_tag = tag;
	m_over = false;
	m_gridX = gridX;
	m_gridY = gridY;
}

Button::~Button()
{
}

int Button::getPosX()
{
	return m_posX;
}

int Button::getPosY()
{
	return m_posY;
}

int Button::getWidth()
{
	return m_width;
}

int Button::getHeight()
{
	return m_height;
}

bool Button::isOver()
{
	return m_over;
}

void Button::setOver(bool state)
{
	m_over = state;
}

std::string Button::getText()
{
	return m_text;
}

void Button::setText(std::string in)
{
	m_text = in;
}

std::string Button::getTag()
{
	return m_tag;
}

int Button::getGridX()
{
	return m_gridX;
}

int Button::getGridY()
{
	return m_gridY;
}
