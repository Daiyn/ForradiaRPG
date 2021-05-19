#include "Point.h"
#include "Global_Player.h"
#include "Global_Canvas.h"
#include "Utilities.h"
#include "Global_MapSize.h"
#include <stdlib.h>
#include "Player.h"
#include "Global_CurrentMap.h"
#include "Map.h"

Point::Point(int _x, int _y)
{
	m_x = _x;
	m_y = _y;
}

Point::Point(int flags)
{
	m_x = 0;
	m_y = 0;

	if ((flags & RANDOM_WITHIN_MAP) != 0)
	{
		m_x = rand() % Global::tilesMapSize;
		m_y = rand() % Global::tilesMapSize;
	}

	if ((flags & MAP_CENTER) != 0)
	{
		m_x = Global::tilesMapSize / 2;
		m_y = Global::tilesMapSize / 2;
	}

	if ((flags & HOVERED_TILE) != 0)
	{
		m_x = Utilities::GetHoveredMapx();
		m_y = Utilities::GetHoveredMapy();
	}
}

void Point::JumpToHoveredTile()
{

	m_x = Global::statePlayer->m_coordPosition.m_x - (Global::GetNumberOfColumns() - 1) / 2 + Utilities::GetHoveredScreenMapx();
	m_y = Global::statePlayer->m_coordPosition.m_y - (Global::tilesNumberOfRows - 1) / 2 + Utilities::GetHoveredScreenMapy();

}

void Point::JumpToScreenStart()
{
	m_x = XSCREENSTART;
	m_y = YSCREENSTART;
}

void Point::JumpRight()
{
	m_x++;
}

void Point::JumpToNextRowStart()
{
	m_x = XSCREENSTART;
	m_y++;
}

void Point::Translate(int dx, int dy)
{
	m_x += dx;
	m_y += dy;
}

bool Point::WithinMap()
{
	return m_x >= 0 && m_y >= 0 && m_x < Global::tilesMapSize && m_y < Global::tilesMapSize;
}

bool Point::Equals(Point p)
{
	return m_x == p.m_x && m_y == p.m_y;
}
