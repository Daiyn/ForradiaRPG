/*+===================================================================
  File:      CNPCDIALOGPHRASE.H

  Summary:   Describes primary building block class for NPC-player
             dialogs.

  Classes:   CNPCDialogPhrase
             CNPCDialogPhraseAnswerOption

  Functions: 

  Origin:    Written by Andreas Åkerberg.

  This software is open source and licensed under the MIT License.
===================================================================+*/

#ifndef FORRADIAFORMATION_NPCDIALOGPHRASE_H
#define FORRADIAFORMATION_NPCDIALOGPHRASE_H

#include <string>
#include <vector>
#include "CNPCDialogPhraseAnswerOption.h"

using std::vector;
using std::string;


/*C+C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C
  Class:    CNPCDialogPhrase

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

class CNPCDialogPhrase
{
public:

    vector<string> m_txtblockTextLines;
    vector<CNPCDialogPhraseAnswerOption> m_optAnswers;

protected:

private:

};

#endif