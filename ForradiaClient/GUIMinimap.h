/*+===================================================================
  File:      GUIMINIMAP.H

  Summary:   Describes constants and functions realted to the minimap
             which is shown at the top right corner of the screen.

  Classes:   

  Functions: Render
             GetScaledMiniMapSize
             GetBottomY

  Origin:    Written by Andreas �kerberg.

  This software is open source and licensed under the MIT License.
===================================================================+*/

#ifndef FORRADIACLIENT_GUIMINIMAP_H
#define FORRADIACLIENT_GUIMINIMAP_H

namespace GUIMinimap
{
    const int pxSizeOriginal = 200;
    const int pxBorderWidth = 10;
    const int pxPlayerSymbolSize = 4;

    int GetBottomY();
    int GetScaledMiniMapSize();
    void Render();
};


#endif //FORRADIACLIENT_GUIMINIMAP_H
