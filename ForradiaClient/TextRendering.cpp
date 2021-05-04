#include "TextRendering.h"
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_render.h>
#include "Global_SDL.h"
#include "Global_Canvas.h"

void TextRendering::Initialize()
{

    char str[200];
    strcpy_s(str, SDL_GetBasePath());
    strcat_s(str, "Resources/Fonts/freesans.ttf");
    const char *c = &str[0];

    Global::Sans = TTF_OpenFont(str, 16);

    if (!Global::Sans) {
        printf("TTF_OpenFont: %s\n", TTF_GetError());
        return;
    }

}

void TextRendering::DrawString(string str, SDL_Color color, CPoint p)
{

    DrawString(str, color, p.m_x, p.m_y);

}

void TextRendering::DrawString(string str, SDL_Color color, int x, int y)
{

    int w;
    int h;

    TTF_SizeText(Global::Sans, str.c_str(), &w, &h);

    SDL_Rect rect = {x, y, w, h};

    SDL_Surface *surfaceMessage = TTF_RenderText_Blended(Global::Sans, str.c_str(), color);
    SDL_Texture *tex = SDL_CreateTextureFromSurface(Global::renderer, surfaceMessage);

    SDL_RenderCopy(Global::renderer, tex, NULL, &rect);

    SDL_DestroyTexture(tex);
    SDL_FreeSurface(surfaceMessage);

}

void TextRendering::DrawString(string str, SDL_Color color, int position)
{

    if (position == BOTTOM_CENTER)
    {

        int w;
        int h;

        TTF_SizeText(Global::Sans, str.c_str(), &w, &h);

        SDL_Rect rect = { Global::GetCanvasWidth() / 2 - w / 2, Global::GetCanvasHeight() - h, w, h };


        SDL_Surface* surfaceMessage = TTF_RenderText_Blended(Global::Sans, str.c_str(), color);
        SDL_Texture* tex = SDL_CreateTextureFromSurface(Global::renderer, surfaceMessage);

        SDL_RenderCopy(Global::renderer, tex, NULL, &rect);

        SDL_DestroyTexture(tex);
        SDL_FreeSurface(surfaceMessage);

    }

}

int TextRendering::GetTextWidth(string str)
{

    int w;
    int h;

    TTF_SizeText(Global::Sans, str.c_str(), &w, &h);

    return w;

}

int TextRendering::GetTextHeight()
{
    int w;
    int h;

    TTF_SizeText(Global::Sans, "", &w, &h);

    return h;

}