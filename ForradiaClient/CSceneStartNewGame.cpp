#include "CSceneStartNewGame.h"
#include "CSceneCoreGameplay.h"
#include "CSceneMainMenu.h"
#include "ImageLoading.h"
#include "Utilities.h"
#include "TextRendering.h"
#include "Drawing.h"
#include "Global_MapPreviewSize.h"
#include "Global_Canvas.h"
#include "Global_GUIProperties.h"
#include "Global_MapSize.h"
#include "Global_SDL.h"
#include "Global_CurrentScene.h"
#include "Global_Mouse.h"
#include "Cursor.h"
#include "Global_GameSettings.h"
#include "Global_CurrentMap.h"
#include <memory>
#include "TileRendering.h"
#include "ObjectsRendering.h"
#include "CTile.h"
#include <memory>

#define FOR(x,y,z) for (int x = y; x < z; x++)

using std::make_unique;

CSceneStartNewGame::CSceneStartNewGame()
{

    m_gamedataMap = make_unique<CMap>(Global::tilesMapSize);

    SDL_DestroyRenderer(Global::sdlRendererFullMapRender);
    Global::sdlRendererFullMapRender = nullptr;

    if (m_gamedataMap->m_texFullMapRender != NULL)
        SDL_DestroyTexture(m_gamedataMap->m_texFullMapRender);

    m_gamedataMap->m_texFullMapRender = NULL;

    m_doGenerateMapPreview = true;
    m_isMapGenerated = false;

}

void CSceneStartNewGame::DoMouseDown(Uint8 button)
{

    int mx = Global::GetMouseX();
    int my = Global::GetMouseY();

    SDL_Rect rectBackButton = { Global::attrMenuButtonMargin * 3,
                      Global::GetCanvasHeight() - Global::attrMenuButtonHeight - Global::attrMenuButtonMargin * 3,
                      Global::attrMenuButtonWidth,
                      Global::attrMenuButtonHeight };

    SDL_Rect rectGenerateButton = { Global::GetCanvasWidth() / 2 - Global::attrMenuButtonWidth / 2,
         Global::GetCanvasHeight() - Global::attrMenuButtonHeight - Global::attrMenuButtonMargin * 3,
        Global::attrMenuButtonWidth,
        Global::attrMenuButtonHeight };

    SDL_Rect rectPlayButton = { Global::GetCanvasWidth() - Global::attrMenuButtonWidth - Global::attrMenuButtonMargin * 3,
                      Global::GetCanvasHeight() - Global::attrMenuButtonHeight - Global::attrMenuButtonMargin * 3,
                      Global::attrMenuButtonWidth,
                      Global::attrMenuButtonHeight };


    SDL_Rect rectOptionIconGameStyleCasual = { rectPlayButton.x,
                                                Global::GetCanvasHeight() / 2,
                                                Global::attrOptionIconSize,
                                                Global::attrOptionIconSize };

    SDL_Rect rectOptionIconGameStyleChallenging = { rectPlayButton.x,
                                                    Global::GetCanvasHeight() / 2 + Global::attrOptionIconSize + Global::attrMargin,
                                                    Global::attrOptionIconSize,
                                                    Global::attrOptionIconSize };



    if (mx >= rectBackButton.x && my >= rectBackButton.y && mx < rectBackButton.x + rectBackButton.w &&
        my < rectBackButton.y + rectBackButton.h)
    {
        Global::ChangeScene(make_unique<CSceneMainMenu>(CSceneMainMenu()));
    }

    if (mx >= rectGenerateButton.x && my >= rectGenerateButton.y && mx < rectGenerateButton.x + rectGenerateButton.w &&
        my < rectGenerateButton.y + rectGenerateButton.h)
    {

        m_gamedataMap = make_unique<CMap>(Global::tilesMapSize);

        SDL_DestroyRenderer(Global::sdlRendererFullMapRender);
        Global::sdlRendererFullMapRender = nullptr;

        SDL_DestroyTexture(m_gamedataMap->m_texFullMapRender);
        m_gamedataMap->m_texFullMapRender = NULL;

        m_doGenerateMapPreview = true;
        m_isMapGenerated = false;
    }

    if (mx >= rectPlayButton.x && my >= rectPlayButton.y && mx < rectPlayButton.x + rectPlayButton.w &&
        my < rectPlayButton.y + rectPlayButton.h)
    {

        Global::ChangeScene(make_unique<CSceneCoreGameplay>(CSceneCoreGameplay()));

    }

    if (mx >= rectOptionIconGameStyleCasual.x && my >= rectOptionIconGameStyleCasual.y && mx < rectOptionIconGameStyleCasual.x + rectOptionIconGameStyleCasual.w &&
        my < rectOptionIconGameStyleCasual.y + rectOptionIconGameStyleCasual.h)
    {

        Global::settingGameMode = 0;

    }

    if (mx >= rectOptionIconGameStyleChallenging.x && my >= rectOptionIconGameStyleChallenging.y && mx < rectOptionIconGameStyleChallenging.x + rectOptionIconGameStyleChallenging.w &&
        my < rectOptionIconGameStyleChallenging.y + rectOptionIconGameStyleChallenging.h)
    {

        Global::settingGameMode = 1;

    }

}

