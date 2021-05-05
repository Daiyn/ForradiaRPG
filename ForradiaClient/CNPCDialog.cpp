#include "CNPCDialog.h"
#include "CNPCDialogPhrase.h"

CNPCDialogPhrase CNPCDialog::getCurrentPhrase()
{
    return m_talkingPhrases[m_iterCurrentPhrase];
}