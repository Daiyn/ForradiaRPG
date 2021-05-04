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

    m_connectedNPCDialogUniqueNPCID = _uniqueNPCID;

    //m_dialog = _dialog;

    m_title = _title;

}

void CWindow::Update()
{

    if (m_isMovingWindow)
    {

        int mx = Global::GetMouseX();
        int my = Global::GetMouseY();

        m_x = m_xStartMovingWindow + mx - m_mxStartMovingWindow;
        m_y = m_yStartMovingWindow + my - m_myStartMovingWindow;

    }

    CPoint pMouse = Global::GetMousePoint();

    int iconCloseWindowSize = m_titleBarHeight - 2 * m_titleBarMargin;

    CRectangle rect = { m_x + m_w - iconCloseWindowSize - m_titleBarMargin, m_y + m_titleBarMargin, iconCloseWindowSize, iconCloseWindowSize };

    if (rect.ContainsPoint(pMouse))
        Cursor::isHoveringButton = true;

}

bool CWindow::HandleMouseClickInWindowBase()
{

    if (m_isMovingWindow)
        return true;

    int mx = Global::GetMouseX();
    int my = Global::GetMouseY();

    int iconCloseWindowSize = m_titleBarHeight - 2 * m_titleBarMargin;

    SDL_Rect rect = {m_x + m_w - iconCloseWindowSize - m_titleBarMargin, m_y + m_titleBarMargin, iconCloseWindowSize, iconCloseWindowSize};

    if (mx >= rect.x && my >= rect.y && mx < rect.x + rect.w && my < rect.y + rect.h)
    {

        m_destroyWindow = true;
        return true;

    }

    if (mx >= m_x && my >= m_y && mx < m_x + m_w && my < m_y + m_titleBarHeight)
    {

        m_isMovingWindow = true;
        m_xStartMovingWindow = m_x;
        m_yStartMovingWindow = m_y;
        m_mxStartMovingWindow = mx;
        m_myStartMovingWindow = my;

        return true;

    }

    return false;

}

bool CWindow::HandleMouseReleaseInWindowBase()
{

    m_isMovingWindow = false;

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

    if (m_isMovingWindow)
        return true;

    return false;

}

bool CWindow::HandleMouseClickInWindow()
{

    int baseResult = HandleMouseClickInWindowBase();

    int mx = Global::GetMouseX();
    int my = Global::GetMouseY();

    

    for (auto it : Global::currentMap->m_listAllNPCs)
    {
        if (it.get().m_uniqueID == m_connectedNPCDialogUniqueNPCID)
        {
            CNPCDialog& dialog = *it.get().m_talkCurrentDialog;




            for (int i = 0; i < dialog.getCurrentPhrase().m_optAnswers.size(); i++)
            {

                SDL_Rect rectButton = { m_x + m_margin + i * (m_buttonWidth + m_margin), m_y + m_h - m_buttonHeight - m_margin, m_buttonWidth, m_buttonHeight };

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

                            if (Global::currentMap->m_2DTiles[mapx][mapy]->m_floorsArray[SURFACE_FLOOR]->m_floorObjectsArr[jjj] == NULL)
                            {

                                Global::currentMap->m_2DTiles[mapx][mapy]->m_floorsArray[SURFACE_FLOOR]->m_floorObjectsArr[jjj] = make_unique<CObject>(CObject(objectIndex, { mapx, mapy }));
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

                        m_destroyWindow = true;

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

    SDL_SetRenderDrawColor(Global::renderer, 0, 0, 0, 255);

    SDL_RenderDrawRect(Global::renderer, &rect);

    SDL_SetRenderDrawColor(Global::renderer, 200, 200, 255, 255);

    rect = {m_x, m_y, m_w, m_titleBarHeight};

    SDL_RenderFillRect(Global::renderer, &rect);

    SDL_SetRenderDrawColor(Global::renderer, 0, 0, 0, 255);

    SDL_RenderDrawRect(Global::renderer, &rect);

    int titleTextMargin = m_titleBarHeight / 2 - TextRendering::GetTextHeight() / 2;

    TextRendering::DrawString(m_title, {0, 0, 0}, m_x + titleTextMargin, m_y + titleTextMargin);

    int iconCloseWindowSize = m_titleBarHeight - 2 * m_titleBarMargin;

    rect = {m_x + m_w - iconCloseWindowSize - m_titleBarMargin, m_y + m_titleBarMargin, iconCloseWindowSize, iconCloseWindowSize};

    SDL_RenderCopy(Global::renderer, ImageLoading::texturesArray[ID_ICON_CLOSE_WINDOW], NULL, &rect);


}

void CWindow::Render()
{

    RenderBase();



    for (auto it : Global::currentMap->m_listAllNPCs)
    {
        if (it.get().m_uniqueID == m_connectedNPCDialogUniqueNPCID)
        {
            CNPCDialog& dialog = *it.get().m_talkCurrentDialog;

            for (int i = 0; i < dialog.getCurrentPhrase().m_txtblockTextLines.size(); i++)
            {

                string str = dialog.getCurrentPhrase().m_txtblockTextLines[i];
                TextRendering::DrawString(str, { 0, 0, 0 }, m_x + m_margin, m_y + m_titleBarHeight + m_margin + i * m_rowHeight);

            }

            for (int i = 0; i < dialog.getCurrentPhrase().m_optAnswers.size(); i++)
            {

                string strAnswer = dialog.getCurrentPhrase().m_optAnswers[i].m_answerText;

                SDL_Rect rectButton = { m_x + m_margin + i * (m_buttonWidth + m_margin), m_y + m_h - m_buttonHeight - m_margin, m_buttonWidth, m_buttonHeight };

                SDL_SetRenderDrawColor(Global::renderer, 255, 200, 200, 255);

                SDL_RenderFillRect(Global::renderer, &rectButton);

                SDL_SetRenderDrawColor(Global::renderer, 0, 0, 0, 255);

                SDL_RenderDrawRect(Global::renderer, &rectButton);

                TextRendering::DrawString(strAnswer, { 0, 0, 0 }, rectButton.x, rectButton.y);

            }


        }

    }

}