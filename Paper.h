//
// Created by magne on 6/22/2021.
//

#ifndef INC_21SU_SRCH_ENG_PAPER_H
#define INC_21SU_SRCH_ENG_PAPER_H

#pragma once
#include "DSString.h"
#include "DSVector.h"

class Paper {
public:
    DSString title;
    DSVector<DSString> authors;
    DSString id;
    DSString publication;
    DSString date;
    DSVector<DSString> textFormatted;       // formatted abstract followed by formatted full text; each string is a word
    Paper() = default;

    void format(DSVector<DSString> &stopWords, DSVector<DSString> &text);
};


#endif //INC_21SU_SRCH_ENG_PAPER_H
