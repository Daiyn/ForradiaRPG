/*+===================================================================
  File:      GUISTATUSPANEL.H

  Summary:   Describes free variables and functions realted to the 
             status panel which is shown at the top left corner of 
             the screen.

  Classes:   

  Functions: Render

  Origin:    Written by Andreas Åkerberg.

  This software is open source and licensed under the MIT License.
===================================================================+*/

#ifndef FORRADIAFORMATION_GUISTATUSPANEL_H
#define FORRADIAFORMATION_GUISTATUSPANEL_H

namespace GUIStatusPanel
{
    inline int wOrig = 350;
    inline int hOrig = 150;
    inline int margin = 10;

    void Render();
};


#endif //FORRADIAFORMATION_GUISTATUSPANEL_H
