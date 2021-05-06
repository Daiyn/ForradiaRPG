#include "CWindowInventory.h"
#include "Global_Mouse.h"
#include "Drawing.h"
#include "Global_Player.h"
#include "ItemMoving.h"
#include "TextRendering.h"
#include "Colors.h"
#include "Constants.h"
#include "CDataDescription.h"
#include "CPlayer.h"
#include <memory>

using std::unique_ptr;
using std::move;

CWindowInventory::CWindowInventory()
{

    m_attrTitle = "Inventory";

    m_x = 200;
    m_y = 200;
    m_w = 400;
    m_h = 700;

}

bool CWindowInventory::HandleMouseClickInWindow()
{

    bool baseResult = HandleMouseClickInWindowBase();

    int mx = Global::GetMouseX();
    int my = Global::GetMouseY();

    int numCols = m_w / (m_pxSlotSize + m_pxMargin);
    int numberOfRows = (m_h - m_pxTitleBarHeight) / (m_pxSlotSize + m_pxMargin);

    int xoffset = (m_w - m_w / (m_pxSlotSize + m_pxMargin) * (m_pxSlotSize + m_pxMargin)) / 2;
    int yoffset = (m_h - m_h / (m_pxSlotSize + m_pxMargin) * (m_pxSlotSize + m_pxMargin)) / 2;

    int i = 0;

    bool objectIsBeingPickedUp = false;

    for (int row = 0; row < numberOfRows; row++)
    {

        for (int col = 0; col < numCols; col++)
        {

            int posx = m_x + xoffset + col*(m_pxSlotSize + m_pxMargin);
            int posy = m_y + m_pxTitleBarHeight + yoffset + row*(m_pxSlotSize + m_pxMargin);

            if (mx >= posx && my >= posy && mx < posx + m_pxSlotSize && my < posy + m_pxSlotSize)
            {

                for (auto it = Global::statePlayer->m_inventory.m_containedItems.begin(); it != Global::statePlayer->m_inventory.m_containedItems.end(); it++)
                {

                    if (it->first == i)
                    {

                        ItemMoving::nodupMovedObject = move(it->second);
                        ItemMoving::nodupMovedObject->m_coordMapX = OBJECT_IN_AIR_OR_INVENTORY;
                        ItemMoving::nodupMovedObject->m_coordMapY = OBJECT_IN_AIR_OR_INVENTORY;
                        objectIsBeingPickedUp = true;

                        break;

                    }

                }

                if (objectIsBeingPickedUp)
                    Global::statePlayer->m_inventory.m_containedItems.erase(i);

            }

            i++;

        }
    }

    return baseResult;

}

bool CWindowInventory::HandleMouseReleaseInWindow()
{

    bool resultBase = HandleMouseReleaseInWindowBase();

    int mx = Global::GetMouseX();
    int my = Global::GetMouseY();

    int numCols = m_w / (m_pxSlotSize + m_pxMargin);
    int numberOfRows = (m_h - m_pxTitleBarHeight) / (m_pxSlotSize + m_pxMargin);

    int xoffset = (m_w - m_w / (m_pxSlotSize + m_pxMargin) * (m_pxSlotSize + m_pxMargin)) / 2;
    int yoffset = (m_h - m_h / (m_pxSlotSize + m_pxMargin) * (m_pxSlotSize + m_pxMargin)) / 2;

    int i = 0;

    for (int row = 0; row < numberOfRows; row++)
    {

        for (int col = 0; col < numCols; col++)
        {

            int posx = m_x + xoffset + col*(m_pxSlotSize + m_pxMargin);
            int posy = m_y + m_pxTitleBarHeight + yoffset + row*(m_pxSlotSize + m_pxMargin);

            if (mx >= posx && my >= posy && mx < posx + m_pxSlotSize && my < posy + m_pxSlotSize)
            {

                if (Global::statePlayer->m_inventory.SlotIsOccupied(i))
                {
                    if (Global::statePlayer->m_inventory.m_containedItems[i]->m_idxObjectType == ItemMoving::nodupMovedObject->m_idxObjectType)
                    {
                        Global::statePlayer->m_inventory.m_containedItems[i]->m_propCurrentQuantity += ItemMoving::nodupMovedObject->m_propCurrentQuantity;
                        ItemMoving::nodupMovedObject.reset();
                        return true;
                    }
                }

                Global::statePlayer->m_inventory.m_containedItems.insert(std::pair<int, unique_ptr<CObject>>(i, move(ItemMoving::nodupMovedObject)));
                return true;

            }

            i++;

        }

    }

    return resultBase;

}

void CWindowInventory::Render()
{

    RenderBase();

    int numCols = m_w / (m_pxSlotSize + m_pxMargin);
    int numberOfRows = (m_h - m_pxTitleBarHeight) / (m_pxSlotSize + m_pxMargin);

    int xoffset = (m_w - m_w / (m_pxSlotSize + m_pxMargin) * (m_pxSlotSize + m_pxMargin)) / 2;
    int yoffset = ((m_h - m_pxTitleBarHeight) - (m_h - m_pxTitleBarHeight) / (m_pxSlotSize + m_pxMargin) * (m_pxSlotSize + m_pxMargin)) / 2;

    int i = 0;

    for (int row = 0; row < numberOfRows; row++)
    {

        for (int col = 0; col < numCols; col++)
        {

            int posx = m_x + xoffset + col*(m_pxSlotSize + m_pxMargin);
            int posy = m_y + m_pxTitleBarHeight + yoffset + row*(m_pxSlotSize + m_pxMargin);

            Drawing::Image(kIDInventorySlotBackground, posx, posy, m_pxSlotSize, m_pxSlotSize);

            for (auto it = Global::statePlayer->m_inventory.m_containedItems.begin(); it != Global::statePlayer->m_inventory.m_containedItems.end(); it++)
            {

                if (it->first == i) 
                {

                    CDataDescription *desc;

                    Drawing::Image(it->second->m_idxObjectType, posx, posy, m_pxSlotSize, m_pxSlotSize);

                    if (it->second->m_propCurrentQuantity > 1)
                    {
                        TextRendering::DrawString(std::to_string(it->second->m_propCurrentQuantity), BLACK, posx + m_pxSlotSize/10, posy + m_pxSlotSize/10);
                    }

                    break;
                }
            }

            i++;

        }

    }

}
