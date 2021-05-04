#include "BattleExecution.h"
#include "Global_CurrentMap.h"
#include "Global_Player.h"
#include "GUITerminal.h"
#include "Combat.h"
#include "DataLoading.h"
#include "CMap.h"
#include "Constants.h"
#include "Utilities.h"
#include "CPlayer.h"
#include <SDL2/SDL_timer.h>



void BattleExecution::PerformCombat()
{
    
    if (Utilities::DoTickCheck(tickLastCombatIteration, tickCombatSpeed))
    {

        if (Combat::tickCombatInitiated == 0)
            Combat::tickCombatInitiated = SDL_GetTicks();

        srand(SDL_GetTicks());

        CFoe& targetedFoe = Global::currentMap->m_allFoesArray[Combat::idxTargetedFoe];

        int maxDamage = 3;
        auto& pFoe = (CFightableCharacter&)targetedFoe;
        HitFightableCharacter(pFoe, maxDamage);
        Global::currentMap->AddObjectIfDoesntAlreadyExist(DataLoading::GetDescriptionIndexByName("ObjectPoolOfBlood"), targetedFoe.m_posCurrent.m_x, targetedFoe.m_posCurrent.m_y, SURFACE_FLOOR);
        auto& pPlayer = (CFightableCharacter&)(*Global::player);
        HitFightableCharacter(pPlayer, maxDamage);

    }

}

void BattleExecution::HitFightableCharacter(CFightableCharacter& character, int maxDamage)
{

    int damage = rand() % maxDamage;
    character.Hit(damage);

    if (character.m_idxCharacterType == CHARACTER_TYPE_PLAYER)
        GUITerminal::PrintDamageToPlayer(damage, "foe");
    else if (character.m_idxCharacterType == CHARACTER_TYPE_FOE)
        GUITerminal::PrintDamageToFoe(damage, "foe");


}