void CSceneStartNewGame::Update()
{
    
    if (m_doGenerateMapPreview)
        GenerateMapPreview();

    int mx = Global::GetMouseX();
    int my = Global::GetMouseY();

    SDL_Rect rectBackButton = { Global::attrMenuButtonMargin * 3,
                                  Global::GetCanvasHeight() - Global::attrMenuButtonHeight - Global::attrMenuButtonMargin * 3,
                                  Global::attrMenuButtonWidth,
                                  Global::attrMenuButtonHeight };

    SDL_Rect rectGenerateButton = { Global::GetCanvasWidth() / 2 - Global::attrMenuButtonWidth / 2,
                                    Global::GetCanvasHeight() - Global::attrMenuButtonHeight - Global::attrMenuButtonMargin * 3,
                                    Global::attrMenuButtonWidth,
                                    Global::attrMenuButtonHeight };

    SDL_Rect rectPlayButton = { Global::GetCanvasWidth() - Global::attrMenuButtonWidth - Global::attrMenuButtonMargin * 3,
                                  Global::GetCanvasHeight() - Global::attrMenuButtonHeight - Global::attrMenuButtonMargin * 3,
                                  Global::attrMenuButtonWidth,
                                  Global::attrMenuButtonHeight };

    Cursor::isHoveringButton = false;

    if (mx >= rectBackButton.x && my >= rectBackButton.y && mx < rectBackButton.x + rectBackButton.w && my < rectBackButton.y + rectBackButton.h)
    {
        Cursor::isHoveringButton = true;
    }

    if (mx >= rectGenerateButton.x && my >= rectGenerateButton.y && mx < rectGenerateButton.x + rectGenerateButton.w && my < rectGenerateButton.y + rectGenerateButton.h)
    {
        Cursor::isHoveringButton = true;
    }

    if (mx >= rectPlayButton.x && my >= rectPlayButton.y && mx < rectPlayButton.x + rectPlayButton.w && my < rectPlayButton.y + rectPlayButton.h)
    {
        Cursor::isHoveringButton = true;
    }

}

void CSceneStartNewGame::GenerateMapPreview()
{

    if (!Global::sdlRendererFullMapRender) {
        Global::sdlRendererFullMapRender = SDL_CreateSoftwareRenderer(m_gamedataMap->m_imgFullMapRender);
        SDL_SetRenderDrawBlendMode(Global::sdlRendererFullMapRender, SDL_BLENDMODE_BLEND);
    }

    // Generate map preview
    //==========================


    Drawing::UseFullMapRenderer();

    ImageLoading::ClearMapPreviewTextures();
    ImageLoading::CreateMapPreviewTextures();

    double tileSize = (double)Global::pxFullMapRenderSize / Global::tilesMapSize;

    Global::contentCurrentMap = move(m_gamedataMap);

    FOR(mapy, 1, Global::tilesMapSize - 1)
    {
        FOR(mapx, 1, Global::tilesMapSize - 1)
        {

            TileRendering::RenderTileGround(tileSize, mapx, mapy, { mapx, mapy });
            ObjectsRendering::RenderTileObjects(tileSize, mapx, mapy, { mapx, mapy });

        }
    }

    Drawing::UseDefaultRenderer();


    //=====================


    m_isMapGenerated = true;

}

