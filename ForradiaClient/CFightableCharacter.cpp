#include "CFightableCharacter.h"



CFightableCharacter::CFightableCharacter(int starthp, int _characterType)
{
	m_hpCurrent = starthp;
	m_idxCharacterType = _characterType;
}


void CFightableCharacter::Hit(int damage)
{
	m_hpCurrent -= damage;
}