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
#include "Size.h"
#include "Tile.h"
#include "Animations.h"

using Global::contentCurrentMap;

void ObjectsRendering::RenderTileObjects(double tileSize, int x, int y, Point pTile)
{

    int tileSizeCeil = ceil(tileSize);
    auto TILESIZE = tileSizeCeil;
    auto& PLAYER = Global::statePlayer;

    int seenFloorIndex = contentCurrentMap->m_tilesGrid[pTile.m_x][pTile.m_y]->GetIndexForSeenFloor();

    if (seenFloorIndex == -1)
        return;

    Rectangle rTile = { int(x * tileSize), int(y * tileSize), TILESIZE, TILESIZE };

    if (contentCurrentMap->m_tilesGrid[pTile.m_x][pTile.m_y]->m_floorsArray[seenFloorIndex]->HoldsObjects())
    {

        for (int jjj = 0; jjj < TileFloor::MAX_OBJECTS_ON_FLOOR; jjj++)
        {

            if (contentCurrentMap->m_tilesGrid[pTile.m_x][pTile.m_y]->m_floorsArray[seenFloorIndex]->m_containedObjects[jjj] == NULL)
                continue;

            auto&  it = contentCurrentMap->m_tilesGrid[pTile.m_x][pTile.m_y]->m_floorsArray[seenFloorIndex]->m_containedObjects[jjj];

            DataDescription& desc = *DataLoading::libDescriptions[it->m_idxObjectType];

            Size imgSize = { TILESIZE * std::atof(desc.m_propAttributes["ImageWidthMultiplier"].c_str()) ,
                            TILESIZE * std::atof(desc.m_propAttributes["ImageHeightMultiplier"].c_str()) };

            double scale = 1;

            if (desc.ContainsPropertyWithValue("RandomScaling", "true"))
                scale = 0.5 + (double)((pTile.m_x * pTile.m_y) % 16) / 32.0;

            imgSize.Scale(scale);

            Point pOffset = { 0, 0 };

            if (desc.ContainsProperty("XOffsetFactor"))
                pOffset.m_x = std::stof(desc.m_propAttributes["XOffsetFactor"]) * TILESIZE;

            if (desc.ContainsProperty("YOffsetFactor"))
                pOffset.m_y = std::stof(desc.m_propAttributes["YOffsetFactor"]) * TILESIZE;

            pOffset.m_x *= scale;
            pOffset.m_y *= scale;

            if (!desc.ContainsPropertyWithValue("IgnoreShadow", "true"))
            {

                Size szShadow(2 * TILESIZE);

                Rectangle rectShadow = {int(x * tileSize + TILESIZE / 2 - szShadow.m_w / 2 + pOffset.m_x),
                                       int(y * tileSize + TILESIZE +
                                       TILESIZE / 2 - szShadow.m_h + pOffset.m_y),
                                       szShadow.m_w, szShadow .m_h};

                Drawing::Image(ImagesIDs::Shadow, rectShadow);

            }

            rTile = { int(x * tileSize + TILESIZE / 2 - imgSize.m_w / 2 + pOffset.m_x),
                    int(y * tileSize + TILESIZE - imgSize.m_h + pOffset.m_y),
                    imgSize.m_w,
                    imgSize.m_h };

            if (pTile.m_x == PlayerActions::coordFocusedObjectMapx && pTile.m_y == PlayerActions::coordFocusedObjectMapy)
            {

                int animIndex = PlayerActions::stateFocusedObjectProgress;
                string imageFocusedObjectAnimationName = desc.m_propAttributes["ImageFocusedObjectAnimation"];

                if (DataLoading::GetDescriptionIndexByName("ObjectTree1") == it->m_idxObjectType)
                {
                    switch (animIndex)
                    {
                    case 0:
                        Drawing::Image(ImagesIDs::Tree1Falling0, rTile);
                        break;
                    case 1:
                        Drawing::Image(ImagesIDs::Tree1Falling1, rTile);
                        break;
                    case 2:
                        Drawing::Image(ImagesIDs::Tree1Falling2, rTile);
                        break;
                    }
                }

                if (DataLoading::GetDescriptionIndexByName("ObjectTree2") == it->m_idxObjectType)
                {
                    switch (animIndex)
                    {
                    case 0:
                        Drawing::Image(ImagesIDs::Tree2Falling0, rTile);
                        break;
                    case 1:
                        Drawing::Image(ImagesIDs::Tree2Falling1, rTile);
                        break;
                    case 2:
                        Drawing::Image(ImagesIDs::Tree2Falling2, rTile);
                        break;
                    }
                }

            }
            else
            {
                if (DataLoading::GetDescriptionIndexByName("ObjectTree1") == it->m_idxObjectType
                    && Global::statePlayer != nullptr)
                {



                    imgSize.Scale(3.0 / 2.0);

                    DataDescription& descRotatedShadow = *DataLoading::libDescriptions[ImagesIDs::ObjectTree1Shadow];

                    if (descRotatedShadow.ContainsProperty("XOffsetFactor"))
                        pOffset.m_x = std::stof(descRotatedShadow.m_propAttributes["XOffsetFactor"]) * TILESIZE * scale;

                    if (descRotatedShadow.ContainsProperty("YOffsetFactor"))
                        pOffset.m_y = std::stof(descRotatedShadow.m_propAttributes["YOffsetFactor"]) * TILESIZE * scale;

                    rTile = { int(x * tileSize + TILESIZE / 2 - imgSize.m_w / 2 + pOffset.m_x),
                            int(y * tileSize + TILESIZE - imgSize.m_h + pOffset.m_y),
                            imgSize.m_w,
                            imgSize.m_h };


                    Drawing::Image(Animations::RunThroughAnimationFilter(ImagesIDs::ObjectTree1Shadow, pTile.m_x, pTile.m_y), rTile);

                    imgSize.Scale(2.0 / 3.0);






                    double dx = pTile.m_x - Global::statePlayer->m_coordPosition.m_x;
                    double dy = pTile.m_y - Global::statePlayer->m_coordPosition.m_y;

                    double w = atan2(dy, dx) + 2.0*M_PI;

                    if (w < 0)
                        w += 2.0 * M_PI;

                    if (w > 2.0 * M_PI)
                        w -= 2.0 * M_PI;

                    if (w < M_PI / 8.0 || w >= M_PI * 15.0 / 8.0)
                    {

                        DataDescription& descRotated = *DataLoading::libDescriptions[ImagesIDs::ObjectTree1E];

                        if (descRotated.ContainsProperty("XOffsetFactor"))
                            pOffset.m_x = std::stof(descRotated.m_propAttributes["XOffsetFactor"]) * TILESIZE * scale;

                        if (descRotated.ContainsProperty("YOffsetFactor"))
                            pOffset.m_y = std::stof(descRotated.m_propAttributes["YOffsetFactor"]) * TILESIZE * scale;

                        rTile = { int(x * tileSize + TILESIZE / 2 - imgSize.m_w / 2 + pOffset.m_x),
                                int(y * tileSize + TILESIZE - imgSize.m_h + pOffset.m_y),
                                imgSize.m_w,
                                imgSize.m_h };


                        Drawing::Image(Animations::RunThroughAnimationFilter(ImagesIDs::ObjectTree1E, pTile.m_x, pTile.m_y), rTile);
                    }
                    else if (w >= M_PI / 8.0 && w < M_PI * 3.0 / 8.0)
                    {

                        imgSize.Scale(3.0 / 2.0);

                        DataDescription& descRotated = *DataLoading::libDescriptions[ImagesIDs::ObjectTree1SE];

                        if (descRotated.ContainsProperty("XOffsetFactor"))
                            pOffset.m_x = std::stof(descRotated.m_propAttributes["XOffsetFactor"]) * TILESIZE * scale;

                        if (descRotated.ContainsProperty("YOffsetFactor"))
                            pOffset.m_y = std::stof(descRotated.m_propAttributes["YOffsetFactor"]) * TILESIZE * scale;

                        rTile = { int(x * tileSize + TILESIZE / 2 - imgSize.m_w / 2 + pOffset.m_x),
                                int(y * tileSize + TILESIZE - imgSize.m_h + pOffset.m_y),
                                imgSize.m_w,
                                imgSize.m_h };


                        Drawing::Image(Animations::RunThroughAnimationFilter(ImagesIDs::ObjectTree1SE, pTile.m_x, pTile.m_y), rTile);
                    }
                    else if (w >= M_PI*  3.0 / 8.0 && w < M_PI * 5.0 / 8.0)
                    {

                        DataDescription& descRotated = *DataLoading::libDescriptions[ImagesIDs::ObjectTree1S];

                        if (descRotated.ContainsProperty("XOffsetFactor"))
                            pOffset.m_x = std::stof(descRotated.m_propAttributes["XOffsetFactor"]) * TILESIZE * scale;

                        if (descRotated.ContainsProperty("YOffsetFactor"))
                            pOffset.m_y = std::stof(descRotated.m_propAttributes["YOffsetFactor"]) * TILESIZE * scale;

                        rTile = { int(x * tileSize + TILESIZE / 2 - imgSize.m_w / 2 + pOffset.m_x),
                                int(y * tileSize + TILESIZE - imgSize.m_h + pOffset.m_y),
                                imgSize.m_w,
                                imgSize.m_h };


                        Drawing::Image(Animations::RunThroughAnimationFilter(ImagesIDs::ObjectTree1S, pTile.m_x, pTile.m_y), rTile);
                    }
                    else if (w >= M_PI * 5.0 / 8.0 && w < M_PI * 7.0 / 8.0)
                    {

                        imgSize.Scale(3.0 / 2.0);

                        DataDescription& descRotated = *DataLoading::libDescriptions[ImagesIDs::ObjectTree1SW];

                        if (descRotated.ContainsProperty("XOffsetFactor"))
                            pOffset.m_x = std::stof(descRotated.m_propAttributes["XOffsetFactor"]) * TILESIZE * scale;

                        if (descRotated.ContainsProperty("YOffsetFactor"))
                            pOffset.m_y = std::stof(descRotated.m_propAttributes["YOffsetFactor"]) * TILESIZE * scale;

                        rTile = { int(x * tileSize + TILESIZE / 2 - imgSize.m_w / 2 + pOffset.m_x),
                                int(y * tileSize + TILESIZE - imgSize.m_h + pOffset.m_y),
                                imgSize.m_w,
                                imgSize.m_h };


                        Drawing::Image(Animations::RunThroughAnimationFilter(ImagesIDs::ObjectTree1SW, pTile.m_x, pTile.m_y), rTile);
                    }
                    else if (w >= M_PI * 7.0 / 8.0 && w < M_PI * 9.0 / 8.0)
                    {

                        DataDescription& descRotated = *DataLoading::libDescriptions[ImagesIDs::ObjectTree1W];

                        if (descRotated.ContainsProperty("XOffsetFactor"))
                            pOffset.m_x = std::stof(descRotated.m_propAttributes["XOffsetFactor"]) * TILESIZE * scale;

                        if (descRotated.ContainsProperty("YOffsetFactor"))
                            pOffset.m_y = std::stof(descRotated.m_propAttributes["YOffsetFactor"]) * TILESIZE * scale;

                        rTile = { int(x * tileSize + TILESIZE / 2 - imgSize.m_w / 2 + pOffset.m_x),
                                int(y * tileSize + TILESIZE - imgSize.m_h + pOffset.m_y),
                                imgSize.m_w,
                                imgSize.m_h };


                        Drawing::Image(Animations::RunThroughAnimationFilter(ImagesIDs::ObjectTree1W, pTile.m_x, pTile.m_y), rTile);
                    }
                    else if (w >= M_PI * 9.0 / 8.0 && w < M_PI * 11.0 / 8.0)
                    {

                        imgSize.Scale(3.0 / 2.0);

                        DataDescription& descRotated = *DataLoading::libDescriptions[ImagesIDs::ObjectTree1NW];

                        if (descRotated.ContainsProperty("XOffsetFactor"))
                            pOffset.m_x = std::stof(descRotated.m_propAttributes["XOffsetFactor"]) * TILESIZE * scale;

                        if (descRotated.ContainsProperty("YOffsetFactor"))
                            pOffset.m_y = std::stof(descRotated.m_propAttributes["YOffsetFactor"]) * TILESIZE * scale;

                        rTile = { int(x * tileSize + TILESIZE / 2 - imgSize.m_w / 2 + pOffset.m_x),
                                int(y * tileSize + TILESIZE - imgSize.m_h + pOffset.m_y),
                                imgSize.m_w,
                                imgSize.m_h };


                        Drawing::Image(Animations::RunThroughAnimationFilter(ImagesIDs::ObjectTree1NW, pTile.m_x, pTile.m_y), rTile);
                    }
                    else if (w >= M_PI * 11.0 / 8.0 && w < M_PI * 13.0 / 8.0)
                    {

                    DataDescription& descRotated = *DataLoading::libDescriptions[ImagesIDs::ObjectTree1N];

                    if (descRotated.ContainsProperty("XOffsetFactor"))
                        pOffset.m_x = std::stof(descRotated.m_propAttributes["XOffsetFactor"]) * TILESIZE * scale;

                    if (descRotated.ContainsProperty("YOffsetFactor"))
                        pOffset.m_y = std::stof(descRotated.m_propAttributes["YOffsetFactor"]) * TILESIZE * scale;

                    rTile = { int(x * tileSize + TILESIZE / 2 - imgSize.m_w / 2 + pOffset.m_x),
                            int(y * tileSize + TILESIZE - imgSize.m_h + pOffset.m_y),
                            imgSize.m_w,
                            imgSize.m_h };


                        Drawing::Image(Animations::RunThroughAnimationFilter(ImagesIDs::ObjectTree1N, pTile.m_x, pTile.m_y), rTile);
                    }
                    else if (w >= M_PI * 13.0 / 8.0 && w < M_PI * 15.0 / 8.0)
                    {

                    imgSize.Scale(3.0/2.0);

                    DataDescription& descRotated = *DataLoading::libDescriptions[ImagesIDs::ObjectTree1NE];

                    if (descRotated.ContainsProperty("XOffsetFactor"))
                        pOffset.m_x = std::stof(descRotated.m_propAttributes["XOffsetFactor"]) * TILESIZE * scale;

                    if (descRotated.ContainsProperty("YOffsetFactor"))
                        pOffset.m_y = std::stof(descRotated.m_propAttributes["YOffsetFactor"]) * TILESIZE * scale;

                    rTile = { int(x * tileSize + TILESIZE / 2 - imgSize.m_w / 2 + pOffset.m_x),
                            int(y * tileSize + TILESIZE - imgSize.m_h + pOffset.m_y),
                            imgSize.m_w,
                            imgSize.m_h };


                        Drawing::Image(Animations::RunThroughAnimationFilter(ImagesIDs::ObjectTree1NE, pTile.m_x, pTile.m_y), rTile);
                    }

                }







                











                else
                {
                    Drawing::Image(Animations::RunThroughAnimationFilter(it->m_idxObjectType, pTile.m_x, pTile.m_y), rTile);
                }

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
                Drawing::Image(ImagesIDs::EffectVanish0, rTile);
                break;
            case 1:
                Drawing::Image(ImagesIDs::EffectVanish1, rTile);
                break;
            case 2:
                Drawing::Image(ImagesIDs::EffectVanish2, rTile);
                break;
            case 3:
                Drawing::Image(ImagesIDs::EffectVanish3, rTile);
                break;
            case 4:
                Drawing::Image(ImagesIDs::EffectVanish4, rTile);
                break;
            case 5:
                Drawing::Image(ImagesIDs::EffectVanish5, rTile);
                break;
            }








            if (it != nullptr
                && pTile.m_x == PlayerActions::coordHoveredTile.m_x
                && pTile.m_y == PlayerActions::coordHoveredTile.m_y)
            {
                string objectName = DataLoading::libDescriptions[it->m_idxObjectType]->m_propAttributes["ReadableName"];

                if (it->m_propCurrentQuantity > 1)
                    objectName = std::to_string(it->m_propCurrentQuantity) + "x " + objectName; +"s";

                int mx = Global::GetMouseX();
                int my = Global::GetMouseY();

                if (DataLoading::libDescriptions[it->m_idxObjectType]->ContainsPropertyWithValue("HasAmount", "true"))
                {
                    int w = TextRendering::GetTextWidth(objectName) + 20;
                    Rectangle rect = { mx - w / 2, my - TILESIZE - 22, w, 22 };
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
                    Rectangle rect = { mx - w / 2, my - TILESIZE, w, 22 };
                    Drawing::FilledRect({ 150, 190, 255, 170 }, rect);
                    TextRendering::DrawString(objectName, { 0, 0, 0 }, rect.x + 10, rect.y + 3);
                }

            }






        }

        
    }
}