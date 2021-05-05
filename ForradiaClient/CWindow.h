/*+===================================================================
  File:      CWINDOW.H

  Summary:   Describes the base window class providing basic GUI
             window functionality inside the CoreGameplay scene.

  Classes:   CWindow
             CNPCDialog

  Functions: 

  Origin:    Written by Andreas Åkerberg.

  This software is open source and licensed under the MIT License.
===================================================================+*/

#ifndef FORRADIAFORMATION_WINDOW_H
#define FORRADIAFORMATION_WINDOW_H

#include <string>
#include <memory>

using std::string;
using std::unique_ptr;

class CNPCDialog;

/*C+C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C
  Class:    CWindow

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

class CWindow
{
public:

    string m_attrTitle = "";
    int m_x;
    int m_y;
    int m_w;
    int m_h;
    int m_pxTitleBarHeight = 40;
    int m_pxTitleBarMargin = 3;
    int m_pxMargin = 15;
    int m_pxRowHeight = 25;
    int m_pxButtonWidth = 160;
    int m_pxButtonHeight = 35;
    int m_pxXStartMovingWindow = -1;
    int m_pxYStartMovingWindow = -1;
    int m_mxStartMovingWindow = -1;
    int m_myStartMovingWindow = -1;
    int m_uniqueNPCIDCoupled = -1;
    bool m_stateIsMovingWindow = false;
    bool m_activateWindowDestruction = false;

    CWindow() = default;
    CWindow(int _x, int _y, int _w, int _h, int _uniqueNPCID, string _title);

    bool CheckMouseClickInWindow();
    virtual bool HandleMouseClickInWindow();
    bool HandleMouseClickInWindowBase();
    virtual bool HandleMouseReleaseInWindow();
    bool HandleMouseReleaseInWindowBase();
    virtual void Render();
    void RenderBase();
    void Update();

protected:

private:

};


#endif
