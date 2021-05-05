/*+===================================================================
  File:      NPCNAMEGENERATION.H

  Summary:   Describes namespace members related to name generation
             for NPCs.

  Classes:   

  Functions: GenerateName

  Origin:    Written by Andreas Åkerberg.

  This software is open source and licensed under the MIT License.
===================================================================+*/

#ifndef FORRADIAFORMATION_NAMEGENERATOR_H
#define FORRADIAFORMATION_NAMEGENERATOR_H

#include <string>

using std::string;

namespace NPCNameGeneration
{
    inline string lettersConsonants[20] = {
        "b",
        "c",
        "d",
        "f",
        "g",
        "h",
        "j",
        "k",
        "l",
        "m",
        "n",
        "p",
        "q",
        "r",
        "s",
        "t",
        "v",
        "w",
        "x",
        "z"
    };
    inline string lettersVowels[6] = {
        "a",
        "e",
        "i",
        "o",
        "u",
        "y"
    };

    string GenerateName();
};


#endif
