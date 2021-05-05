/*+===================================================================
  File:      CNPCDIALOG.H

  Summary:   Describes building block class in NPC-player-dialogs.

  Classes:   CNPCDialog
             CNPCDialogPhrase

  Functions: 

  Origin:    Written by Andreas Åkerberg.

  This software is open source and licensed under the MIT License.
===================================================================+*/

#ifndef FORRADIAFORMATION_NPCDIALOG_H
#define FORRADIAFORMATION_NPCDIALOG_H

#include <vector>
#include "CNPCDialogPhrase.h"

//class CNPCDialogPhrase;

/*C+C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C
  Class:    CNPCDialog

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

class CNPCDialog
{
public:

    std::vector<CNPCDialogPhrase> m_talkingPhrases;
    int m_iterCurrentPhrase = 0;

    CNPCDialogPhrase getCurrentPhrase();

protected:

private:

};

#endif