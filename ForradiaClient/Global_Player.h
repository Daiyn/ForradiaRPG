/*+===================================================================
  File:      GLOBAL_PLAYER.H

  Summary:   Describes the globally accessed primary Player instance 
			 object and a few help functions related to the player
			 position.

  Classes:   CPlayer

  Functions: 

  Origin:    Written by Andreas Åkerberg.

  This software is open source and licensed under the MIT License.
===================================================================+*/

#pragma once

#include <stddef.h>
#include <memory>
#include "CPlayer.h"

#define XSCREENSTART Global::statePlayer->m_coordPosition.m_x - (Global::GetNumberOfColumns() - 1) / 2
#define YSCREENSTART Global::statePlayer->m_coordPosition.m_y - (Global::tilesNumberOfRows - 1) / 2 - 3

using std::unique_ptr;

namespace Global
{

	inline unique_ptr<CPlayer> statePlayer;

}
