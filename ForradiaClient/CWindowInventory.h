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

#include "CWindow.h"

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

class CWindowInventory : public CWindow
{
public:

    int m_slotSize = 60;
    int m_margin = 2;

    CWindowInventory();

    bool HandleMouseClickInWindow() override;
    bool HandleMouseReleaseInWindow() override;
    void Render() override;

protected:

private:

};


#endif
