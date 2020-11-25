#pragma once
#include "Texture.h"

class Button
{
public:
	Button(int _x, int _y, Texture& _texture);
	~Button();
	void Render();
	void OnHover();
	void OnClick();
	bool IsInside(int _xMouse, int _yMouse);

private:
	bool CheckBounds(int x, int y, int xMin, int yMin, int xMax, int yMax);

private:
	int m_x;
	int m_y;

	Texture& m_texture;
	SDL_Cursor* m_cursor;
};

