//
// Created by magne on 6/26/2021.
//

#ifndef INC_21SU_SRCH_ENG_QUERYENGINE_H
#define INC_21SU_SRCH_ENG_QUERYENGINE_H


#include "Index.h"

class QueryEngine {
private:
    Index theIndex;
    DSVector<std::pair<DSString, size_t>> results;
    DSVector<DSString> queryEntries;
    void startSearch();
    DSString formatWord(DSString& word);
public:
    QueryEngine(DSString& arg);

    DSVector<std::pair<DSString, size_t>> searchWord(int&);
};


#endif //INC_21SU_SRCH_ENG_QUERYENGINE_H
