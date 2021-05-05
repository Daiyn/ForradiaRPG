#include "Animations.h"
#include "DataLoading.h"
#include "Utilities.h"


int Animations::RunThroughAnimationFilter(int descIndex, int mapx, int mapy)
{

	int result = descIndex;

	if (descIndex == DataLoading::GetDescriptionIndexByName("TileWater"))
	{
		int numFrames;
		int animSpeed;
		int animIndex;
		std::string imageName;

		numFrames = 3;
		animSpeed = 500;
		animIndex = Utilities::GenerateTileCorrelatedAnimationFrameIndex(numFrames, animSpeed, mapx, mapy);
		imageName = "TileWater" + std::to_string(animIndex);

		result = DataLoading::GetDescriptionIndexByName(imageName);
	}

	if (descIndex == DataLoading::GetDescriptionIndexByName("ObjectBurningCampfire"))
	{
		int numFrames;
		int animSpeed;
		int animIndex;
		std::string imageName;

		numFrames = 3;
		animSpeed = 300;
		animIndex = Utilities::GenerateTileCorrelatedAnimationFrameIndex(numFrames, animSpeed, mapx, mapy);
		imageName = "ObjectBurningCampfire" + std::to_string(animIndex);

		result = DataLoading::GetDescriptionIndexByName(imageName);
	}

	return result;

}