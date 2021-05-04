#include "Forradia.h"
#include "FPSCounter.h"
#include "ImageLoading.h"
#include "Cursor.h"
#include "Global_GameLoop.h"
#include "CSceneStartScreen.h"
#include "SDLInitialization.h"
#include "Drawing.h"
#include "KeyboardInput.h"
#include "MouseInput.h"
#include "TextRendering.h"
#include "DataLoading.h"
#include "Global_CurrentScene.h"
#include "Global_SDL.h"
#include "Global_Player.h"
#include "Global_WorldMap.h"
#include "ImageLoading.h"
#include <memory>

using std::make_unique;

void Forradia::Initialize()
{

    SDLInitialization::Initialize();
    DataLoading::LoadDescriptions();
    ImageLoading::LoadImages();
    TextRendering::Initialize();
    Drawing::UseDefaultRenderer();
    Global::currentScene = make_unique<CSceneStartScreen>(CSceneStartScreen());

}

void Forradia::Run()
{

    while (!Global::quit)
    {

        HandleEvents();

        if (Global::restartGameLoop)
        {
            Global::restartGameLoop = false;
            continue;
        }

        Update();
        Render();

    }

    Global::DestroySDLObjects();

}

void Forradia::HandleEvents()
{

    while (SDL_PollEvent(&event))
    {

        switch (event.type)
        {

            case SDL_QUIT:
                Global::quit = true;
                break;

            case SDL_KEYDOWN:

                if (event.key.keysym.sym == SDLK_LALT)
                    altKeyPressed = true;

                if (event.key.keysym.sym == SDLK_RETURN
                    && altKeyPressed)
                    Global::ToggleFullscreen();

                Global::currentScene->DoKeyDown(event.key.keysym.sym);
                break;

            case SDL_KEYUP:

                if (event.key.keysym.sym == SDLK_LALT)
                    altKeyPressed = false;

                Global::currentScene->DoKeyUp(event.key.keysym.sym);
                break;

            case SDL_MOUSEBUTTONDOWN:
                Global::currentScene->DoMouseDown(event.button.button);
                break;

            case SDL_MOUSEBUTTONUP:
                Global::currentScene->DoMouseUp(event.button.button);
                break;

        }

    }

}

void Forradia::Update() 
{

    Global::currentScene->Update();
    FPSCounter::Update();
    Cursor::Update();

}

void Forradia::Render()
{

    Global::currentScene->Render();
    FPSCounter::Render();
    Cursor::Render();

    Drawing::PresentToScreen();

}