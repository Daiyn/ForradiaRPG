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
    FilledRect(r, g, b, currentRect.x, currentRect.y, currentRect.w, currentRect.h);
}

void Drawing::CurrentRectContour(float r, float g, float b)
{
    SDL_SetRenderDrawColor(currentRenderer, r, g, b, 255);
    SDL_RenderDrawRect(currentRenderer, &currentRect);
}

void Drawing::CurrentRectContour(float r, float g, float b, float a)
{
    SDL_SetRenderDrawColor(currentRenderer, r, g, b, a);
    SDL_RenderDrawRect(currentRenderer, &currentRect);
}

void Drawing::FilledScreen(float r, float g, float b)
{
    SDL_SetRenderDrawColor(currentRenderer, r, g, b, 255);
    SDL_RenderClear(currentRenderer);
}

void Drawing::Image(int imgIndex)
{
    auto tex = currentTexturesArray[imgIndex];
    SDL_RenderCopy(currentRenderer, tex, NULL, NULL);
}

void Drawing::RectContour(float r, float g, float b, int x, int y, int w, int h)
{
    RectContour(r, g, b, 255, x, y, w, h);
}

void Drawing::RectContour(float r, float g, float b, float a, int x, int y, int w, int h)
{
    SDL_Rect rect = {x, y, w, h};

    SDL_SetRenderDrawColor(currentRenderer, r, g, b, a);
    SDL_RenderDrawRect(currentRenderer, &rect);
}

void Drawing::RectContour(SDL_Color color, CRectangle rect)
{
    SDL_SetRenderDrawColor(currentRenderer, color.r, color.g, color.b, color.a);
    SDL_RenderDrawRect(currentRenderer, &rect);
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

    SDL_SetRenderDrawColor(currentRenderer, r, g, b, a);
    SDL_RenderFillRect(currentRenderer, &rect);
}

void Drawing::PresentToScreen()
{
    SDL_RenderPresent(currentRenderer);
}

void Drawing::Image(SDL_Texture* texture, CRectangle rect)
{
    SDL_RenderCopy(currentRenderer, texture, NULL, &rect);
}

void Drawing::Image(int imgIndex, CRectangle rect)
{
    SDL_RenderCopy(currentRenderer, currentTexturesArray[imgIndex], NULL, &rect);
}

void Drawing::Image(int imgIndex, int x, int y, int w, int h)
{
    SDL_Rect rect = { x, y, w, h };
    SDL_RenderCopy(currentRenderer, currentTexturesArray[imgIndex], NULL, &rect);
}

void Drawing::RectPrepare(int x, int y, int w, int h)
{
    currentRect = { x, y, w, h };
}


void Drawing::ImageCurrentRect(int imageIndex)
{
    SDL_RenderCopy(currentRenderer, currentTexturesArray[imageIndex], NULL, &currentRect);
}

void Drawing::FilledRect(float r, float g, float b, float a, CRectangle rect)
{
    SDL_SetRenderDrawColor(currentRenderer, r, g, b, a);
    SDL_RenderFillRect(currentRenderer, &rect);
}

void Drawing::UseDefaultRenderer()
{
    currentRenderer = Global::renderer;
    currentTexturesArray = ImageLoading::texturesArray;
}

void Drawing::UseFullMapRenderer()
{
    currentRenderer = Global::rendererFullMapOverview;
    currentTexturesArray = ImageLoading::texturesMapPreviewArray;
}