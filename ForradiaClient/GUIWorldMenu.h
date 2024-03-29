/*+===================================================================
  File:      GUIWORLDMENU.H

  Summary:   Describes a constant, free variables and functions
             related to the GUI world menu which can be brought up by
             right-clicking a tile on the map.

  Classes:   Point

  Functions: HandleLeftMouseClickInWorld
             HandleRightMouseClickInWorld
             Update
             Render

  Origin:    Written by Andreas �kerberg.

  This software is open source and licensed under the MIT License.
===================================================================+*/

#ifndef FORRADIAFORMATION_GUIWORLDMENU_H
#define FORRADIAFORMATION_GUIWORLDMENU_H

#include <string>
#include <vector>
#include <unordered_map>
#include "Point.h"

#define MENU_ID_NONE                        0
#define MENU_ID_CHOP_DOWN_TREE              1
#define MENU_ID_CREATE_UNLOADED_CAMPFIRE    2
#define MENU_ID_LOAD_CAMPFIRE               3
#define MENU_ID_CHOP_UP_WOOD_LOG            4
#define MENU_ID_MINE_CAVE                   5
#define MENU_ID_LIGHT_CAMPFIRE              6
#define MENU_ID_DIG_CLAY                    7
#define MENU_ID_CREATE_BRICK                8
#define MENU_ID_CREATE_MELTING_FURNACE      9
#define MENU_ID_EAT_APPLE                   10
#define MENU_ID_CREATE_WOODPLANK            11
#define MENU_ID_CREATE_WOODFLOOR            12
#define MENU_ID_LOAD_MELTING_FURNACE        13
#define MENU_ID_LIGHT_MELTING_FURNACE       14
#define MENU_ID_HEAT_IRON                   15
#define MENU_ID_CREATE_IRON_NAIL            16
#define MENU_ID_DIG_GROUND                  17
#define MENU_ID_CREATE_WOODWALL_NS          18
#define MENU_ID_CREATE_WOODWALL_EW          19
#define MENU_ID_CREATE_WOODWALL_CORNER      20
#define MENU_ID_HARVEST_STRAWBERRY          21
#define MENU_ID_EAT_STRAWBERRY             22

using std::string;

namespace GUIWorldMenu
{
    const std::unordered_map<int, string> contentAvailableMenuOptions =
    {
        {MENU_ID_NONE,                      "------"},
        {MENU_ID_CHOP_DOWN_TREE,            "Chop Down Tree"},
        {MENU_ID_CREATE_UNLOADED_CAMPFIRE,  "Create Unloaded Campfire"},
        {MENU_ID_LOAD_CAMPFIRE,             "Load Campfire"},
        {MENU_ID_CHOP_UP_WOOD_LOG,          "Chop Up Wood Log"},
        {MENU_ID_MINE_CAVE,                 "Mine Cave"},
        {MENU_ID_LIGHT_CAMPFIRE,            "Light Campfire" },
        {MENU_ID_DIG_CLAY,                  "Dig Clay" },
        {MENU_ID_CREATE_BRICK,              "Create Brick" },
        {MENU_ID_CREATE_MELTING_FURNACE,    "Create Melting Furnace" },
        {MENU_ID_EAT_APPLE,                 "Eat Apple" },
        {MENU_ID_CREATE_WOODPLANK,          "Create Woodplank" },
        {MENU_ID_CREATE_WOODFLOOR,          "Create Woodfloor" },
        {MENU_ID_LOAD_MELTING_FURNACE,      "Load Melting Furnace" },
        {MENU_ID_LIGHT_MELTING_FURNACE,     "Light Melting Furnace" },
        {MENU_ID_HEAT_IRON,                 "Heat Iron" },
        {MENU_ID_CREATE_IRON_NAIL,          "Create Iron Nail" },
        {MENU_ID_DIG_GROUND,                "Dig Ground" },
        {MENU_ID_CREATE_WOODWALL_NS,        "Create Woodwall NS" },
        {MENU_ID_CREATE_WOODWALL_EW,        "Create Woodwall EW" },
        {MENU_ID_CREATE_WOODWALL_CORNER,    "Create Woodwall Corner" },
        {MENU_ID_HARVEST_STRAWBERRY,        "Harvest Strawberry" },
        {MENU_ID_EAT_STRAWBERRY,           "Eat Strawberry" }
    };
    inline std::vector<int> stateShownMenuOptions;
    inline Point coordClickedTile = { -1, -1 };
    inline int pxMenuX;
    inline int pxMenuY;
    inline int pxMenuWidth = 160;
    inline int pxMenuHeight = 200;
    inline int pxRowHeight = 25;
    inline int pxMargin = 5;
    inline bool stateIsShown = false;

    bool HandleLeftMouseClickInWorld();
    void HandleRightMouseClickInWorld();
    void Render();
    void Update();
};


#endif //FORRADIAFORMATION_GUIWORLDMENU_H
