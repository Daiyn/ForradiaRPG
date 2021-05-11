#include "CWindow.h"
#include "TextRendering.h"
#include "ImageLoading.h"
#include "Global_Mouse.h"
#include "Global_CurrentMap.h"
#include "Global_SDL.h"
#include "Global_GUIProperties.h"
#include "Global_Mouse.h"
#include "Drawing.h"
#include "CTileFloor.h"
#include "CMap.h"
#include "CTile.h"
#include <memory>

using std::make_unique;
using std::unique_ptr;

CWindow::CWindow(int _x, int _y, int _w, int _h, int _uniqueNPCID, string _title)
{

    m_x = _x;
    m_y = _y;
    m_w = _w;
    m_h = _h;

    m_uniqueNPCIDCoupled = _uniqueNPCID;

    m_attrTitle = _title;

}

void CWindow::Update()
{

    if (m_stateIsMovingWindow)
    {

        int mx = Global::GetMouseX();
        int my = Global::GetMouseY();

        m_x = m_pxXStartMovingWindow + mx - m_mxStartMovingWindow;
        m_y = m_pxYStartMovingWindow + my - m_myStartMovingWindow;

    }

    CPoint pMouse = Global::GetMousePoint();

    int iconCloseWindowSize = m_pxTitleBarHeight - 2 * m_pxTitleBarMargin;

    CRectangle rect = { m_x + m_w - iconCloseWindowSize - m_pxTitleBarMargin, m_y + m_pxTitleBarMargin, iconCloseWindowSize, iconCloseWindowSize };


}

bool CWindow::HandleMouseClickInWindowBase()
{

    if (m_stateIsMovingWindow)
        return true;

    int mx = Global::GetMouseX();
    int my = Global::GetMouseY();

    int iconCloseWindowSize = m_pxTitleBarHeight - 2 * m_pxTitleBarMargin;

    SDL_Rect rect = {m_x + m_w - iconCloseWindowSize - m_pxTitleBarMargin, m_y + m_pxTitleBarMargin, iconCloseWindowSize, iconCloseWindowSize};

    if (mx >= rect.x && my >= rect.y && mx < rect.x + rect.w && my < rect.y + rect.h)
    {

        m_activateWindowDestruction = true;
        return true;

    }

    if (mx >= m_x && my >= m_y && mx < m_x + m_w && my < m_y + m_pxTitleBarHeight)
    {

        m_stateIsMovingWindow = true;
        m_pxXStartMovingWindow = m_x;
        m_pxYStartMovingWindow = m_y;
        m_mxStartMovingWindow = mx;
        m_myStartMovingWindow = my;

        return true;

    }

    return false;

}

bool CWindow::HandleMouseReleaseInWindowBase()
{

    m_stateIsMovingWindow = false;

    int mx = Global::GetMouseX();
    int my = Global::GetMouseY();

    if (mx >= m_x && my >= m_y && mx < m_x + m_w && my < m_y + m_h)
        return true;

    return false;

}

bool CWindow::HandleMouseReleaseInWindow()
{

    bool resultBase = HandleMouseReleaseInWindowBase();

    return resultBase;

}

bool CWindow::CheckMouseClickInWindow()
{

    int mx = Global::GetMouseX();
    int my = Global::GetMouseY();

    if (mx >= m_x && my >= m_y && mx < m_x + m_w && my < m_y + m_h)
        return true;

    if (m_stateIsMovingWindow)
        return true;

    return false;

}

bool CWindow::HandleMouseClickInWindow()
{

    int baseResult = HandleMouseClickInWindowBase();

    int mx = Global::GetMouseX();
    int my = Global::GetMouseY();

    return baseResult;
}

void CWindow::RenderBase()
{

    CRectangle rect = { m_x, m_y, m_w, m_h };

    Drawing::Image(ImagesIDs::WindowBackground, rect);

    SDL_SetRenderDrawColor(Global::sdlRendererDefault, 0, 0, 0, 255);

    SDL_RenderDrawRect(Global::sdlRendererDefault, &rect);

    SDL_SetRenderDrawColor(Global::sdlRendererDefault, 200, 200, 255, 255);

    rect = {m_x, m_y, m_w, m_pxTitleBarHeight};

    SDL_RenderFillRect(Global::sdlRendererDefault, &rect);

    SDL_SetRenderDrawColor(Global::sdlRendererDefault, 0, 0, 0, 255);

    SDL_RenderDrawRect(Global::sdlRendererDefault, &rect);

    int titleTextMargin = m_pxTitleBarHeight / 2 - TextRendering::GetTextHeight() / 2;

    TextRendering::DrawString(m_attrTitle, {0, 0, 0}, m_x + titleTextMargin, m_y + titleTextMargin);

    int iconCloseWindowSize = m_pxTitleBarHeight - 2 * m_pxTitleBarMargin;

    rect = {m_x + m_w - iconCloseWindowSize - m_pxTitleBarMargin, m_y + m_pxTitleBarMargin, iconCloseWindowSize, iconCloseWindowSize};

    SDL_RenderCopy(Global::sdlRendererDefault, ImageLoading::libTextures[ImagesIDs::IconCloseWindow], NULL, &rect);

}

void CWindow::Render()
{

    RenderBase();

}