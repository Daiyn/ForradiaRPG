#include "Rectangle.h"

Rectangle::Rectangle(int _x, int _y, int _w, int _h)
{
	x = _x;
	y = _y;
	w = _w;
	h = _h;
}

Rectangle::Rectangle(Point startingPoint)
{
	x = startingPoint.m_x;
	y = startingPoint.m_y;
}

void Rectangle::Scale(double multiplier)
{
	x *= multiplier;
	y *= multiplier;
}

void Rectangle::Translate(int dx, int dy)
{
	x += dx;
	y += dy;
}

void Rectangle::SetSize(int _w, int _h)
{
	w = _w;
	h = _h;
}

void Rectangle::IncreaseSize(int dx, int dy)
{
	w += dx;
	h += dy;
}

bool Rectangle::ContainsPoint(Point p)
{
	return p.m_x >= x && p.m_y > y && p.m_x < x + w && p.m_y < y + h;

}