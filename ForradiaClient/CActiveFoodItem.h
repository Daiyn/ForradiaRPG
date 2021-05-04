#pragma once

#include "CObject.h"
#include <memory>

using std::unique_ptr;


class CActiveFoodItem
{
public:
	unique_ptr<CObject> m_foodItem;
	int m_tickCreated = 0;

	CActiveFoodItem(unique_ptr<CObject> foodItem);
};