void CSceneStartNewGame::Render()
{

    SDL_Rect rectBackButton = { Global::attrMenuButtonMargin * 3,
                                  Global::GetCanvasHeight() - Global::attrMenuButtonHeight - Global::attrMenuButtonMargin * 3,
                                  Global::attrMenuButtonWidth,
                                  Global::attrMenuButtonHeight };

    SDL_Rect rectGenerateButton = { Global::GetCanvasWidth() / 2 - Global::attrMenuButtonWidth / 2,
                                      Global::GetCanvasHeight() - Global::attrMenuButtonHeight - Global::attrMenuButtonMargin * 3,
                                      Global::attrMenuButtonWidth,
                                      Global::attrMenuButtonHeight };

    SDL_Rect rectPlayButton = { Global::GetCanvasWidth() - Global::attrMenuButtonWidth - Global::attrMenuButtonMargin * 3,
                                  Global::GetCanvasHeight() - Global::attrMenuButtonHeight - Global::attrMenuButtonMargin * 3,
                                  Global::attrMenuButtonWidth,
                                  Global::attrMenuButtonHeight };

    SDL_Rect rectOptionIconGameStyleCasual = { rectPlayButton.x,
                                                Global::GetCanvasHeight() / 2,
                                                Global::attrOptionIconSize,
                                                Global::attrOptionIconSize };

    SDL_Rect rectOptionIconGameStyleChallenging = { rectPlayButton.x,
                                                    Global::GetCanvasHeight() / 2 + Global::attrOptionIconSize + Global::attrMargin,
                                                    Global::attrOptionIconSize,
                                                    Global::attrOptionIconSize};


    int mx = Global::GetMouseX();
    int my = Global::GetMouseY();

    int animIndex_text = Utilities::GenerateAnimationFrameIndex(19, 90);

    if (animIndex_text > 8)
        animIndex_text = 0;

    Drawing::FilledRect(Global::attrBackColorR, Global::attrBackColorG, Global::attrBackColorB, 0, 0, Global::GetCanvasWidth(), Global::GetCanvasHeight());

    int titleW = 766 / 3 / 1600.0 * Global::GetCanvasWidth();
    int titleH = 342 / 3 / 900.0 * Global::GetCanvasHeight();
    int titleX = Global::GetCanvasWidth() / 2 - titleW / 2;
    int titleY = titleH/2;

    SDL_Rect rectText = {titleX, titleY, titleW, titleH};

    switch (animIndex_text)
    {

    case 0:
        SDL_RenderCopy(Global::sdlRendererDefault, ImageLoading::libTextures[ID_FORRADIA_START_TEXT_0], NULL, &rectText);
        break;
    case 1:
        SDL_RenderCopy(Global::sdlRendererDefault, ImageLoading::libTextures[ID_FORRADIA_START_TEXT_1], NULL, &rectText);
        break;
    case 2:
        SDL_RenderCopy(Global::sdlRendererDefault, ImageLoading::libTextures[ID_FORRADIA_START_TEXT_2], NULL, &rectText);
        break;
    case 3:
        SDL_RenderCopy(Global::sdlRendererDefault, ImageLoading::libTextures[ID_FORRADIA_START_TEXT_3], NULL, &rectText);
        break;
    case 4:
        SDL_RenderCopy(Global::sdlRendererDefault, ImageLoading::libTextures[ID_FORRADIA_START_TEXT_4], NULL, &rectText);
        break;
    case 5:
        SDL_RenderCopy(Global::sdlRendererDefault, ImageLoading::libTextures[ID_FORRADIA_START_TEXT_5], NULL, &rectText);
        break;
    case 6:
        SDL_RenderCopy(Global::sdlRendererDefault, ImageLoading::libTextures[ID_FORRADIA_START_TEXT_6], NULL, &rectText);
        break;
    case 7:
        SDL_RenderCopy(Global::sdlRendererDefault, ImageLoading::libTextures[ID_FORRADIA_START_TEXT_7], NULL, &rectText);
        break;
    case 8:
        SDL_RenderCopy(Global::sdlRendererDefault, ImageLoading::libTextures[ID_FORRADIA_START_TEXT_8], NULL, &rectText);
        break;

    }

    SDL_Rect rectTitle = {0, 0, 300 / 1600.0 * Global::GetCanvasWidth(), 60 / 900.0 * Global::GetCanvasHeight() };

    SDL_RenderCopy(Global::sdlRendererDefault, ImageLoading::libTextures[ID_TITLE_START_NEW_GAME], NULL, &rectTitle);

    string textBack = "Back";

    int imgIndex = 0;

    if (mx >= rectBackButton.x && my >= rectBackButton.y && mx < rectBackButton.x + rectBackButton.w && my < rectBackButton.y + rectBackButton.h)
        imgIndex = ID_MENU_BUTTON_BACK_HOVERED;
    else
        imgIndex = ID_MENU_BUTTON_BACK;

    SDL_RenderCopy(Global::sdlRendererDefault, ImageLoading::libTextures[imgIndex], NULL, &rectBackButton);

    int xmid = rectBackButton.x + rectBackButton.w / 2;
    int xtextpos = xmid - TextRendering::GetTextWidth(textBack) / 2;

    int ymid = rectBackButton.y + rectBackButton.h / 2;
    int ytextpos = ymid - TextRendering::GetTextHeight() / 2;

    TextRendering::DrawString(textBack.c_str(), {0, 0, 0}, xtextpos, ytextpos);

    string textGenerate = "Generate new map";

    if (mx >= rectGenerateButton.x && my >= rectGenerateButton.y && mx < rectGenerateButton.x + rectGenerateButton.w && my < rectGenerateButton.y + rectGenerateButton.h)
        imgIndex = ID_MENU_BUTTON_BACK_HOVERED;
    else
        imgIndex = ID_MENU_BUTTON_BACK;

    SDL_RenderCopy(Global::sdlRendererDefault, ImageLoading::libTextures[imgIndex], NULL, &rectGenerateButton);

    xmid = rectGenerateButton.x + rectGenerateButton.w / 2;
    xtextpos = xmid - TextRendering::GetTextWidth(textGenerate) / 2;

    ymid = rectGenerateButton.y + rectGenerateButton.h / 2;
    ytextpos = ymid - TextRendering::GetTextHeight() / 2;

    TextRendering::DrawString(textGenerate.c_str(), {0, 0, 0}, xtextpos, ytextpos);

    string textPlay = "Play";

    if (mx >= rectPlayButton.x && my >= rectPlayButton.y && mx < rectPlayButton.x + rectPlayButton.w && my < rectPlayButton.y + rectPlayButton.h)
        imgIndex = ID_MENU_BUTTON_BACK_HOVERED;
    else
        imgIndex = ID_MENU_BUTTON_BACK;

    SDL_RenderCopy(Global::sdlRendererDefault, ImageLoading::libTextures[imgIndex], NULL, &rectPlayButton);

    xmid = rectPlayButton.x + rectPlayButton.w / 2;
    xtextpos = xmid - TextRendering::GetTextWidth(textPlay) / 2;

    ymid = rectPlayButton.y + rectPlayButton.h / 2;
    ytextpos = ymid - TextRendering::GetTextHeight() / 2;

    TextRendering::DrawString(textPlay.c_str(), {0, 0, 0}, xtextpos, ytextpos);

    xtextpos = rectOptionIconGameStyleCasual.x;
    ytextpos = rectOptionIconGameStyleCasual.y - Global::attrOptionIconSize;

    TextRendering::DrawString("Game Style", { 0, 0, 0 }, xtextpos, ytextpos);

    if (Global::settingGameMode == 0)
        SDL_RenderCopy(Global::sdlRendererDefault, ImageLoading::libTextures[ID_OPTION_ICON_SELECTED], NULL, &rectOptionIconGameStyleCasual);
    else
        SDL_RenderCopy(Global::sdlRendererDefault, ImageLoading::libTextures[ID_OPTION_ICON_UNSELECTED], NULL, &rectOptionIconGameStyleCasual);

    xtextpos = rectOptionIconGameStyleCasual.x + Global::attrOptionIconSize + Global::attrMargin;
    ytextpos = rectOptionIconGameStyleCasual.y + Global::attrOptionIconSize/2 - TextRendering::GetTextHeight()/2;

    TextRendering::DrawString("Casual", { 0, 0, 0 }, xtextpos, ytextpos);

    if (Global::settingGameMode == 1)
        SDL_RenderCopy(Global::sdlRendererDefault, ImageLoading::libTextures[ID_OPTION_ICON_SELECTED], NULL, &rectOptionIconGameStyleChallenging);
    else
        SDL_RenderCopy(Global::sdlRendererDefault, ImageLoading::libTextures[ID_OPTION_ICON_UNSELECTED], NULL, &rectOptionIconGameStyleChallenging);

    xtextpos = rectOptionIconGameStyleCasual.x + Global::attrOptionIconSize + Global::attrMargin;
    ytextpos = rectOptionIconGameStyleChallenging.y + Global::attrOptionIconSize / 2 - TextRendering::GetTextHeight() / 2;

    TextRendering::DrawString("Challenging", { 0, 0, 0 }, xtextpos, ytextpos);

    RenderMapPreview();

}

