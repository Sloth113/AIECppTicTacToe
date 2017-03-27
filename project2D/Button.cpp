#include "Button.h"

//My button class
Button::Button()
{

	m_posX = 0;
	m_posY = 0;
	m_width = 1;
	m_height = 1;
	m_text = "";
	m_over = false;
}

Button::Button(int x, int y, int width, int height, std::string text)
{
	m_posX = x;
	m_posY = y;
	m_width = width;
	m_height = height;
	m_text = text;
	
	m_over = false;
}

Button::Button(int x, int y, int width, int height, std::string text, int gridX, int gridY)
{

	m_posX = x;
	m_posY = y;
	m_width = width;
	m_height = height;
	m_text = text;
	m_over = false;
	m_gridX = gridX;
	m_gridY = gridY;
}

Button::~Button()
{
}

void Button::draw(aie::Renderer2D * renderer, aie::Font * font)
{
	if(m_over)
		renderer->setRenderColour(0.7f, 0.7f, 0.7f, 0.5f);
	else
		renderer->setRenderColour(0.5f, 0.5f, 0.5f, 0.5f);
	//Draw with offsets 
	renderer->drawBox(m_posX + m_width / 2 - 5.0f, m_posY + m_height / 2 - 5.0f, m_width*1.0f, m_height*1.0f, 0.0f);
	//Text & text colour
	renderer->setRenderColour(1, 1, 1, 1);
	//No text
	if(font != nullptr)
	renderer->drawText(font, m_text.c_str(),m_posX*1.0f, m_posY*1.0f);

}

bool Button::isCollision(int x, int y)
{
	//Check if the co-ords are within the bound box
	if (x >m_posX && x < m_posX + m_width && y >m_posY && y < m_posY + m_height) {
		return true;
	}
	return false;
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

int Button::getGridX()
{
	return m_gridX;
}

int Button::getGridY()
{
	return m_gridY;
}
