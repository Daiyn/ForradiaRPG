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

    string m_title = "";
    int m_x;
    int m_y;
    int m_w;
    int m_h;
    int m_titleBarHeight = 40;
    int m_titleBarMargin = 3;
    int m_margin = 15;
    int m_rowHeight = 25;
    int m_buttonWidth = 160;
    int m_buttonHeight = 35;
    int m_xStartMovingWindow = -1;
    int m_yStartMovingWindow = -1;
    int m_mxStartMovingWindow = -1;
    int m_myStartMovingWindow = -1;
    int m_connectedNPCDialogUniqueNPCID = -1;
    bool m_isMovingWindow = false;
    bool m_destroyWindow = false;

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
