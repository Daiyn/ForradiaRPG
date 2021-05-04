/*+===================================================================
  File:      CSIZE.H

  Summary:   Describes small helpful geometry class.

  Classes:   CSize

  Functions: 

  Origin:    Written by Andreas Åkerberg.

  This software is open source and licensed under the MIT License.
===================================================================+*/

#pragma once

/*C+C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C
  Class:    CSize

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

class CSize
{
public:

	int m_w;
	int m_h;

	CSize(int _w, int _h);
	CSize(double _w, double _h);
	CSize(int size);

	void Scale(double scale);

protected:

private:

};

