#include "Drawing.h"
#include <SDL2/SDL_render.h>
#include "ImageLoading.h"
#include "Global_SDL.h"

void Drawing::BlankScreen()
{
    Drawing::FilledScreen(10, 10, 10);
}

void Drawing::FilledCurrentRect(float r, float g, float b)
{
    FilledRect(r, g, b, activeDestRectangle.x, activeDestRectangle.y, activeDestRectangle.w, activeDestRectangle.h);
}

void Drawing::CurrentRectContour(float r, float g, float b)
{
    SDL_SetRenderDrawColor(activeRenderer, r, g, b, 255);
    SDL_RenderDrawRect(activeRenderer, &activeDestRectangle);
}

void Drawing::CurrentRectContour(float r, float g, float b, float a)
{
    SDL_SetRenderDrawColor(activeRenderer, r, g, b, a);
    SDL_RenderDrawRect(activeRenderer, &activeDestRectangle);
}

void Drawing::FilledScreen(float r, float g, float b)
{
    SDL_SetRenderDrawColor(activeRenderer, r, g, b, 255);
    SDL_RenderClear(activeRenderer);
}

void Drawing::Image(int imgIndex)
{
    auto tex = activeTexturesLib[imgIndex];
    SDL_RenderCopy(activeRenderer, tex, NULL, NULL);
}

void Drawing::RectContour(float r, float g, float b, int x, int y, int w, int h)
{
    RectContour(r, g, b, 255, x, y, w, h);
}

void Drawing::RectContour(float r, float g, float b, float a, int x, int y, int w, int h)
{
    SDL_Rect rect = {x, y, w, h};

    SDL_SetRenderDrawColor(activeRenderer, r, g, b, a);
    SDL_RenderDrawRect(activeRenderer, &rect);
}

void Drawing::RectContour(SDL_Color color, CRectangle rect)
{
    SDL_SetRenderDrawColor(activeRenderer, color.r, color.g, color.b, color.a);
    SDL_RenderDrawRect(activeRenderer, &rect);
}

void Drawing::FilledRect(SDL_Color color, CRectangle rect)
{
    FilledRect(color.r, color.g, color.b, color.a, rect.x, rect.y, rect.w, rect.h);
}

void Drawing::FilledRect(SDL_Color color, int x, int y, int w, int h)
{
    FilledRect(color.r, color.g, color.b, color.a, x, y, w, h);
}

void Drawing::FilledRect(float r, float g, float b, int x, int y, int w, int h)
{
    FilledRect(r, g, b, 255, x, y, w, h);
}

void Drawing::FilledRect(float r, float g, float b, float a, int x, int y, int w, int h)
{
    SDL_Rect rect = {x, y, w, h};

    SDL_SetRenderDrawColor(activeRenderer, r, g, b, a);
    SDL_RenderFillRect(activeRenderer, &rect);
}

void Drawing::PresentToScreen()
{
    SDL_RenderPresent(activeRenderer);
}

void Drawing::Image(SDL_Texture* texture, CRectangle rect)
{
    SDL_RenderCopy(activeRenderer, texture, NULL, &rect);
}

void Drawing::Image(int imgIndex, CRectangle rect)
{
    SDL_RenderCopy(activeRenderer, activeTexturesLib[imgIndex], NULL, &rect);
}

void Drawing::Image(int imgIndex, int x, int y, int w, int h)
{
    SDL_Rect rect = { x, y, w, h };
    SDL_RenderCopy(activeRenderer, activeTexturesLib[imgIndex], NULL, &rect);
}

void Drawing::RectPrepare(int x, int y, int w, int h)
{
    activeDestRectangle = { x, y, w, h };
}


void Drawing::ImageCurrentRect(int imageIndex)
{
    SDL_RenderCopy(activeRenderer, activeTexturesLib[imageIndex], NULL, &activeDestRectangle);
}

void Drawing::FilledRect(float r, float g, float b, float a, CRectangle rect)
{
    SDL_SetRenderDrawColor(activeRenderer, r, g, b, a);
    SDL_RenderFillRect(activeRenderer, &rect);
}

void Drawing::UseDefaultRenderer()
{
    activeRenderer = Global::sdlRendererDefault;
    activeTexturesLib = ImageLoading::libTextures;
}

void Drawing::UseFullMapRenderer()
{
    activeRenderer = Global::sdlRendererFullMapRender;
    activeTexturesLib = ImageLoading::libTexturesFullMapRender;
}