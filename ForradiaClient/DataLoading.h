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

#include "CDataDescription.h"
#include <memory>
#include "Constants.h"

using std::string;
using std::unique_ptr;


namespace DataLoading
{
    inline unique_ptr<CDataDescription> descriptions[CONTENT_DB_SIZE];

    int GetDescriptionIndexByName(string name);
    void LoadDescriptions();
};


#endif //FORRADIACLIENT_DATALOADER_H
