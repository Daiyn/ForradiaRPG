/*+===================================================================
  File:      GUITERMINAL.H

  Summary:   Describes a constant, free variables and functions
             related to the GUI terminal component.

  Classes:   CColoredString

  Functions: Print
             PrintDamageToFoe
             PrintDamageToPlayer
             Render

  Origin:    Written by Andreas Åkerberg.

  This software is open source and licensed under the MIT License.
===================================================================+*/

#ifndef FORRADIAFORMATION_GUITERMINAL_H
#define FORRADIAFORMATION_GUITERMINAL_H

#include <vector>
#include "CColoredString.h"

using std::string;

namespace GUITerminal
{
    inline std::vector< std::vector<CColoredString>> bufferAllText;
    const int pxPadding = 10;

    void Print(string msg);
    void PrintDamageToFoe(int damage, string enemy);
    void PrintDamageToPlayer(int damage, string enemy);
    void Render();
};


#endif //FORRADIAFORMATION_GUITERMINAL_H
