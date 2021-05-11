/*+===================================================================
  File:      CRECTANGLE.H

  Summary:   Describes the commonly used CRectangle geometry class which
			 adds some functionality on top of the SDL_Rect class.

  Classes:   CRectangle
			 CPoint

  Functions: 

  Origin:    Written by Andreas Åkerberg.

  This software is open source and licensed under the MIT License.
===================================================================+*/

#pragma once

#include <SDL2/SDL_rect.h>
#include "CPoint.h"

/*C+C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C
  Class:    CRectangle

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

class CRectangle : public SDL_Rect
{
public:

	CRectangle() = default;
	CRectangle(int _x, int _y, int _w, int _h);
	CRectangle(CPoint startingPoint);

	bool ContainsPoint(CPoint p);
	void IncreaseSize(int dx, int dy);
	void Scale(double multiplier);
	void SetSize(int _w, int _h);
	void Translate(int dx, int dy);

protected:

private:

};

