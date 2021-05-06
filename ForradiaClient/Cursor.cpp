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

    SDL_Rect rectCursor = {mx, my, attrCursorSize, attrCursorSize};
    
    if (isHoveringButtonBuffer)
        SDL_RenderCopy(Global::sdlRendererDefault, ImageLoading::libTextures[kIDCursorHovering], NULL, &rectCursor);
    else
        SDL_RenderCopy(Global::sdlRendererDefault, ImageLoading::libTextures[kIDCursor], NULL, &rectCursor);

}