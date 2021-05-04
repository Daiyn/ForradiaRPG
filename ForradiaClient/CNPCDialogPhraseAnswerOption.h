/*+===================================================================
  File:      CNPCDIALOGPHRASEANSWEROPTION.H

  Summary:   Describing one of the building block classes for
             NPC-player dialogs.

  Classes:   CNPCDialogPhraseAnswerOption

  Functions: 

  Origin:    Written by Andreas Åkerberg.

  This software is open source and licensed under the MIT License.
===================================================================+*/

#ifndef FORRADIAFORMATION_NPCDIALOGPHRASEANSWEROPTION_H
#define FORRADIAFORMATION_NPCDIALOGPHRASEANSWEROPTION_H

#include <string>
#include <tuple>

using std::string;

/*C+C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C
  Class:    CNPCDialogPhraseAnswerOption

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

class CNPCDialogPhraseAnswerOption
{
public:

    string m_answerText;
    std::tuple<int, int, int> m_instructObjectCreation = {-1, -1, -1};
    int m_idxAnswerMakeJumpToPhrase = -1;

    CNPCDialogPhraseAnswerOption(string _text, int _answerMakeJumpToPhrase);

protected:

private:

};


#endif
