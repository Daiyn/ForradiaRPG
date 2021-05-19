/*+===================================================================
  File:      CPOINT.H

  Summary:   Describes the commonly used simple geometric class 
			 Point and its several point data manipulation methods.

  Classes:   Point

  Functions: 

  Origin:    Written by Andreas Åkerberg.

  This software is open source and licensed under the MIT License.
===================================================================+*/

#pragma once

#define RANDOM_WITHIN_MAP 1
#define MAP_CENTER 2
#define HOVERED_TILE 3

/*C+C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C
  Class:    Point

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

class Point
{
public:

	int m_x;
	int m_y;

	Point() = default;
	Point(int flags);
	Point(int _x, int _y);

	bool Equals(Point p);
	//Point GetAbsDistanceToPlayer();
	void JumpToHoveredTile();
	void JumpToScreenStart();
	void JumpRight();
	void JumpToNextRowStart();
	void Translate(int dx, int dy);
	bool WithinMap();

protected:

private:

};

class Point3D
{
public:
	int m_x;
	int m_y;
	int m_z;
};

