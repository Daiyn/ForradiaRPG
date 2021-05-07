#include "CNPCDialog.h"

CNPCDialogPhrase CNPCDialog::getCurrentPhrase()
{
    return m_talkingPhrases[m_iterCurrentPhrase];
}



CNPCDialogPhraseAnswerOption::CNPCDialogPhraseAnswerOption(string _text, int _answerMakeJumpToPhrase)
{
    m_answerText = _text;
    m_idxAnswerMakeJumpToPhrase = _answerMakeJumpToPhrase;
}