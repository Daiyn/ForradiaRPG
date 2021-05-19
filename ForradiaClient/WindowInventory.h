/*+===================================================================
  File:      CWINDOWINVENTORY.H

  Summary:   Describes the inventory window class used inside the
             CoreGameplay scene.

  Classes:   CWindowInventory
             CWindow

  Functions: 

  Origin:    Written by Andreas Åkerberg.

  This software is open source and licensed under the MIT License.
===================================================================+*/

#ifndef FORRADIAFORMATION_WINDOWINVENTORY_H
#define FORRADIAFORMATION_WINDOWINVENTORY_H

#include "Window.h"

/*C+C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C
  Class:    CWindowInventory

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

class WindowInventory : public Window
{
public:

    int m_pxSlotSize = 60;
    int m_pxMargin = 2;

    WindowInventory();

    bool HandleMouseClickInWindow() override;
    bool HandleMouseReleaseInWindow() override;
    void Render() override;

protected:

private:

};


#endif
