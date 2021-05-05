#include "CSize.h"

CSize::CSize(int _w, int _h)
{
	m_w = _w;
	m_h = _h;
}

CSize::CSize(double _w, double _h)
{
	m_w = int(_w);
	m_h = int(_h);
}

CSize::CSize(int size)
{
	m_w = size;
	m_h = size;
}

void CSize::Scale(double scale)
{
	m_w *= scale;
	m_h *= scale;
}
