#include "MapGeneration.h"
#include "DataLoading.h"
#include <SDL2/SDL_timer.h>
#include "Global_MapSize.h"
#include "Constants.h"
#include "CTile.h"
#include <memory>

using std::make_unique;

#define FOR(j) for (int i = 0; i < j; i++)
#define FOR_EXT(x,y,z) for (int x = y; x < z; x++)
#define LOOP_OVER_MAP(xyz) FOR_EXT(y, 0, Global::tilesMapSize) { FOR_EXT(x, 0, Global::tilesMapSize) { xyz } }
#define LOOP_OVER_CIRCLE(xcenter, ycenter, r, content) FOR_EXT(y, ycenter - r, ycenter + r + 1) { FOR_EXT(x, xcenter - r, xcenter + r + 1) { int dx = x - xcenter; int dy = y - ycenter; if (dx * dx + dy * dy <= r * r) { content } } }
#define IN_MAP(z) z >= 0 && z < Global::tilesMapSize

void MapGeneration::GenerateMap(CMap& map)
{

    idxsUsedTiles["grass"] = DataLoading::GetDescriptionIndexByName("TileGrass");
    idxsUsedTiles["water"] = DataLoading::GetDescriptionIndexByName("TileWater");
    idxsUsedTiles["rock"] = DataLoading::GetDescriptionIndexByName("TileRock");
    idxsUsedTiles["clay"] = DataLoading::GetDescriptionIndexByName("TileClay");
    idxsUsedTiles["sand"] = DataLoading::GetDescriptionIndexByName("TileSand");
    idxsUsedTiles["woodFloor"] = DataLoading::GetDescriptionIndexByName("TileWoodFloor");
    idxsUsedTiles["stoneSlab"] = DataLoading::GetDescriptionIndexByName("TileStoneSlab");

    idxsUsedObjects["reed"] = DataLoading::GetDescriptionIndexByName("ObjectReed");

    paramsGenerationInput["numRivers"] = 50;
    paramsGenerationInput["riverInterval"] = 5;
    paramsGenerationInput["mountainLength"] = 50;

    srand(SDL_GetTicks());

    GenerateAll(map);

}