void CSceneStartNewGame::RenderMapPreview()
{

    int xmid = Global::GetCanvasWidth() / 2;
    int ymid = Global::GetCanvasHeight() / 2;

    int mapPreviewSizeScaled = (Global::pxFullMapRenderSize / 1600.0 * Global::GetCanvasWidth()
        + Global::pxFullMapRenderSize / 900.0 * Global::GetCanvasHeight())/2;

    int xLeft = xmid - mapPreviewSizeScaled / 2;
    int yTop = ymid - mapPreviewSizeScaled / 2;

    SDL_Rect rectFrame = {xLeft - m_attrBoxBorderThickness,
                          yTop - m_attrBoxBorderThickness,
                          mapPreviewSizeScaled + 2 * m_attrBoxBorderThickness,
                          mapPreviewSizeScaled + 2 * m_attrBoxBorderThickness };

    SDL_RenderCopy(Global::sdlRendererDefault, ImageLoading::libTextures[ID_MAP_PREVIEW_BACK], NULL, &rectFrame);

    rectFrame.x = xLeft - 5;
    rectFrame.y = yTop - 5;
    rectFrame.w = mapPreviewSizeScaled + 10;
    rectFrame.h = mapPreviewSizeScaled + 10;

    SDL_SetRenderDrawColor(Global::sdlRendererDefault, 0, 0, 0, 255);

    SDL_RenderFillRect(Global::sdlRendererDefault, &rectFrame);

    SDL_Rect rectMapPreview = { xLeft,
                                yTop,
                                mapPreviewSizeScaled,
                                mapPreviewSizeScaled };

    if (m_doGenerateMapPreview && m_isMapGenerated)
    {

        Global::contentCurrentMap->m_texFullMapRender = SDL_CreateTextureFromSurface(Global::sdlRendererDefault, Global::contentCurrentMap->m_imgFullMapRender);
        m_doGenerateMapPreview = false;
    }

    if (Global::contentCurrentMap->m_texFullMapRender != NULL)
        SDL_RenderCopy(Global::sdlRendererDefault, Global::contentCurrentMap->m_texFullMapRender, NULL, &rectMapPreview);

}