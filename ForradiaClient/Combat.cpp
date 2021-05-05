#include "Combat.h"
#include "GUITerminal.h"
#include "Utilities.h"
#include "Global_Player.h"
#include "Global_Canvas.h"
#include "Global_CurrentMap.h"
#include "BattleExecution.h"
#include "CPoint.h"
#include "CMap.h"
#include "CFoe.h"

using std::unique_ptr;

void Combat::Update()
{

    if (idxTargetedFoe != -1)
    {

        CFoe& targetedFoe = Global::contentCurrentMap->m_mirrorAllFoes[idxTargetedFoe];

        if (targetedFoe.IsAlive())
        {

            CPoint tc(targetedFoe.m_coordPosition.m_x, targetedFoe.m_coordPosition.m_y);
            CPoint tcDist = tc.GetAbsDistanceToPlayer();

            int maxDist = std::max(tcDist.m_x, tcDist.m_y);

            if (maxDist == 1)
                BattleExecution::PerformCombat();

        }
        else
            idxTargetedFoe = -1;

    }

}

bool Combat::HandleMouseClickOnFoe()
{

    CPoint tc;
    tc.JumpToHoveredTile();

    if (Global::contentCurrentMap->SeenFloorHasFoes(tc.m_x, tc.m_y))
    {
        int indexAllFoesArray = Global::contentCurrentMap->GetTopFoeInMapAllFoeArrayIndex(tc.m_x, tc.m_y);
        if (indexAllFoesArray != -1)
        {
            idxTargetedFoe = indexAllFoesArray;
            tickCombatInitiated = 0;
            tickSelectTarget = SDL_GetTicks();

            return true;
        }
    }
    else
        return false;


    return false;

}

