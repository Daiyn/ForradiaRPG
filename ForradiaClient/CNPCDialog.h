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
#include <string>

using std::string;
using std::vector;

class CNPCDialogPhrase;
class CNPCDialogPhraseAnswerOption;

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

    vector<CNPCDialogPhrase> m_talkingPhrases;
    int m_iterCurrentPhrase = 0;

    CNPCDialogPhrase getCurrentPhrase();

protected:

private:

};


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

    vector<string> m_textblockTextLines;
    vector<CNPCDialogPhraseAnswerOption> m_optAnswers;

protected:

private:

};




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
    std::tuple<int, int, int> m_instructObjectCreation = { -1, -1, -1 };
    int m_idxAnswerMakeJumpToPhrase = -1;

    CNPCDialogPhraseAnswerOption(string _text, int _answerMakeJumpToPhrase);

protected:

private:

};


#endif