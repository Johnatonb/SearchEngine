//
// Created by magne on 6/22/2021.
//



#ifndef INC_21SU_SRCH_ENG_DOCUMENTPARSER_H
#define INC_21SU_SRCH_ENG_DOCUMENTPARSER_H

#pragma once
#include "rapidjson/document.h"
#include "rapidjson/filereadstream.h"
#include "DSString.h"
#include "DSVector.h"
#include "Paper.h"
#include <iostream>
#include <fstream>

class DocumentParser {
private:
    char buffer[65535]{};
    DSVector<DSString> stopWords;

public:
    DocumentParser();
    Paper parseJSON(DSString&);
};


#endif //INC_21SU_SRCH_ENG_DOCUMENTPARSER_H
