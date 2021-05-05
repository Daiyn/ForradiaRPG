#include "Forradia.h"
#include "FPSCounter.h"
#include "ImageLoading.h"
#include "Cursor.h"
#include "Global_Gameloop.h"
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
#include "Global_Worldmap.h"
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
    Global::stateCurrentScene = make_unique<CSceneStartScreen>(CSceneStartScreen());

}

void Forradia::Run()
{

    while (!Global::eventQuit)
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

    while (SDL_PollEvent(&inputUnhandledEvent))
    {

        switch (inputUnhandledEvent.type)
        {

            case SDL_QUIT:
                Global::eventQuit = true;
                break;

            case SDL_KEYDOWN:

                if (inputUnhandledEvent.key.keysym.sym == SDLK_LALT)
                    stateAltKeyPressed = true;

                if (inputUnhandledEvent.key.keysym.sym == SDLK_RETURN
                    && stateAltKeyPressed)
                    Global::ToggleFullscreen();

                Global::stateCurrentScene->DoKeyDown(inputUnhandledEvent.key.keysym.sym);
                break;

            case SDL_KEYUP:

                if (inputUnhandledEvent.key.keysym.sym == SDLK_LALT)
                    stateAltKeyPressed = false;

                Global::stateCurrentScene->DoKeyUp(inputUnhandledEvent.key.keysym.sym);
                break;

            case SDL_MOUSEBUTTONDOWN:
                Global::stateCurrentScene->DoMouseDown(inputUnhandledEvent.button.button);
                break;

            case SDL_MOUSEBUTTONUP:
                Global::stateCurrentScene->DoMouseUp(inputUnhandledEvent.button.button);
                break;

        }

    }

}

void Forradia::Update() 
{

    Global::stateCurrentScene->Update();
    FPSCounter::Update();
    Cursor::Update();

}

void Forradia::Render()
{

    Global::stateCurrentScene->Render();
    FPSCounter::Render();
    Cursor::Render();

    Drawing::PresentToScreen();

}