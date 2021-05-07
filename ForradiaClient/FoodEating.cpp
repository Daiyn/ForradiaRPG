#include "FoodEating.h"
#include "DataLoading.h"
#include "Global_CurrentMap.h"
#include "CMap.h"
#include "CRectangle.h"
#include "Drawing.h"
#include "GUIStatusPanel.h"
#include "Constants.h"
#include "Global_Canvas.h"
#include "TextRendering.h"
#include "Colors.h"
#include <iomanip>
#include "Global_Player.h"

using std::make_unique;
using std::to_string;
using std::stringstream;
using std::setprecision;

void FoodEating::Render()
{

    int margin = 5;
    int left = GUIStatusPanel::pxWidthOriginal * Global::GetScalingHorizontal() + margin;
    int top = 20;
    int iconSize = 40;

    int i = 0;

    for (auto it = activeFoodItems.begin(); it != activeFoodItems.end(); it++)
    {
        CRectangle rect = { left + i * (iconSize + margin), top, iconSize, iconSize };

        Drawing::Image(it->m_foodItem->m_idxObjectType, rect);
        Drawing::Image(kIDIconActiveFoodItemFrame, rect);

        auto& desc = DataLoading::libDescriptions[it->m_foodItem->m_idxObjectType];

        if (desc->ContainsProperty("FoodAmount") && desc->ContainsProperty("FoodSpeed"))
        {
            double amount = atof(desc->m_propAttributes["FoodAmount"].c_str());
            double speed = atof(desc->m_propAttributes["FoodSpeed"].c_str());

            double totalDuration = amount / speed;
            double passedTime = (SDL_GetTicks() - it->m_tickCreated) / 1000.0;
            double timeLeft = totalDuration - passedTime;
            
            stringstream stream;
            stream << std::fixed << setprecision(1) << timeLeft;
            string strDuration = stream.str();

            int textX = rect.x + iconSize/2 - TextRendering::GetTextWidth(strDuration) / 2;

            TextRendering::DrawString(strDuration, WHITE, textX, rect.y + rect.h);
        }

        i++;
    }
}

void FoodEating::EatAppleFromGround(CPoint p)
{
    int objectApple = DataLoading::GetDescriptionIndexByName("ObjectApple");

    int seenFloorIndex = Global::contentCurrentMap->m_tilesGrid[p.m_x][p.m_y]->GetIndexForSeenFloor();

    if (seenFloorIndex == -1)
        return;

    CTileFloor& floor = *Global::contentCurrentMap->m_tilesGrid[p.m_x][p.m_y]->m_floorsArray[seenFloorIndex];

    if (floor.RemoveIfHoldsObjectOfTypeAndQuantity(objectApple, 1))
    {
        activeFoodItems.push_back(CActiveFoodItem(make_unique<CObject>(CObject(objectApple, 1))));
    }
}

void FoodEating::Update()
{

    int ticksPassed = SDL_GetTicks() - tickLastUpdate;
    tickLastUpdate = SDL_GetTicks();

    for (int i = 0; i < activeFoodItems.size(); i++)
    {
        
        auto& it = activeFoodItems[i];

        auto& desc = DataLoading::libDescriptions[it.m_foodItem->m_idxObjectType];

        if (desc->ContainsProperty("FoodAmount") && desc->ContainsProperty("FoodSpeed"))
        {
            double amount = atof(desc->m_propAttributes["FoodAmount"].c_str());
            double speed = atof(desc->m_propAttributes["FoodSpeed"].c_str());

            double totalDuration = amount / speed;
            double passedTime = (SDL_GetTicks() - it.m_tickCreated) / 1000.0;
            double timeLeft = totalDuration - passedTime;

            if (timeLeft <= 0)
            {
                activeFoodItems.erase(activeFoodItems.begin() + i);
            }
            else
            {
                double increasePerMillisecond = amount / totalDuration / 1000.0;
                double increaseAmount = increasePerMillisecond * ticksPassed;

                Global::statePlayer->AddNRGY(increaseAmount);
            }
        }
    }
}

CActiveFoodItem::CActiveFoodItem(unique_ptr<CObject> foodItem)
{
    m_foodItem = move(foodItem);
    m_tickCreated = SDL_GetTicks();
}
