#include "NPCNameGeneration.h"


string NPCNameGeneration::GenerateName()
{

    int c0 = rand() % 20;
    int v1 = rand() % 6;
    int c2 = rand() % 20;
    int c3 = rand() % 20;
    int v4 = rand() % 6;
    int c5 = rand() % 20;

    string name = (char) toupper((int) (lettersConsonants[c0][0]))
                        + lettersVowels[v1]
                        + lettersConsonants[c2]
                        + lettersConsonants[c3]
                        + lettersVowels[v4]
                        + lettersConsonants[c5];

    return name;

}