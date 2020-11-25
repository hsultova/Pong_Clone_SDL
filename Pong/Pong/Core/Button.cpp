#include "Button.h"

Button::Button(int _x, int _y, Texture& _texture)
	:m_x(_x), m_y(_y), m_texture(_texture)
{	
}

Button::~Button()
{
}

void Button::Render()
{
	m_texture.Render(m_x, m_y);
}

void Button::OnHover()
{
	m_cursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_HAND);
	SDL_SetCursor(m_cursor);
}

void Button::OnClick()
{
}

bool Button::IsInside(int _xMouse, int _yMouse)
{
	return CheckBounds(_xMouse, _yMouse, m_x, m_y, m_x + m_texture.GetWidth(), m_y + m_texture.GetHeight());
}

bool Button::CheckBounds(int x, int y, int xMin, int yMin, int xMax, int yMax)
{
	return (x < xMax&& x > xMin) && (y < yMax&& y > yMin);
}
