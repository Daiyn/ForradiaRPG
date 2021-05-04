#include "CNPCDialog.h"
#include "CNPCDialogPhrase.h"

CNPCDialogPhrase CNPCDialog::getCurrentPhrase()

{
    return m_talkPhrases[m_iterCurrentPhrase];

}