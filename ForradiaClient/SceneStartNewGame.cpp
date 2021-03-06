#include "SceneStartNewGame.h"
#include "SceneCoreGameplay.h"
#include "SceneMainMenu.h"
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
#include "Global_GameSettings.h"
#include "Global_CurrentMap.h"
#include <memory>
#include "TileRendering.h"
#include "ObjectsRendering.h"
#include "Tile.h"
#include <memory>

#define FOR(x,y,z) for (int x = y; x < z; x++)

using std::make_unique;

SceneStartNewGame::SceneStartNewGame()
{

    m_gamedataMap = make_unique<Map>(Global::tilesMapSize);

    SDL_DestroyRenderer(Global::sdlRendererFullMapRender);
    Global::sdlRendererFullMapRender = nullptr;

    if (m_gamedataMap->m_texFullMapRender != NULL)
        SDL_DestroyTexture(m_gamedataMap->m_texFullMapRender);

    m_gamedataMap->m_texFullMapRender = NULL;

    m_doGenerateMapPreview = true;
    m_isMapGenerated = false;

}

void SceneStartNewGame::DoMouseDown(Uint8 button)
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





    if (mx >= rectBackButton.x && my >= rectBackButton.y && mx < rectBackButton.x + rectBackButton.w &&
        my < rectBackButton.y + rectBackButton.h)
    {
        Global::ChangeScene(make_unique<SceneMainMenu>(SceneMainMenu()));
    }

    if (mx >= rectGenerateButton.x && my >= rectGenerateButton.y && mx < rectGenerateButton.x + rectGenerateButton.w &&
        my < rectGenerateButton.y + rectGenerateButton.h)
    {

        m_gamedataMap = make_unique<Map>(Global::tilesMapSize);

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

        Global::ChangeScene(make_unique<SceneCoreGameplay>(SceneCoreGameplay()));

    }


}

void SceneStartNewGame::Update()
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


}

void SceneStartNewGame::GenerateMapPreview()
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

void SceneStartNewGame::Render()
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
    case 1:
    case 2:
    case 3:
    case 4:
    case 5:
    case 6:
    case 7:
    case 8:
        SDL_RenderCopy(Global::sdlRendererDefault, ImageLoading::libTextures[ImagesIDs::ForradiaStartText0], NULL, &rectText);
        break;

    }

    string textBack = "Back";

    int imgIndex = 0;

    if (mx >= rectBackButton.x && my >= rectBackButton.y && mx < rectBackButton.x + rectBackButton.w && my < rectBackButton.y + rectBackButton.h)
        imgIndex = ImagesIDs::MenuButtonBackHovered;
    else
        imgIndex = ImagesIDs::MenuButtonBackground;

    SDL_RenderCopy(Global::sdlRendererDefault, ImageLoading::libTextures[imgIndex], NULL, &rectBackButton);

    int xmid = rectBackButton.x + rectBackButton.w / 2;
    int xtextpos = xmid - TextRendering::GetTextWidth(textBack) / 2;

    int ymid = rectBackButton.y + rectBackButton.h / 2;
    int ytextpos = ymid - TextRendering::GetTextHeight() / 2;

    TextRendering::DrawString(textBack.c_str(), {0, 0, 0}, xtextpos, ytextpos);

    string textGenerate = "Generate new map";

    if (mx >= rectGenerateButton.x && my >= rectGenerateButton.y && mx < rectGenerateButton.x + rectGenerateButton.w && my < rectGenerateButton.y + rectGenerateButton.h)
        imgIndex = ImagesIDs::MenuButtonBackHovered;
    else
        imgIndex = ImagesIDs::MenuButtonBackground;

    SDL_RenderCopy(Global::sdlRendererDefault, ImageLoading::libTextures[imgIndex], NULL, &rectGenerateButton);

    xmid = rectGenerateButton.x + rectGenerateButton.w / 2;
    xtextpos = xmid - TextRendering::GetTextWidth(textGenerate) / 2;

    ymid = rectGenerateButton.y + rectGenerateButton.h / 2;
    ytextpos = ymid - TextRendering::GetTextHeight() / 2;

    TextRendering::DrawString(textGenerate.c_str(), {0, 0, 0}, xtextpos, ytextpos);

    string textPlay = "Play";

    if (mx >= rectPlayButton.x && my >= rectPlayButton.y && mx < rectPlayButton.x + rectPlayButton.w && my < rectPlayButton.y + rectPlayButton.h)
        imgIndex = ImagesIDs::MenuButtonBackHovered;
    else
        imgIndex = ImagesIDs::MenuButtonBackground;

    SDL_RenderCopy(Global::sdlRendererDefault, ImageLoading::libTextures[imgIndex], NULL, &rectPlayButton);

    xmid = rectPlayButton.x + rectPlayButton.w / 2;
    xtextpos = xmid - TextRendering::GetTextWidth(textPlay) / 2;

    ymid = rectPlayButton.y + rectPlayButton.h / 2;
    ytextpos = ymid - TextRendering::GetTextHeight() / 2;

    TextRendering::DrawString(textPlay.c_str(), {0, 0, 0}, xtextpos, ytextpos);


    RenderMapPreview();

}

void SceneStartNewGame::RenderMapPreview()
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

    SDL_RenderCopy(Global::sdlRendererDefault, ImageLoading::libTextures[ImagesIDs::FullMapFrameBackground], NULL, &rectFrame);

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