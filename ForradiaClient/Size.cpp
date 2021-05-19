#include "Size.h"

Size::Size(int _w, int _h)
{
	m_w = _w;
	m_h = _h;
}

Size::Size(double _w, double _h)
{
	m_w = int(_w);
	m_h = int(_h);
}

Size::Size(int size)
{
	m_w = size;
	m_h = size;
}

void Size::Scale(double scale)
{
	m_w *= scale;
	m_h *= scale;
}