void MapGeneration::GenerateAll(CMap& map)
{


    int intervalRivers = 0;
    int numRiverStarts = paramsGenerationInput["numRivers"];

    int stationLength = 15;
    int plazaSize = stationLength;

    map.m_coordPlazaPosition = { Global::tilesMapSize / 2 - stationLength / 2, Global::tilesMapSize / 2 + 2 };
    map.m_tilesNumPlazaSize = plazaSize;

    double k0 = 90.0 * (0.5 + (rand() % 40) / 40.0);
    double k1 = 1.5 * (0.5 + (rand() % 40) / 40.0);
    double k2 = 2.0 * (0.5 + (rand() % 40) / 40.0);
    double k3 = 2.0 * (0.5 + (rand() % 40) / 40.0);
    double k4 = 2.0 * (0.5 + (rand() % 40) / 40.0);
    double k5 = 0.8 * (0.5 + (rand() % 40) / 40.0);
    double k6 = 2.0 * (0.5 + (rand() % 40) / 40.0);
    double k7 = 0.6 * (0.5 + (rand() % 40) / 40.0);
    double k8 = 2.0 * (0.5 + (rand() % 40) / 40.0);
    double k9 = 0.8 * (0.5 + (rand() % 40) / 40.0);
    double k10 = 175.0 * (0.5 + (rand() % 40) / 40.0);
    double k11 = 275.0 * (0.5 + (rand() % 40) / 40.0);
    double k12 = 375.0 * (0.5 + (rand() % 40) / 40.0);
    double k13 = 475.0 * (0.5 + (rand() % 40) / 40.0);

    for (int iteration = 0; iteration <= 1; iteration++)
    {

        FOR_EXT(y, 0, Global::tilesMapSize)
        {
            FOR_EXT(x, 0, Global::tilesMapSize)
            {

                int xx = x + Global::tilesMapSize / 2;
                int yy = y + Global::tilesMapSize / 2;
                
                if (iteration == 0)
                {

                    map.m_tilesGrid[x][y]->m_floorsArray[SURFACE_FLOOR]->m_idxGroundType = idxsUsedTiles["grass"];

                    

                    map.m_tilesGrid[x][y]->m_elevationHeight =
                        k0 * cos(k1 * cos(k2 + (x + xx * xx + x * y) / ((double)Global::tilesMapSize * k10)))
                        * cos(k3 * cos(k4 + k5 * (y + yy * yy + y * x) / ((double)Global::tilesMapSize * k11)))
                        * cos(k6 + k7 * (x + xx * xx + x * y) / ((double)Global::tilesMapSize * k12))
                        * cos(k8 + k9 * (y + y * y) / ((double)Global::tilesMapSize * k13));
                    
                    
                    if (map.m_tilesGrid[x][y]->m_elevationHeight > 0)
                    {

                        double rock = cos(2 * (1 + (y + yy * yy + y * x + cos(x / 100.0 + xx * xx / 8000.0) * Global::tilesMapSize * 80) / ((double)Global::tilesMapSize * 75)));
                        if (rock > 0.1)
                            map.m_tilesGrid[x][y]->m_floorsArray[SURFACE_FLOOR]->m_idxGroundType = idxsUsedTiles["rock"];

                    }

                }

                    if (map.m_tilesGrid[x][y]->m_elevationHeight < 0
                        && (map.m_tilesGrid[x][y]->m_floorsArray[SURFACE_FLOOR]->m_idxGroundType != idxsUsedTiles["water"] || iteration == 1))
                    {


                        if (iteration == 0)
                            map.m_tilesGrid[x][y]->m_floorsArray[SURFACE_FLOOR]->m_idxGroundType = idxsUsedTiles["water"];

                    }

                    if (map.m_tilesGrid[x][y]->m_elevationHeight == -1)
                    {


                        if (iteration == 0)
                        {
                            double sand = cos(2 * (1 + (y + yy * yy + y * x + cos(x / 100.0 + xx * xx / 8000.0) * Global::tilesMapSize * 80) / ((double)Global::tilesMapSize * 75)));
                            if (sand > 0.1)
                            {
                                map.m_tilesGrid[x][y]->m_floorsArray[SURFACE_FLOOR]->m_idxGroundType = idxsUsedTiles["sand"];
                                map.m_tilesGrid[x][y]->m_elevationHeight = 0;
                            }
                        }

                    }

                    if (iteration == 1)
                    {

                        double tree1 = cos(0.5 * (1 + (x + xx * xx + x * y + cos(y / 100.0 + yy * yy / 8000.0) * Global::tilesMapSize * 80) / ((double)Global::tilesMapSize * 75)));
                        tree1 *= cos(y / 60.0);
                        tree1 *= cos(x / 60.0);
                        tree1 *= cos(2*(x + y + x * y));
                        tree1 *= (10 + (x * y)/60) % 2;
                        tree1 *= (11 + (x * y) / 33) % 2;
                        if (tree1 > 0.2 && map.m_tilesGrid[x][y]->m_floorsArray[SURFACE_FLOOR]->m_idxGroundType == idxsUsedTiles["grass"]
                            && !map.m_tilesGrid[x][y]->m_floorsArray[SURFACE_FLOOR]->HoldsObjects())
                            map.m_tilesGrid[x][y]->m_floorsArray[SURFACE_FLOOR]->AddObject(DataLoading::GetDescriptionIndexByName("ObjectTree1"));


                        double tree2 = cos(0.5 * (2 + (y + yy * yy + y * x + cos(x / 100.0 + xx * xx / 8000.0) * Global::tilesMapSize * 80) / ((double)Global::tilesMapSize * 75)));
                        tree2 *= cos(1 + y / 60.0);
                        tree2 *= cos(2 + x / 60.0);
                        tree2 *= cos(2*(3 + x + y + x * y));
                        tree2 *= (12 + (x * y) / 60 + 1) % 2;
                        tree2 *= (13 + (x * y) / 23 + 1) % 2;
                        if (tree2 > 0.2 && map.m_tilesGrid[x][y]->m_floorsArray[SURFACE_FLOOR]->m_idxGroundType == idxsUsedTiles["grass"]
                            && !map.m_tilesGrid[x][y]->m_floorsArray[SURFACE_FLOOR]->HoldsObjects())
                            map.m_tilesGrid[x][y]->m_floorsArray[SURFACE_FLOOR]->AddObject(DataLoading::GetDescriptionIndexByName("ObjectTree2"));



                        double bush = (x + 1 * y + 2 * x * y + 3 * xx * y + 4 * x * yy) % 83;
                        if (bush == 1 && map.m_tilesGrid[x][y]->m_floorsArray[SURFACE_FLOOR]->m_idxGroundType == idxsUsedTiles["grass"]
                            && !map.m_tilesGrid[x][y]->m_floorsArray[SURFACE_FLOOR]->HoldsObjects())
                            map.m_tilesGrid[x][y]->m_floorsArray[SURFACE_FLOOR]->AddObject(DataLoading::GetDescriptionIndexByName("ObjectBush"));


                        double bushTall = (40 + x + 1 * y + 2 * x * y + 3 * xx * y + 4 * x * yy) % 83;
                        if (bushTall == 1 && map.m_tilesGrid[x][y]->m_floorsArray[SURFACE_FLOOR]->m_idxGroundType == idxsUsedTiles["grass"]
                            && !map.m_tilesGrid[x][y]->m_floorsArray[SURFACE_FLOOR]->HoldsObjects())
                            map.m_tilesGrid[x][y]->m_floorsArray[SURFACE_FLOOR]->AddObject(DataLoading::GetDescriptionIndexByName("ObjectBushTall"));


                        double boulder = (40 + x + 1 * y + 2 * x * y + 3 * xx * y + 4 * x * yy) % 313;
                        if (boulder == 1
                            && (map.m_tilesGrid[x][y]->m_floorsArray[SURFACE_FLOOR]->m_idxGroundType == idxsUsedTiles["rock"]
                            || map.m_tilesGrid[x][y]->m_floorsArray[SURFACE_FLOOR]->m_idxGroundType == idxsUsedTiles["water"])
                            )
                            map.m_tilesGrid[x][y]->m_floorsArray[SURFACE_FLOOR]->AddObject(DataLoading::GetDescriptionIndexByName("ObjectBoulder"));


                        double foe = cos(4 * (3 + (y + yy * yy + y * x + cos(x / 100.0 + xx * xx / 8000.0) * Global::tilesMapSize * 80) / ((double)Global::tilesMapSize * 75)));
                        foe *= cos(5 + y / 20.0);
                        foe *= cos(6 + x / 20.0);
                        foe *= cos(7 + (x + y + x * y) / 10.0);
                        if (foe >= 0.8 && map.m_tilesGrid[x][y]->m_floorsArray[SURFACE_FLOOR]->m_idxGroundType != idxsUsedTiles["water"]
                            && !map.m_tilesGrid[x][y]->m_floorsArray[SURFACE_FLOOR]->HoldsObjects()
                            && !map.SeenFloorHasFoes(x, y))
                            map.AddFoe(make_unique<CFoe>(CFoe(1, x, y)), SURFACE_FLOOR);

                        double butterfly = (40 + x + 1 * y + 2 * x * y + 3 * xx * y + 4 * x * yy) % 390;
                        if (butterfly == 1
                            && (map.m_tilesGrid[x][y]->m_floorsArray[SURFACE_FLOOR]->m_idxGroundType != idxsUsedTiles["water"]
                                && map.m_tilesGrid[x][y]->m_floorsArray[SURFACE_FLOOR]->m_idxGroundType != idxsUsedTiles["woodFloor"]))
                            map.AddFoe(make_unique<CFoe>(CFoe(ID_BUTTERFLY, x, y)), SURFACE_FLOOR);

                        double pinkSlime = (40 + x + 1 * y + 2 * x * y + 3 * xx * y + 4 * x * yy) % 390;
                        if (pinkSlime == 1
                            && (map.m_tilesGrid[x][y]->m_floorsArray[SURFACE_FLOOR]->m_idxGroundType != idxsUsedTiles["water"]
                                && map.m_tilesGrid[x][y]->m_floorsArray[SURFACE_FLOOR]->m_idxGroundType != idxsUsedTiles["woodFloor"]))
                            map.AddFoe(make_unique<CFoe>(CFoe(ID_PINKSLIME, x, y)), SURFACE_FLOOR);


                        if (map.m_tilesGrid[x][y]->m_floorsArray[SURFACE_FLOOR]->m_idxGroundType == idxsUsedTiles["water"])
                        {
                            int waterDepth = -map.m_tilesGrid[x][y]->m_elevationHeight;
                            if (waterDepth == 1)
                            {
                                double clay = cos(std::max(0, waterDepth) / 30.0 * M_PI / 2.0);
                                clay *= cos(0.5 * (17 + (x + xx * xx + x * y + cos(y / 100.0 + yy * yy / 8000.0) * Global::tilesMapSize * 80) / ((double)Global::tilesMapSize * 75)));
                                clay *= cos(y / 10.0);
                                clay *= cos(x / 10.0);
                                if (clay > 0.2 && !map.m_tilesGrid[x][y]->m_floorsArray[SURFACE_FLOOR]->HoldsObjects())
                                {
                                    map.m_tilesGrid[x][y]->m_floorsArray[SURFACE_FLOOR]->m_idxGroundType = idxsUsedTiles["clay"];
                                    map.m_tilesGrid[x][y]->m_elevationHeight = 0;
                                }
                            }
                        }


                        if (map.m_tilesGrid[x][y]->m_floorsArray[SURFACE_FLOOR]->m_idxGroundType == idxsUsedTiles["water"])
                        {
                            int waterDepth = -map.m_tilesGrid[x][y]->m_elevationHeight;
                            double reed = cos(std::max(0, waterDepth) / 7.0 * M_PI / 2.0);
                            reed *= cos(0.5 * (17 + (x + xx * xx + x * y + cos(y / 100.0 + yy * yy / 8000.0) * Global::tilesMapSize * 80) / ((double)Global::tilesMapSize * 75)));
                            reed *= cos(y / 10.0);
                            reed *= cos(x / 10.0);
                            reed *= ((11 + x + y + x*y + x*x - y*y) % 9)/8.0;
                            if (reed > 0.5 && !map.m_tilesGrid[x][y]->m_floorsArray[SURFACE_FLOOR]->HoldsObjects())
                                map.m_tilesGrid[x][y]->m_floorsArray[SURFACE_FLOOR]->AddObject(DataLoading::GetDescriptionIndexByName("ObjectReed"));
                        }

                    }

                    if (iteration == 1)
                    {
                        if (map.m_tilesGrid[x][y]->m_elevationHeight > 4 && map.m_tilesGrid[x][y]->m_elevationHeight < 15)
                        {
                            if (intervalRivers % numRiverStarts == 0)
                            {
                                GenerateRiversFromMountainTop(map, x, y);
                            }
                            intervalRivers++;
                        }
                    }

                    if (iteration == 1)
                    {

                        

                        int yTrainRail = Global::tilesMapSize / 2;

                        map.m_tilesGrid[x][yTrainRail]->m_floorsArray[SURFACE_FLOOR]->ClearObjects();
                        map.m_tilesGrid[x][yTrainRail + 1]->m_floorsArray[SURFACE_FLOOR]->ClearObjects();

                        if (x >= Global::tilesMapSize / 2 - stationLength / 2 && x <= Global::tilesMapSize / 2 + stationLength / 2)
                            map.m_tilesGrid[x][yTrainRail]->m_floorsArray[SURFACE_FLOOR]->AddObject(DataLoading::GetDescriptionIndexByName("ObjectTrainRailEWStationS"));
                        else
                            map.m_tilesGrid[x][yTrainRail]->m_floorsArray[SURFACE_FLOOR]->AddObject(DataLoading::GetDescriptionIndexByName("ObjectTrainRailEW"));


                        if (y >= Global::tilesMapSize / 2 + 2 && y < Global::tilesMapSize / 2 + 2 + plazaSize)
                        {
                            if (x >= Global::tilesMapSize / 2 - stationLength / 2 && x < Global::tilesMapSize / 2 - stationLength / 2 + plazaSize)
                            {

                                map.m_tilesGrid[x][y]->m_elevationHeight = map.m_tilesGrid[Global::tilesMapSize / 2 - stationLength / 2][Global::tilesMapSize / 2 + 3]->m_elevationHeight;
                                map.m_tilesGrid[x][y]->m_floorsArray[SURFACE_FLOOR]->m_idxGroundType = idxsUsedTiles["stoneSlab"];

                                map.m_tilesGrid[x][y]->m_floorsArray[SURFACE_FLOOR]->ClearObjects();

                                if (x == Global::tilesMapSize / 2 - stationLength / 2 + plazaSize / 2 && y == Global::tilesMapSize / 2 + 3 + plazaSize / 2)
                                    map.m_tilesGrid[x][y]->m_floorsArray[SURFACE_FLOOR]->AddObject(DataLoading::GetDescriptionIndexByName("ObjectFountain"));

                                map.m_tilesGrid[x][y]->m_isNPCOwnedLand = true;

                            }

                            map.m_tilesGrid[Global::tilesMapSize / 2 - stationLength / 2 + plazaSize][y]->m_elevationHeight = map.m_tilesGrid[Global::tilesMapSize / 2 - stationLength / 2][Global::tilesMapSize / 2 + 3]->m_elevationHeight;

                        }




                    }


            }
        }
    }
}


