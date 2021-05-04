/*+===================================================================
  File:      CTILEFLOOR.H

  Summary:   Describes essential data holder class used in the map.

  Classes:   CTileFloor
             CObject
             CFoe
             CNPC

  Functions: 

  Origin:    Written by Andreas Åkerberg.

  This software is open source and licensed under the MIT License.
===================================================================+*/

#ifndef FORRADIACLIENT_TILEFLOOR_H
#define FORRADIACLIENT_TILEFLOOR_H

#include "CObject.h"
#include "CFoe.h"
#include "CNPC.h"
#include <vector>
#include <memory>

using std::unique_ptr;

#define INVALID_INDEX -1

/*C+C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C
  Class:    CTileFloor

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

class CTileFloor
{
public:

    static const int MAX_OBJECTS_ON_FLOOR = 10;
    static const int MAX_FOES_ON_FLOOR = 3;

    int m_groundType;
    int m_mapx;
    int m_mapy;
    unique_ptr<CObject> m_floorObjectsArr[MAX_OBJECTS_ON_FLOOR];
    unique_ptr<CFoe> m_floorFoesArr[MAX_FOES_ON_FLOOR];
    std::vector<unique_ptr<CNPC>> m_npcs;

    CTileFloor(int _mapx, int _mapy);
    CTileFloor(int _mapx, int _mapy, int _groundType);

    void AddObject(int _objectType);
    void ClearObjects();
    void DeleteObjectAtIndex(int i);
    void DeleteObjectWithId(int id);
    int GetFreeObjectIndex();
    int GetObjectIndexForObjectType(int _objectType);
    int GetObjectIndexWithId(int id);
    bool HasNpcs();
    bool HoldsObjectOfType(int _objectType);
    bool HoldsObjectOfTypeAndQuantity(int _objectType, int _quantity);
    bool HoldsObjects();
    bool RemoveIfHoldsObjectOfTypeAndQuantity(int _objectType, int _quantity);
    void ReplaceObject(int objectTypeToReplace, int objectToReplaceQuantity, int objectTypeToReplaceWith, int objectToReplaceWithQuantity);

protected:

private:

};


#endif //FORRADIACLIENT_TILEFLOOR_H
