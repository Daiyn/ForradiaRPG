/*+===================================================================
  File:      CURSOR.H

  Summary:   Describes the class for the games custom cursor.

  Classes:   Classes declared or used (in source files).

  Functions: 

  Origin:    Written by Andreas Åkerberg.

  This software is open source and licensed under the MIT License.
===================================================================+*/

#ifndef FORRADIAFORMATION_CURSOR_H
#define FORRADIAFORMATION_CURSOR_H

namespace Cursor
{
    inline int attrCursorSize = 40;
    inline bool isHoveringButton = false;
    inline bool isHoveringButtonBuffer = false;

    void Render();
    void Update();
};


#endif
