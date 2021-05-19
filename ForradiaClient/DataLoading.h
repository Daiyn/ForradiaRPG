/*+===================================================================
  File:      DATALOADING.H

  Summary:   Describes functions and free variables related to the  
             game content database used in many areas of the game.

  Classes:   CDataDescription

  Functions: LoadDescriptions
             GetDescriptionIndexByName

  Origin:    Written by Andreas Åkerberg.

  This software is open source and licensed under the MIT License.
===================================================================+*/

#ifndef FORRADIACLIENT_DATALOADER_H
#define FORRADIACLIENT_DATALOADER_H

#include "DataDescription.h"
#include <memory>
#include "Constants.h"
#include <unordered_map>

using std::string;
using std::unique_ptr;
using std::unordered_map;


namespace DataLoading
{
    inline unique_ptr<DataDescription> libDescriptions[ImagesIDs::ContentDBSize];
    inline unordered_map<string, int> contentIndicesByName[ImagesIDs::ContentDBSize];

    int GetDescriptionIndexByName(string name);
    void LoadDescriptions();
    void AddDescription(int id, string name);
    void AddDescriptionEx(int id,
                            string name,
                            double imgWidthMulti,
                            double imgHeightMulti,
                            string imgFocusedObjAnim,
                            bool isObstacle,
                            bool movable,
                            string readableName,
                            bool randomScaling,
                            bool ignoreShadow,
                            int ticksToVanish,
                            double XOffsetFactor,
                            double YOffsetFactor,
                            bool hasAmount,
                            double foodAmount,
                            double foodSpeed);
};


#endif //FORRADIACLIENT_DATALOADER_H
