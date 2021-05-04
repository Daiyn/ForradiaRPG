#include "ImageLoading.h"
#include <SDL2/SDL_image.h>
#include <filesystem>
#include "DataLoading.h"
#include "Global_SDL.h"



void ImageLoading::LoadImages()
{

    for (int i = 0; i < CONTENT_DB_SIZE; i++)
    {
        texturesArray[i] = NULL;
        texturesMapPreviewArray[i] = NULL;
    }

    auto imagesDirectory = std::filesystem::directory_iterator(imagesPath);

    for (const auto &fileEntry : imagesDirectory)
    {

        auto path = fileEntry.path();

        string imageFilename = string(path.filename().string());

        if (imageFilename.substr(imageFilename.length() - 4, 4) == ".png")
        {
            string onlyName = imageFilename.substr(0, imageFilename.find("."));
            LoadSingleImage(onlyName, Global::renderer);
        }

    }

}


void ImageLoading::LoadSingleImage(string texName, SDL_Renderer *renderer)
{

    const char *path = SDL_GetBasePath();
    string s = path;
    s.append(imagesPath + texName + ".png");

    SDL_Surface *img = IMG_Load(s.c_str());
    SDL_Texture *tex = SDL_CreateTextureFromSurface(renderer, img);

    int texDescId = DataLoading::GetDescriptionIndexByName(texName);

    if (texDescId != -1)
        texturesArray[texDescId] = tex;

    surfaces.insert(std::pair<string, SDL_Surface *>(texName, img));

}

void ImageLoading::ClearMapPreviewTextures()
{

    for (int i = 0; i < CONTENT_DB_SIZE; i++)
    {
        if (texturesMapPreviewArray[i] != NULL)
        {
            SDL_DestroyTexture(texturesMapPreviewArray[i]);
            texturesMapPreviewArray[i] = NULL;
        }
    }

}

void ImageLoading::CreateMapPreviewTextures()
{

    for (auto it: surfaces)
    {
        SDL_Texture *texMapPreview = SDL_CreateTextureFromSurface(Global::rendererFullMapOverview, it.second);
        int texDescId = DataLoading::GetDescriptionIndexByName(it.first);
        texturesMapPreviewArray[texDescId] = texMapPreview;
    }

}