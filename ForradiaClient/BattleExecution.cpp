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
    
    if (tmrBattleIteration.TimeForUpdate())
    {

        if (Combat::tickCombatInitiated == 0)
            Combat::tickCombatInitiated = SDL_GetTicks();

        srand(SDL_GetTicks());

        CFoe& targetedFoe = Global::contentCurrentMap->m_mirrorAllFoes[Combat::idxTargetedFoe];

        /* Determine the maxDamage for the player and the foe and hit both
           the player and the foe once every timer tick. */
        int maxDamage = 3;
        auto& pFoe = (CFightableCharacter&)targetedFoe;
        HitFightableCharacter(pFoe, maxDamage);
        Global::contentCurrentMap->AddObjectIfDoesntAlreadyExist(DataLoading::GetDescriptionIndexByName("ObjectPoolOfBlood"), targetedFoe.m_coordPosition.m_x, targetedFoe.m_coordPosition.m_y, SURFACE_FLOOR);
        auto& pPlayer = (CFightableCharacter&)(*Global::player);
        HitFightableCharacter(pPlayer, maxDamage);

    }

}

/* This function applies to both the player and the foes. */
void BattleExecution::HitFightableCharacter(CFightableCharacter& character, int maxDamage)
{

    int damage = rand() % maxDamage;
    character.Hit(damage);

    if (character.m_idxCharacterType == CHARACTER_TYPE_PLAYER)
        GUITerminal::PrintDamageToPlayer(damage, "foe");
    else if (character.m_idxCharacterType == CHARACTER_TYPE_FOE)
        GUITerminal::PrintDamageToFoe(damage, "foe");


}