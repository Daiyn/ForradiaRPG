/*+===================================================================
  File:      DRAWING.H

  Summary:   Describes free variables and functions used to render
             things to the screen, based on the SDL library.

  Classes:   CRectangle

  Functions: BlankScreen
             FilledScreen
             RectPrepare
             ImageCurrentRect
             Image
             RectContour
             FilledRect
             PresentToScreen
             UseDefaultRenderer
             UseFullMapRenderer

  Origin:    Written by Andreas Åkerberg.

  This software is open source and licensed under the MIT License.
===================================================================+*/

#ifndef FORRADIACLIENT_DRAWING_H
#define FORRADIACLIENT_DRAWING_H

#include <string>
#include <SDL2/SDL_rect.h>
#include "Rectangle.h"

struct SDL_Renderer;
struct SDL_Texture;

namespace Drawing
{
    inline SDL_Rect activeDestRectangle;
    inline SDL_Renderer* activeRenderer = NULL;
    inline SDL_Texture** activeTexturesLib = NULL;

    void BlankScreen();
    void FilledCurrentRect(float r, float g, float b);
    void FilledCurrentRect(float r, float g, float b, float a);
    void FilledRect(SDL_Color color, Rectangle rect);
    void FilledRect(SDL_Color color, int x, int y, int w, int h);
    void FilledRect(float r, float g, float b, int x, int y, int w, int h);
    void FilledRect(float r, float g, float b, float a, int x, int y, int w, int h);
    void FilledRect(float r, float g, float b, float a, Rectangle rect);
    void FilledScreen(float r, float g, float b);
    void Image(SDL_Texture *texture, Rectangle rect);
    void Image(int imageIndex, Rectangle rect);
    void Image(int imageIndex, int x, int y, int w, int h);
    void Image(int imageIndex);
    void ImageCurrentRect(int imageIndex);
    void PresentToScreen();
    void CurrentRectContour(float r, float g, float b);
    void CurrentRectContour(float r, float g, float b, float a);
    void RectContour(float r, float g, float b, int x, int y, int w, int h);
    void RectContour(float r, float g, float b, float a, int x, int y, int w, int h);
    void RectContour(SDL_Color color, Rectangle rect);
    void RectPrepare(int x, int y, int w, int h);
    void UseDefaultRenderer();
    void UseFullMapRenderer();
};

#endif //FORRADIACLIENT_DRAWING_H
