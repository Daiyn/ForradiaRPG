/*+===================================================================
  File:      COBJECT.H

  Summary:   Describes essential CObject class of which lots are
             instantiated in the CMap clas.

  Classes:   CObject
             CPoint

  Functions: 

  Origin:    Written by Andreas Åkerberg.

  This software is open source and licensed under the MIT License.
===================================================================+*/

#ifndef FORRADIAFORMATION_OBJECT_H
#define FORRADIAFORMATION_OBJECT_H

#define OBJECT_IN_AIR_OR_INVENTORY -1

class CPoint;

/*C+C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C
  Class:    CObject

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

class CObject
{
public:

    int m_idxObjectType = -1;
    int m_coordMapX;
    int m_coordMapY;
    int m_propCurrentAmount = 100;
    int m_propCurrentQuantity = 1;
    int m_uniqueID;
    int m_tickTimeToVanish = 0;
    int m_idxVanishingEffect = -1;

    static int s_cntMaxObjectID;

    CObject(unsigned short _objectType, CPoint p);
    CObject(unsigned short _objectType, CPoint p, int _quantity);

protected:

private:

};


#endif
