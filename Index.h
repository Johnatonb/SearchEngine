//
// Created by johnk on 6/23/2021.
//

#pragma once
#include "DSString.h"
#include "DSTree.h"
#include "DSVector.h"
#include "DSHash.h"
#include "DocumentParser.h"
#include <filesystem>

#ifndef INC_21SU_SRCH_ENG_INDEX_H
#define INC_21SU_SRCH_ENG_INDEX_H


class Index {
public:
    struct inWord{
        DSString word;
        bool operator<(const inWord& word) const;
        DSVector<std::pair<DSString,size_t>> docFreq;
        inWord() = default;
        inWord(DSString w, DSString id, size_t freq);

    };

    struct documentMetadata{
        DSString id;
        DSString title;
        DSVector<DSString> authors;
    };
    void indexFolder(char* folderPath);
    DSVector<std::pair<DSString,size_t>> getWordFreq(DSString word);
    DSVector<std::pair<DSString,size_t>> getDoubleWordFreq(DSString word);
    DSVector<DSString> getAuthorDoc(DSString author);
    void clearIndex();
    void printStats();
    void printMetadata(DSString id);
private:
    int totalArticles = 0;
    int uniqueWords = 0;
    double avgWords = 0.0;
    DSVector<inWord*> topWords;
    int uniqueAuthors = 0;
    DSTree<inWord> wordIndex;
    DSTree<inWord> doubleWordIndex;
    DSHash<DSString,DSVector<DSString>> authorIndex;
    DSVector<documentMetadata> metadata;
};


#endif //INC_21SU_SRCH_ENG_INDEX_H
