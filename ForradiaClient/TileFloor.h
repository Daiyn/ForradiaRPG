/*+===================================================================
  File:      CTILEFLOOR.H

  Summary:   Describes essential data holder class used in the map.

  Classes:   CTileFloor
             CObject
             CAnimal
             CNPC

  Functions: 

  Origin:    Written by Andreas Åkerberg.

  This software is open source and licensed under the MIT License.
===================================================================+*/

#ifndef FORRADIACLIENT_TILEFLOOR_H
#define FORRADIACLIENT_TILEFLOOR_H

#include "Object.h"
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

class TileFloor
{
public:

    static const int MAX_OBJECTS_ON_FLOOR = 10;
    static const int MAX_FOES_ON_FLOOR = 3;

    int m_idxGroundType;
    int m_coordMapX;
    int m_coordMapY;
    unique_ptr<Object> m_containedObjects[MAX_OBJECTS_ON_FLOOR];

    TileFloor(int _mapx, int _mapy);
    TileFloor(int _mapx, int _mapy, int _groundType);

    void AddObject(int _objectType);
    void ClearObjects();
    void DeleteObjectAtIndex(int i);
    void DeleteObjectWithId(int id);
    int GetFreeObjectIndex();
    int GetObjectIndexForObjectType(int _objectType);
    int GetObjectIndexWithId(int id);
    bool HoldsObjectOfType(int _objectType);
    bool HoldsObjectOfTypeAndQuantity(int _objectType, int _quantity);
    bool HoldsObjects();
    bool RemoveIfHoldsObjectOfTypeAndQuantity(int _objectType, int _quantity);
    void ReplaceObject(int objectTypeToReplace, int objectToReplaceQuantity, int objectTypeToReplaceWith, int objectToReplaceWithQuantity);

protected:

private:

};


#endif //FORRADIACLIENT_TILEFLOOR_H
