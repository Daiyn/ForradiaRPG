/*+===================================================================
  File:      GLOBAL_CURRENTMAP.H

  Summary:   Describes function giving global access to the map
			 the player is currently located on.

  Classes:   CMap

  Functions: CurrentMap

  Origin:    Written by Andreas Åkerberg.

  This software is open source and licensed under the MIT License.
===================================================================+*/

#pragma once

#include <memory>

using std::unique_ptr;
using std::move;

class CMap;

namespace Global
{
	inline unique_ptr<CMap> currentMap;
}
