//
// Created by magne on 6/22/2021.
//

#include "Paper.h"
#include "porter2_stemmer.h"

void Paper::format(DSVector<DSString>& stopWords, DSVector<DSString>& text) {
    // format abstract and full text
    for (int i = 0; i < text.size(); i++){
        std::string textLine = text[i].c_str();
        DSVector<DSString> textWords = DSString(textLine.c_str()).tokenize();
        for (int j = 0; j < textWords.size(); j++){
            std::string s = textWords[j].c_str();
            Porter2Stemmer::trim(s);
            DSString word = DSString(s.c_str());

            if (stopWords.find(word) == -1){
                Porter2Stemmer::stem(s);
                DSString formattedString(s.c_str());
                textFormatted.push_back(formattedString);
            }
        }
    }
}