void MapGeneration::GenerateRiversFromMountainTop(CMap& map, int mapx, int mapy)
{


    CPoint p = { mapx, mapy };

    double width = 1;

    double dxOrig = 0;
    double dyOrig = 0;

    double minDist = 9999;

    double r;
    double w;

    for (r = 1; r < Global::tilesMapSize; r++)
    {
        srand(SDL_GetTicks());
        double startAngle = (double)rand() / (2 * M_PI);

        double step = M_PI / 10.0;

        double valCos;
        double valSin;

        for (w = startAngle; w < startAngle + 2 * M_PI; w += step)
        {

            valCos = r * cos(w);
            valSin = r * sin(w);

            double xx = p.m_x + valCos;
            double yy = p.m_y + valSin;

            if (xx >= 0 && yy >= 0 && xx < Global::tilesMapSize && yy < Global::tilesMapSize)
            {
                if (map.m_tilesGrid[int(xx)][int(yy)]->m_elevationHeight < 0 )
                {

                    if (valCos + valSin < minDist)
                    {
                        minDist = valCos + valSin;
                        break;
                    }

                }

                if (r < 15 && map.m_tilesGrid[int(xx)][int(yy)]->m_floorsArray[SURFACE_FLOOR]->m_idxGroundType == idxsUsedTiles["water"])
                    return;
            }

            if (minDist != 9999)
                break;

        }

        if (minDist != 9999)
        {
            dxOrig = valCos / r;
            dyOrig = valSin / r;

                break;
        }

    }

    int j = 0;

    int xx = p.m_x;
    int yy = p.m_y;

    int xxOld = xx;
    int yyOld = yy;

    while(true)
    {

        width += (double)rand() / RAND_MAX - (double)rand() / RAND_MAX;
        width = std::max(1.0, width);

        double ww = w + cos(mapx + mapy + mapx*mapy + j / 5.0) * M_PI / 2;

        double valCos = cos(ww);
        double valSin = sin(ww);

        double dx = valCos*20;
        double dy = valSin* 20;

        double absmax = std::max(abs(dx), abs(dy));

        dx = dx / absmax;
        dy = dy / absmax;

        xxOld = xx;
        yyOld = yy;

        xx = xxOld + dx;
        yy = yyOld + dy;

        if (xx == xxOld && yy == yyOld)
        {
            j++;
            continue;
        }

        if (xx >= 0 && yy >= 0 && xx < Global::tilesMapSize && yy < Global::tilesMapSize
            && (map.m_tilesGrid[xx][yy]->m_floorsArray[SURFACE_FLOOR]->m_idxGroundType != idxsUsedTiles["water"] || j == 0))
        {
            for (int _yy = yy; _yy < yy + width; _yy++)
            {
                for (int _xx = xx; _xx < xx + width; _xx++)
                {
                    if (_xx >= 0 && _yy >= 0 && _xx < Global::tilesMapSize && _yy < Global::tilesMapSize)
                    {

                        int xcenter = _xx + (width + 1)/2;
                        int ycenter = _yy + (width + 1) / 2;

                        int dddx = xcenter - _xx;
                        int dddy = ycenter - _yy;

                        int totabs = abs(dddx) + abs(dddy);
                        double dxnorm = (double)dddx / totabs;
                        double dynorm = (double)dddy / totabs;

                        int minabs = std::min(abs(dxnorm), abs(dynorm));
                        int inverse = (width + 1) / 2 - minabs;

                        map.m_tilesGrid[_xx][_yy]->m_elevationHeight -= inverse;
                        
                        map.m_tilesGrid[_xx][_yy]->m_floorsArray[SURFACE_FLOOR]->m_idxGroundType = idxsUsedTiles["water"];
                        map.m_tilesGrid[_xx][_yy]->m_floorsArray[SURFACE_FLOOR]->ClearObjects();
                    }
                }
            }
        }
        else
        {
            break;
        }

        j++;

    }
}


