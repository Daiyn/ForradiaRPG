#include "NpcRendering.h"
#include "ImageLoading.h"
#include "TextRendering.h"
#include "Global_CurrentMap.h"
#include "Global_Canvas.h"
#include "Global_SDL.h"
#include "Drawing.h"
#include "CMap.h"
#include "CTile.h"


void NPCRendering::RenderNpcs(int x, int y, CPoint pTile)
{

    auto TILESIZE = Global::GetTileSize();

    int seenFloorIndex = Global::currentMap->m_2DTiles[pTile.m_x][pTile.m_y]->GetIndexForSeenFloor();

    if (seenFloorIndex == -1)
        return;

    auto& FLOOR = Global::currentMap->m_2DTiles[pTile.m_x][pTile.m_y]->m_floorsArray[seenFloorIndex];


    if (FLOOR->HasNpcs())
    {
        for (int i = 0; i < FLOOR->m_npcs.size(); i++)
        {

            CNPC& npc = *FLOOR->m_npcs[i];

            int npcSize = 1.5 * TILESIZE;
            int shadowSize = 1.5 * TILESIZE;

            CRectangle rectShadow = {x * TILESIZE + TILESIZE / 2 - shadowSize / 2,
                                   y * TILESIZE + TILESIZE + TILESIZE / 2 -
                                   shadowSize, shadowSize, shadowSize };


            CRectangle rectNPC = {x * TILESIZE + TILESIZE / 2 - npcSize / 2,
                                y * TILESIZE + TILESIZE - npcSize, npcSize, npcSize };

            int textw = TextRendering::GetTextWidth(npc.m_nameCharacter);
            CPoint pNameText = { x * TILESIZE + TILESIZE / 2 - textw / 2 , rectNPC.y - 30 };
            
            Drawing::Image(ID_SHADOW, rectShadow);
            Drawing::Image(ID_NPC, rectNPC);
            TextRendering::DrawString(npc.m_nameCharacter, {255, 255, 255, 255}, pNameText);

            if (npc.m_stateCurrentActivity == CNPC::NPCActivites::StandingInPlazaTalkable)
            {

                int chatBubbleSize = TILESIZE * 2;

                CRectangle rectChatBubble = {x * TILESIZE + TILESIZE / 2,
                                           y * TILESIZE + TILESIZE - npcSize -
                                           chatBubbleSize, chatBubbleSize, chatBubbleSize};

                Drawing::Image(ID_CHAT_BUBBLE, rectChatBubble);

            }
        }
    }
}