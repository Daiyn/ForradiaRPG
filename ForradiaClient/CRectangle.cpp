#include "CRectangle.h"

CRectangle::CRectangle(int _x, int _y, int _w, int _h)
{
	x = _x;
	y = _y;
	w = _w;
	h = _h;
}

CRectangle::CRectangle(CPoint startingPoint)
{
	x = startingPoint.m_x;
	y = startingPoint.m_y;
}

void CRectangle::Scale(double multiplier)
{
	x *= multiplier;
	y *= multiplier;
}

void CRectangle::Translate(int dx, int dy)
{
	x += dx;
	y += dy;
}

void CRectangle::SetSize(int _w, int _h)
{
	w = _w;
	h = _h;
}

void CRectangle::IncreaseSize(int dx, int dy)
{
	w += dx;
	h += dy;
}

bool CRectangle::ContainsPoint(CPoint p)
{
	return p.m_x >= x && p.m_y > y && p.m_x < x + w && p.m_y < y + h;

}