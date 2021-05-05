/*+===================================================================
  File:      ITEMMOVING.H

  Summary:   Describes a free variable and functions related to the
             moving of game objects of type CObject.

  Classes:   CObject

  Functions: TryStartDragingObjectFromGround
             DropnodupMovedObjectIfExists
             Render

  Origin:    Written by Andreas Åkerberg.

  This software is open source and licensed under the MIT License.
===================================================================+*/

#ifndef FORRADIACLIENT_ITEMMOVING_H
#define FORRADIACLIENT_ITEMMOVING_H

#include "CObject.h"
#include <stdio.h>
#include <memory>

using std::unique_ptr;

void RenderItemMoving();

namespace ItemMoving
{
    inline unique_ptr<CObject> nodupMovedObject;

    void DropnodupMovedObjectIfExists(int mapx, int mapy);
    void Render();
    bool TryStartDragingObjectFromGround(int mapx, int mapy);
};


#endif //FORRADIACLIENT_ITEMMOVING_H
