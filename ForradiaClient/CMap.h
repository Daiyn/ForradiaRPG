/*+===================================================================
  File:      CMAP.H

  Summary:   Describes the essential CMap class representing a part  
             of the world map on which the player moves and is being
             rendered.

  Classes:   CMap
             CTile
             CObject
             CAnimal
             CNPC
             CTileFloor
             CPoint

  Functions: 

  Origin:    Written by Andreas Åkerberg.

  This software is open source and licensed under the MIT License.
===================================================================+*/

#ifndef FORRADIAFORMATION_MAP_H
#define FORRADIAFORMATION_MAP_H



#include <vector>
#include "CPoint.h"
#include "CObject.h"
#include <memory>
#include "CTile.h"

#define INVALID_ELVATION -1

using std::unique_ptr;
using std::vector;
using std::reference_wrapper;

class CNPC;
class CAnimal;
class CTileFloor;
struct SDL_Surface;
struct SDL_Texture;

/*C+C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C
  Class:    CMap

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

class CMap
{
public:

    vector<CObject> m_objectsWithUpdateNeed;
    vector<reference_wrapper<CNPC>> m_mirrorAllNPCs;
    CPoint m_coordPlazaPosition;
    int m_tilesNumPlazaSize;
    vector<reference_wrapper<CAnimal>> m_mirrorAllFoes;
    vector<vector < unique_ptr<CTile>>> m_tilesGrid;
    SDL_Surface* m_imgFullMapRender = NULL;
    SDL_Texture* m_texFullMapRender = NULL;

    CMap(int mapSize);

    void AddFoe(unique_ptr<CAnimal>, int floor);
    void AddChangingObject(int _objectType, CPoint p, int floor);
    void AddObject(int objectType, int mapx, int mapy, int floor);
    void AddObject(unique_ptr<CObject> _object, CPoint p, int floor);
    void AddObjectIfDoesntAlreadyExist(int objectType, int mapx, int mapy, int floor);
    void ClearReferencesToFoe(CAnimal& foe, int allFoesListIndex, CTileFloor& floor);
    unique_ptr<CObject> GetTopObject(int mapx, int mapy);
    int GetTopObjectType(int mapx, int mapy);
    int GetTopFoeInMapAllFoeArrayIndex(int mapx, int mapy);
    bool SeenFloorHasBlockingFoes(int mapx, int mapy);
    bool SeenFloorHasFoes(int mapx, int mapy);
    bool TileHoldsObjectOfType(int _objectType, int mapx, int mapy, int floor);
    bool TileHoldsObjectOfTypeAndQuantity(int _objectType, int quantity, int mapx, int mapy, int floor);
    bool TileIsAnyOfTypes(int mapx, int mapy, int val1, int val2, int val3);
    bool TileIsMinedAtElev(int elev, int mapx, int mapy);
    bool TileIsNotAnyOfTypes(int mapx, int mapy, int val1, int val2, int val3);
    void TranslateFoe(int uniqueID, CPoint pFrom, CPoint pTo, int floor);
    void UpdateNPCs();

protected:

private:

};


#endif
