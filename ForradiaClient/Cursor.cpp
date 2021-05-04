#include "Cursor.h"
#include "ImageLoading.h"
#include "Global_SDL.h"
#include "Global_Mouse.h"
#include "Constants.h"

void Cursor::Update()
{

    isHoveringButtonBuffer = isHoveringButton;
    isHoveringButton = false;

}

void Cursor::Render()
{

    int mx = Global::GetMouseX();
    int my = Global::GetMouseY();

    SDL_Rect rectCursor = {mx, my, cursorSize, cursorSize};
    
    if (isHoveringButtonBuffer)
        SDL_RenderCopy(Global::renderer, ImageLoading::texturesArray[ID_CURSOR_HOVERING], NULL, &rectCursor);
    else
        SDL_RenderCopy(Global::renderer, ImageLoading::texturesArray[ID_CURSOR], NULL, &rectCursor);

}