/*+===================================================================
  File:      CTILE.H

  Summary:   Describes essential data holder class used in the map.

  Classes:   CTile
             CTileFloor

  Functions: 

  Origin:    Written by Andreas Åkerberg.

  This software is open source and licensed under the MIT License.
===================================================================+*/

#ifndef FORRADIACLIENT_TILE_H
#define FORRADIACLIENT_TILE_H

#define SURFACE_FLOOR CTile::MAX_NUM_FLOORS

#include <unordered_map>
#include "CTileFloor.h"

/*C+C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C
  Class:    CTile

  Summary:  Short summary of purpose and content of CMyClass.
            Short summary of purpose and content of CMyClass.

  Methods:  MyMethodOne
              Short description of MyMethodOne.
            MyMethodTwo
              Short description of MyMethodTwo.
            CMyClass
              Constructor.
            ~CMyClass
              Destructor.
C---C---C---C---C---C---C---C---C---C---C---C---C---C---C---C---C-C*/

class CTile
{
public:

    static const int MAX_NUM_FLOORS = 50;

    unique_ptr<CTileFloor> m_floorsArray[MAX_NUM_FLOORS + 1];

    int m_elevationHeight = 0;
    vector<int> m_checkMinedTiles;
    bool m_isNPCOwnedLand = false;

    int GetIndexForSeenFloor();

protected:

private:

};


#endif //FORRADIACLIENT_TILE_H
