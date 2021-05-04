/*+===================================================================
  File:      CCOLOREDSTRING.H

  Summary:   Describes class representing a colored string of which 
			 several are used to make up a line in the terminal.

  Classes:   CColoredString

  Functions: 

  Origin:    Written by Andreas Åkerberg.

  This software is open source and licensed under the MIT License.
===================================================================+*/

#pragma once

#include <string>
#include <SDL2/SDL_pixels.h>

using std::string;

/*C+C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C
  Class:    CColoredString

  Summary:  Short summary of purpose and content of CMyClass.
            Short summary of purpose and content of CMyClass.

  Methods:  MyMethodOne
              Short description of MyMethodOne.
            MyMethodTwo
              Short description of MyMethodTwo.
            CMyClass
              Constructor.
            ~CMyClass
              Destructor.
C---C---C---C---C---C---C---C---C---C---C---C---C---C---C---C---C-C*/

class CColoredString
{
public:

	string m_txtColoredString;
	SDL_Color m_clrColoredString;

protected:

private:

};