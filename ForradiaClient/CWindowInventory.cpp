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

    m_title = "Inventory";

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

    int numCols = m_w / (m_slotSize + m_margin);
    int numberOfRows = (m_h - m_titleBarHeight) / (m_slotSize + m_margin);

    int xoffset = (m_w - m_w / (m_slotSize + m_margin) * (m_slotSize + m_margin)) / 2;
    int yoffset = (m_h - m_h / (m_slotSize + m_margin) * (m_slotSize + m_margin)) / 2;

    int i = 0;

    bool objectIsBeingPickedUp = false;

    for (int row = 0; row < numberOfRows; row++)
    {

        for (int col = 0; col < numCols; col++)
        {

            int posx = m_x + xoffset + col*(m_slotSize + m_margin);
            int posy = m_y + m_titleBarHeight + yoffset + row*(m_slotSize + m_margin);

            if (mx >= posx && my >= posy && mx < posx + m_slotSize && my < posy + m_slotSize)
            {

                for (auto it = Global::player->m_inventory.m_belongingCollection.begin(); it != Global::player->m_inventory.m_belongingCollection.end(); it++)
                {

                    if (it->first == i)
                    {

                        ItemMoving::objectInAir = move(it->second);
                        ItemMoving::objectInAir->m_2DMapX = OBJECT_IN_AIR_OR_INVENTORY;
                        ItemMoving::objectInAir->m_2DMapY = OBJECT_IN_AIR_OR_INVENTORY;
                        objectIsBeingPickedUp = true;

                        break;

                    }

                }

                if (objectIsBeingPickedUp)
                    Global::player->m_inventory.m_belongingCollection.erase(i);

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

    int numCols = m_w / (m_slotSize + m_margin);
    int numberOfRows = (m_h - m_titleBarHeight) / (m_slotSize + m_margin);

    int xoffset = (m_w - m_w / (m_slotSize + m_margin) * (m_slotSize + m_margin)) / 2;
    int yoffset = (m_h - m_h / (m_slotSize + m_margin) * (m_slotSize + m_margin)) / 2;

    int i = 0;

    for (int row = 0; row < numberOfRows; row++)
    {

        for (int col = 0; col < numCols; col++)
        {

            int posx = m_x + xoffset + col*(m_slotSize + m_margin);
            int posy = m_y + m_titleBarHeight + yoffset + row*(m_slotSize + m_margin);

            if (mx >= posx && my >= posy && mx < posx + m_slotSize && my < posy + m_slotSize)
            {

                if (Global::player->m_inventory.SlotIsOccupied(i))
                {
                    if (Global::player->m_inventory.m_belongingCollection[i]->m_idxObjectType == ItemMoving::objectInAir->m_idxObjectType)
                    {
                        Global::player->m_inventory.m_belongingCollection[i]->m_qtyCurrent += ItemMoving::objectInAir->m_qtyCurrent;
                        ItemMoving::objectInAir.reset();
                        return true;
                    }
                }

                Global::player->m_inventory.m_belongingCollection.insert(std::pair<int, unique_ptr<CObject>>(i, move(ItemMoving::objectInAir)));
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

    int numCols = m_w / (m_slotSize + m_margin);
    int numberOfRows = (m_h - m_titleBarHeight) / (m_slotSize + m_margin);

    int xoffset = (m_w - m_w / (m_slotSize + m_margin) * (m_slotSize + m_margin)) / 2;
    int yoffset = ((m_h - m_titleBarHeight) - (m_h - m_titleBarHeight) / (m_slotSize + m_margin) * (m_slotSize + m_margin)) / 2;

    int i = 0;

    for (int row = 0; row < numberOfRows; row++)
    {

        for (int col = 0; col < numCols; col++)
        {

            int posx = m_x + xoffset + col*(m_slotSize + m_margin);
            int posy = m_y + m_titleBarHeight + yoffset + row*(m_slotSize + m_margin);

            Drawing::Image(ID_INVENTORY_SLOT_BACK, posx, posy, m_slotSize, m_slotSize);

            for (auto it = Global::player->m_inventory.m_belongingCollection.begin(); it != Global::player->m_inventory.m_belongingCollection.end(); it++)
            {

                if (it->first == i) 
                {

                    CDataDescription *desc;

                    Drawing::Image(it->second->m_idxObjectType, posx, posy, m_slotSize, m_slotSize);

                    if (it->second->m_qtyCurrent > 1)
                    {
                        TextRendering::DrawString(std::to_string(it->second->m_qtyCurrent), BLACK, posx + m_slotSize/10, posy + m_slotSize/10);
                    }

                    break;
                }
            }

            i++;

        }

    }

}
