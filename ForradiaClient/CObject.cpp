#include "CObject.h"
#include "DataLoading.h"
#include "CPoint.h"
#include <SDL2/SDL_timer.h>

int CObject::s_cntMaxObjectID = 0;

CObject::CObject(unsigned short _objectType, CPoint p)
{

    m_idxObjectType = _objectType;

    m_coordMapX = p.m_x;
    m_coordMapY = p.m_y;

    CDataDescription& desc = *DataLoading::libDescriptions[_objectType];

    if (desc.ContainsProperty("TicksToVanish"))
        m_tickTimeToVanish = SDL_GetTicks() + std::stoi(desc.m_propAttributes["TicksToVanish"]);

    m_uniqueID = s_cntMaxObjectID;
    s_cntMaxObjectID++;

}

CObject::CObject(unsigned short _objectType, CPoint p, int _quantity)
{

    m_idxObjectType = _objectType;

    m_coordMapX = p.m_x;
    m_coordMapY = p.m_y;

    CDataDescription& desc = *DataLoading::libDescriptions[_objectType];

    if (desc.ContainsProperty("TicksToVanish"))
        m_tickTimeToVanish = SDL_GetTicks() + std::stoi(desc.m_propAttributes["TicksToVanish"]);

    m_uniqueID = s_cntMaxObjectID;
    s_cntMaxObjectID++;

    m_propCurrentQuantity = _quantity;

}