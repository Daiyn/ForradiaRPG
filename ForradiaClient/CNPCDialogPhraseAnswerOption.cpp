#include "CNPCDialogPhraseAnswerOption.h"


CNPCDialogPhraseAnswerOption::CNPCDialogPhraseAnswerOption(string _text, int _answerMakeJumpToPhrase)
{
    m_answerText = _text;
    m_idxAnswerMakeJumpToPhrase = _answerMakeJumpToPhrase;
}