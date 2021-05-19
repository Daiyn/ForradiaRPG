#include "Object.h"
#include "DataLoading.h"
#include "Point.h"
#include <SDL2/SDL_timer.h>

int Object::s_cntMaxObjectID = 0;

Object::Object(unsigned short _objectType, Point p)
{

    m_idxObjectType = _objectType;

    m_coordMapX = p.m_x;
    m_coordMapY = p.m_y;

    DataDescription& desc = *DataLoading::libDescriptions[_objectType];

    if (desc.ContainsProperty("TicksToVanish"))
        m_tickTimeToVanish = SDL_GetTicks() + std::stoi(desc.m_propAttributes["TicksToVanish"]);

    m_uniqueID = s_cntMaxObjectID;
    s_cntMaxObjectID++;

}

Object::Object(unsigned short _objectType, Point p, int _quantity)
{

    m_idxObjectType = _objectType;

    m_coordMapX = p.m_x;
    m_coordMapY = p.m_y;

    DataDescription& desc = *DataLoading::libDescriptions[_objectType];

    if (desc.ContainsProperty("TicksToVanish"))
        m_tickTimeToVanish = SDL_GetTicks() + std::stoi(desc.m_propAttributes["TicksToVanish"]);

    m_uniqueID = s_cntMaxObjectID;
    s_cntMaxObjectID++;

    m_propCurrentQuantity = _quantity;

}