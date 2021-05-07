/*+===================================================================
  File:      FORRADIA.H

  Summary:    ____   ____   ____   ____   _____   ___     _   _____
             | ___| | __ | |    | |    | |     | |   \   | | |     |
             | |_   | || | | 0 _| | 0 _| |  0  | |    \  | | |  0  | 
             |  _|  | || | |   \  |   \  |  _  | |  0  | | | |  _  | 
             |_|    |____| | |\_\ | |\_\ |_| |_| |_____| |_| |_| |_| 
             ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  
             Forradia is a game combining elements from the sandbox
             RPG as well as simulation game genres. It makes heavily
             use of procedural generation for the map generation where
             the purpose is to randomily generate a large variety of
             interesting nature maps for the player to explore. The 
             maps contain nature elements such as grass, mountains, 
             lakes (or sometimes even parts of seas), and naturally
             appearing rivers flowing from the top of the mountains 
             down to the water level.

             Background story: 
             =================
             The world of Forradia is located on a mystical 
             island out in the middle of a wild sea in a reality not
             being the one of the ordinary world.

                                  /\
                                _/  \_
                          ~   _/      \_    ~
                      ~     _/          \_~
                            \_          _/
                          ~   `--------´        ~
                              ~            ~

             At first the player started to have very vidid dreams 
             at night and after a while they got so vidid that the 
             player understood that they actually were real and 
             that he actually traveled to Forradia at night.

                                 0
                                -|-
                                / \
                               

             <How the player appeared at the Forradia Island>

             ( Didnt fit in the ordinary world and somehow found a
             way leading to Forradia, which cannot be seen on the 
             ordinary world map. The train rail isnt connected to
             the ordinary world either )

             This file describes top-most level game functions and free variables.

  Classes:   

  Functions: Initialize
             Run
             HandleEvents
             Update
             Render

  Origin:    Written by Andreas Åkerberg.

  This software is open source and licensed under the MIT License.
===================================================================+*/

#ifndef FORRADIAFORMATION_GAMELOOP_H
#define FORRADIAFORMATION_GAMELOOP_H

#include <SDL2/SDL_events.h>

namespace Game
{
    inline SDL_Event inputUnhandledEvent;
    inline bool stateAltKeyPressed = false;
    
    void HandleEvents();
    void Initialize();
    void Render();
    void Run();
    void Update();
};


#endif
