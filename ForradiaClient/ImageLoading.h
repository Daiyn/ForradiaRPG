/*+===================================================================
  File:      IMAGELOADING.H

  Summary:   Describes a constant, free variables and functions
             related to the loading of image assets.

  Classes:   

  Functions: LoadImages
             LoadSingleImage
             ClearMapPreviewTextures
             CreateMapPreviewTextures

  Origin:    Written by Andreas Åkerberg.

  This software is open source and licensed under the MIT License.
===================================================================+*/

#ifndef FORRADIAFORMATION_IMAGELOADER_H
#define FORRADIAFORMATION_IMAGELOADER_H

#include <SDL2/SDL_render.h>
#include <unordered_map >
#include <string>
#include "Constants.h"

using std::string;
using std::unordered_map;

namespace ImageLoading
{
    inline std::unordered_map <string, SDL_Surface*> libSurfaces;
    const string imagesPath = "Resources/Images/";
    inline SDL_Texture** libTextures = new SDL_Texture* [CONTENT_DB_SIZE];
    inline SDL_Texture** libTexturesFullMapRender = new SDL_Texture * [CONTENT_DB_SIZE];

    void ClearMapPreviewTextures();
    void CreateMapPreviewTextures();
    void LoadImages();
    void LoadSingleImage(string s, SDL_Renderer *renderer); 
};


#endif
