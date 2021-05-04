#include "NPCNameGeneration.h"


string NPCNameGeneration::GenerateName()
{

    int c0 = rand() % 20;
    int v1 = rand() % 6;
    int c2 = rand() % 20;
    int c3 = rand() % 20;
    int v4 = rand() % 6;
    int c5 = rand() % 20;

    string name = (char) toupper((int) (consonants[c0][0]))
                        + vowels[v1]
                        + consonants[c2]
                        + consonants[c3]
                        + vowels[v4]
                        + consonants[c5];

    return name;

}