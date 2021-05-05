#include "ObjectsRendering.h"
#include "PlayerActions.h"
#include "ImageLoading.h"
#include "DataLoading.h"
#include "Global_CurrentMap.h"
#include "Global_Canvas.h"
#include "Global_Player.h"
#include <SDL2/SDL_timer.h>
#include "Global_SDL.h"
#include "TextRendering.h"
#include "Drawing.h"
#include "Global_mapSize.h"
#include "Global_Mouse.h"
#include "CSize.h"
#include "CTile.h"
#include "Animations.h"

using Global::contentCurrentMap;

void ObjectsRendering::RenderTileObjects(double tileSize, int x, int y, CPoint pTile)
{

    int tileSizeCeil = ceil(tileSize);
    auto TILESIZE = tileSizeCeil;
    auto& PLAYER = Global::statePlayer;

    int seenFloorIndex = contentCurrentMap->m_tilesGrid[pTile.m_x][pTile.m_y]->GetIndexForSeenFloor();

    if (seenFloorIndex == -1)
        return;

    CRectangle rTile = { int(x * tileSize), int(y * tileSize), TILESIZE, TILESIZE };

    if (contentCurrentMap->m_tilesGrid[pTile.m_x][pTile.m_y]->m_floorsArray[seenFloorIndex]->HoldsObjects())
    {

        for (int jjj = 0; jjj < CTileFloor::MAX_OBJECTS_ON_FLOOR; jjj++)
        {

            if (contentCurrentMap->m_tilesGrid[pTile.m_x][pTile.m_y]->m_floorsArray[seenFloorIndex]->m_containedObjects[jjj] == NULL)
                continue;

            auto&  it = contentCurrentMap->m_tilesGrid[pTile.m_x][pTile.m_y]->m_floorsArray[seenFloorIndex]->m_containedObjects[jjj];

            CDataDescription& desc = *DataLoading::libDescriptions[it->m_idxObjectType];

            CSize imgSize = { TILESIZE * std::atof(desc.m_propAttributes["ImageWidthMultiplier"].c_str()) ,
                            TILESIZE * std::atof(desc.m_propAttributes["ImageHeightMultiplier"].c_str()) };

            double scale = 1;

            if (desc.ContainsPropertyWithValue("RandomScaling", "True"))
                scale = 0.5 + (double)((pTile.m_x * pTile.m_y) % 16) / 32.0;

            imgSize.Scale(scale);

            CPoint pOffset = { 0, 0 };

            if (desc.ContainsProperty("XOffsetFactor"))
                pOffset.m_x = std::stof(desc.m_propAttributes["XOffsetFactor"]) * TILESIZE;

            if (desc.ContainsProperty("YOffsetFactor"))
                pOffset.m_y = std::stof(desc.m_propAttributes["YOffsetFactor"]) * TILESIZE;

            if (!desc.ContainsPropertyWithValue("IgnoreShadow", "True"))
            {

                CSize szShadow(2 * TILESIZE);

                CRectangle rectShadow = {int(x * tileSize + TILESIZE / 2 - szShadow.m_w / 2 + pOffset.m_x),
                                       int(y * tileSize + TILESIZE +
                                       TILESIZE / 2 - szShadow.m_h + pOffset.m_y),
                                       szShadow.m_w, szShadow .m_h};

                Drawing::Image(ID_SHADOW, rectShadow);

            }

            rTile = { int(x * tileSize + TILESIZE / 2 - imgSize.m_w / 2 + pOffset.m_x),
                    int(y * tileSize + TILESIZE - imgSize.m_h + pOffset.m_y),
                    imgSize.m_w,
                    imgSize.m_h };

            if (pTile.m_x == PlayerActions::focusedObjectMapx && pTile.m_y == PlayerActions::focusedObjectMapy)
            {

                int animIndex = PlayerActions::focusedObjectProgress;
                string imageFocusedObjectAnimationName = desc.m_propAttributes["ImageFocusedObjectAnimation"];

                if (DataLoading::GetDescriptionIndexByName("ObjectTree1") == it->m_idxObjectType)
                {
                    switch (animIndex)
                    {
                    case 0:
                        Drawing::Image(ID_TREE1_FALLING_0, rTile);
                        break;
                    case 1:
                        Drawing::Image(ID_TREE1_FALLING_1, rTile);
                        break;
                    case 2:
                        Drawing::Image(ID_TREE1_FALLING_2, rTile);
                        break;
                    }
                }

                if (DataLoading::GetDescriptionIndexByName("ObjectTree2") == it->m_idxObjectType)
                {
                    switch (animIndex)
                    {
                    case 0:
                        Drawing::Image(ID_TREE2_FALLING_0, rTile);
                        break;
                    case 1:
                        Drawing::Image(ID_TREE2_FALLING_1, rTile);
                        break;
                    case 2:
                        Drawing::Image(ID_TREE2_FALLING_2, rTile);
                        break;
                    }
                }

            }
            else
            {

                Drawing::Image(Animations::RunThroughAnimationFilter(it->m_idxObjectType, pTile.m_x, pTile.m_y), rTile);

            }


            imgSize.m_w = TILESIZE * 2;
            imgSize.m_h = TILESIZE * 2;

            rTile = {
                    int(x * tileSize + TILESIZE / 2 - imgSize.m_w / 2),
                    int(y * tileSize + TILESIZE - imgSize.m_h),
                    imgSize.m_w,
                    imgSize.m_h };

            switch (it->m_idxVanishingEffect)
            {

            case 0:
                Drawing::Image(ID_EFFECT_VANISH_0, rTile);
                break;
            case 1:
                Drawing::Image(ID_EFFECT_VANISH_1, rTile);
                break;
            case 2:
                Drawing::Image(ID_EFFECT_VANISH_2, rTile);
                break;
            case 3:
                Drawing::Image(ID_EFFECT_VANISH_3, rTile);
                break;
            case 4:
                Drawing::Image(ID_EFFECT_VANISH_4, rTile);
                break;
            case 5:
                Drawing::Image(ID_EFFECT_VANISH_5, rTile);
                break;
            }








            if (it != nullptr
                && pTile.m_x == PlayerActions::hoveredTile.m_x
                && pTile.m_y == PlayerActions::hoveredTile.m_y)
            {
                string objectName = DataLoading::libDescriptions[it->m_idxObjectType]->m_propAttributes["ReadableName"];

                if (it->m_propCurrentQuantity > 1)
                    objectName = std::to_string(it->m_propCurrentQuantity) + "x " + objectName; +"s";

                int mx = Global::GetMouseX();
                int my = Global::GetMouseY();

                if (DataLoading::libDescriptions[it->m_idxObjectType]->ContainsPropertyWithValue("HasAmount", "True"))
                {
                    int w = TextRendering::GetTextWidth(objectName) + 20;
                    CRectangle rect = { mx - w / 2, my - TILESIZE - 22, w, 22 };
                    Drawing::FilledRect({ 150, 190, 255, 170 }, rect);
                    TextRendering::DrawString(objectName, { 0, 0, 0 }, rect.x + 10, rect.y + 3);

                    string strAmount = "Amount: " + std::to_string(it->m_propCurrentAmount) + " %";
                    w = TextRendering::GetTextWidth(strAmount) + 20;
                    rect = { mx - w / 2, my - TILESIZE, w, 22 };
                    Drawing::FilledRect({ 150, 190, 255, 170 }, rect);
                    TextRendering::DrawString(strAmount, { 0, 0, 0 }, rect.x + 10, rect.y + 3);
                }
                else
                {
                    int w = TextRendering::GetTextWidth(objectName) + 20;
                    CRectangle rect = { mx - w / 2, my - TILESIZE, w, 22 };
                    Drawing::FilledRect({ 150, 190, 255, 170 }, rect);
                    TextRendering::DrawString(objectName, { 0, 0, 0 }, rect.x + 10, rect.y + 3);
                }

            }






        }

        
    }
}