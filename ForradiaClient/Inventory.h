/*+===================================================================
  File:      CINVENTORY.H

  Summary:   Describes class responsible for holding and managing
			 the player inventory and its objects.

  Classes:   CInventory
			 CObject

  Functions: 

  Origin:    Written by Andreas Åkerberg.

  This software is open source and licensed under the MIT License.
===================================================================+*/

#pragma once

#include <unordered_map>
#include <memory>

using std::unique_ptr;
using std::unordered_map;

class Object;

/*C+C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C
  Class:    CInventory

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

class Inventory
{
public:

    unordered_map<int, unique_ptr<Object>> m_containedItems;

	bool HasItemInInventory(int objectType);
	bool SlotIsOccupied(int index);
	bool UseItemInInventory(int objectType, int _quantity);
    void AddItemToInventory(int objectType);

protected:

private:

};

