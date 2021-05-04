/*+===================================================================
  File:      GLOBAL_TRAIN.H

  Summary:   Describes the globally accessed primary train instance
             object;

  Classes:   CTrain

  Functions: DestroyTrain

  Origin:    Written by Andreas Åkerberg.

  This software is open source and licensed under the MIT License.
===================================================================+*/

#pragma once

#include <memory>

using std::unique_ptr;

class CTrain;

namespace Global
{
    inline unique_ptr<CTrain> train;
}
