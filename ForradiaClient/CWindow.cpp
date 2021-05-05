#include "CWindow.h"
#include "TextRendering.h"
#include "ImageLoading.h"
#include "Global_Mouse.h"
#include "Global_CurrentMap.h"
#include "Global_SDL.h"
#include "Global_GUIProperties.h"
#include "Global_Mouse.h"
#include "Cursor.h"
#include "Drawing.h"
#include "CNPCDialogPhrase.h"
#include "CNPCDialog.h"
#include "CNPCDialogPhraseAnswerOption.h"
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

    if (rect.ContainsPoint(pMouse))
        Cursor::isHoveringButton = true;

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

    for (auto it : Global::contentCurrentMap->m_mirrorAllNPCs)
    {
        if (it.get().m_uniqueID == m_uniqueNPCIDCoupled)
        {
            CNPCDialog& dialog = *it.get().m_interactiveCurrentDialog;

            for (int i = 0; i < dialog.getCurrentPhrase().m_optAnswers.size(); i++)
            {

                SDL_Rect rectButton = { m_x + m_pxMargin + i * (m_pxButtonWidth + m_pxMargin), m_y + m_h - m_pxButtonHeight - m_pxMargin, m_pxButtonWidth, m_pxButtonHeight };

                if (mx >= rectButton.x && my >= rectButton.y && mx < rectButton.x + rectButton.w &&
                    my < rectButton.y + rectButton.h)
                {

                    std::tuple<int, int, int> instruction = dialog.getCurrentPhrase().m_optAnswers[i].m_instructObjectCreation;

                    if (std::get<0>(instruction) != -1 && std::get<1>(instruction) != -1 && std::get<2>(instruction) != -1)
                    {

                        int mapx = std::get<0>(instruction);
                        int mapy = std::get<1>(instruction);
                        int objectIndex = std::get<2>(instruction);

                        for (int jjj = 0; jjj < CTileFloor::MAX_OBJECTS_ON_FLOOR; jjj++)
                        {

                            if (Global::contentCurrentMap->m_tilesGrid[mapx][mapy]->m_floorsArray[SURFACE_FLOOR]->m_containedObjects[jjj] == NULL)
                            {

                                Global::contentCurrentMap->m_tilesGrid[mapx][mapy]->m_floorsArray[SURFACE_FLOOR]->m_containedObjects[jjj] = make_unique<CObject>(CObject(objectIndex, { mapx, mapy }));
                                break;

                            }

                        }

                    }

                    if (dialog.getCurrentPhrase().m_optAnswers[i].m_idxAnswerMakeJumpToPhrase != -1)
                    {

                        dialog.m_iterCurrentPhrase = dialog.getCurrentPhrase().m_optAnswers[i].m_idxAnswerMakeJumpToPhrase;

                    }
                    else
                    {

                        m_activateWindowDestruction = true;

                    }

                    return true;

                }

            }

            break;
        }
    }

    return baseResult;
}

void CWindow::RenderBase()
{

    CRectangle rect = { m_x, m_y, m_w, m_h };

    Drawing::Image(ID_WINDOW_BACK, rect);

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

    SDL_RenderCopy(Global::sdlRendererDefault, ImageLoading::libTextures[ID_ICON_CLOSE_WINDOW], NULL, &rect);

}

void CWindow::Render()
{

    RenderBase();

    for (auto it : Global::contentCurrentMap->m_mirrorAllNPCs)
    {
        if (it.get().m_uniqueID == m_uniqueNPCIDCoupled)
        {
            CNPCDialog& dialog = *it.get().m_interactiveCurrentDialog;

            for (int i = 0; i < dialog.getCurrentPhrase().m_textblockTextLines.size(); i++)
            {

                string str = dialog.getCurrentPhrase().m_textblockTextLines[i];
                TextRendering::DrawString(str, { 0, 0, 0 }, m_x + m_pxMargin, m_y + m_pxTitleBarHeight + m_pxMargin + i * m_pxRowHeight);

            }

            for (int i = 0; i < dialog.getCurrentPhrase().m_optAnswers.size(); i++)
            {

                string strAnswer = dialog.getCurrentPhrase().m_optAnswers[i].m_answerText;

                SDL_Rect rectButton = { m_x + m_pxMargin + i * (m_pxButtonWidth + m_pxMargin), m_y + m_h - m_pxButtonHeight - m_pxMargin, m_pxButtonWidth, m_pxButtonHeight };

                SDL_SetRenderDrawColor(Global::sdlRendererDefault, 255, 200, 200, 255);

                SDL_RenderFillRect(Global::sdlRendererDefault, &rectButton);

                SDL_SetRenderDrawColor(Global::sdlRendererDefault, 0, 0, 0, 255);

                SDL_RenderDrawRect(Global::sdlRendererDefault, &rectButton);

                TextRendering::DrawString(strAnswer, { 0, 0, 0 }, rectButton.x, rectButton.y);

            }

        }

    }

}