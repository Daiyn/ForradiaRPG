#include "GUITerminal.h"
#include "TextRendering.h"
#include "ImageLoading.h"
#include "Global_Canvas.h"
#include "Global_SDL.h"
#include "Drawing.h"
#include "Colors.h"

typedef unsigned int uint;

void GUITerminal::Print(string msg)
{
    std::vector<CColoredString> v;
    v.push_back({ msg, WHITE });
    bufferAllText.push_back(v);
}

void GUITerminal::PrintDamageToFoe(int damage, string enemy)
{

    CColoredString cs0 = { "You hit ", WHITE };
    CColoredString cs1 = { enemy, MEDIUM_RED };
    CColoredString cs2 = { " for ", WHITE };
    CColoredString cs3 = { std::to_string(damage), MEDIUM_GREEN };
    CColoredString cs4 = { " damage.", WHITE };

    bufferAllText.push_back({cs0, cs1, cs2, cs3, cs4});
}

void GUITerminal::PrintDamageToPlayer(int damage, string enemy)
{

    CColoredString cs0 = { enemy, MEDIUM_RED };
    CColoredString cs1 = { " hit you for ", WHITE };
    CColoredString cs2 = { std::to_string(damage), MEDIUM_RED };
    CColoredString cs3 = { " damage.", WHITE };

    bufferAllText.push_back({ cs0, cs1, cs2, cs3});

}

void GUITerminal::Render() {

    int w = int(520*Global::GetScalingHorizontal());
    int h = int(200 * Global::GetScalingVertical());
    int left = 0;
    int top = Global::GetCanvasHeight() - h;
    int topText = top;

    CRectangle rect = {left, top, w, h};

    Drawing::Image(ID_TERMINAL_BACK, rect);

    top = topText;

    left += pxPadding;
    topText += pxPadding;
    w -= 2*pxPadding;
    h -= 2*pxPadding;

    rect = {left, top, w, h};


    int numberOfRows = 6;


    int indexLast = bufferAllText.size() - 1;
    int indexFirst = indexLast - numberOfRows;

    int rowHeight = 25;
    int margin = 5;


    for (int i = 0; i <= numberOfRows; i++) {


        if (uint(indexFirst + i) >= 0 && uint(indexFirst + i) < bufferAllText.size()) {

            int i_modulu = (indexFirst + i) % 3;

            rect = {left, int((double)top + 1.5 * (double)margin + (double)i * (double)rowHeight), w, rowHeight};

            if (i_modulu == 0)
                Drawing::FilledRect(BLACK_ALPHA_40, rect);

            if (i_modulu == 1)
                Drawing::FilledRect(WHITE_ALPHA_20, rect);

            std::vector<CColoredString> parts = bufferAllText[indexFirst + i];

            int x = left + margin;
            int y = top + margin + i * rowHeight;

            for (auto it : parts)
            {
                string str = it.m_txtColoredString;
                SDL_Color color = it.m_clrColoredString;

                TextRendering::DrawString(str, color, x, y);

                x += TextRendering::GetTextWidth(str);
                
            }

        }

    }


}