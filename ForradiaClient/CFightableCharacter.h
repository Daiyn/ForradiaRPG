/*+===================================================================
  File:      CFIGHTABLECHARACTER.H

  Summary:   Describes parent class for all characters that can take
			 part in battles.

  Classes:   CFightableCharacter

  Functions: 

  Origin:    Written by Andreas Åkerberg.

  This software is open source and licensed under the MIT License.
===================================================================+*/

#pragma once

#define CHARACTER_TYPE_PLAYER 0
#define CHARACTER_TYPE_FOE 1

/*C+C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C
  Class:    CFightableCharacter

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

class CFightableCharacter
{
public:

	int m_idxCharacterType = -1;
	int m_statCurrentHP;

	CFightableCharacter(int starthp, int characterType);

	void Hit(int damage);

protected:

private:

};

