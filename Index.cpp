//
// Created by johnk on 6/23/2021.
//

#include "Index.h"

Index::inWord::inWord(DSString w, DSString id, size_t freq) {
    word = w;
    docFreq.push_back(std::pair(id,freq));
}

bool Index::inWord::operator<(const inWord &theWord) const{
    return word < theWord.word;
}

void Index::indexFolder(char* folderPath) {
    DocumentParser myParser;
    DSVector<Paper> myPapers;
    int count = 0;
    for (auto& theFile : std::filesystem::directory_iterator(folderPath)){ // argv[1] = "ds_01"
        DSString filePath = theFile.path().c_str();
        Paper thePaper = myParser.parseJSON(filePath);
        if (thePaper.textFormatted.empty()){continue;}
        totalArticles++;
        avgWords = (double)thePaper.textFormatted.size()/(count + 1) + (avgWords * count) / (count + 1);
        // ignore empty papers
        for(int i = 0; i < thePaper.textFormatted.size(); i++){
            if(i + 1 < thePaper.textFormatted.size()){
                DSString twoWord = thePaper.textFormatted[i] + " " + thePaper.textFormatted[i+1];
                DSTree<inWord>::Node* wordNode = doubleWordIndex.find([&](inWord& theWord){return strcmp(thePaper.textFormatted[i].c_str(),theWord.word.c_str());});
                if(wordNode == nullptr){
                    doubleWordIndex.insert(inWord(thePaper.textFormatted[i],thePaper.id,1));
                }else{
                    if(wordNode->data.docFreq.contains([&](const std::pair<DSString,size_t>& freq){return freq.first == thePaper.id;})){
                        wordNode->data.docFreq[wordNode->data.docFreq.find([&](const std::pair<DSString,size_t>& freq){return freq.first == thePaper.id;})].second++;
                    }else{
                        wordNode->data.docFreq.push_back(std::pair(thePaper.id,1));
                    }
                }
            }
            DSTree<inWord>::Node* wordNode = wordIndex.find([&](inWord& theWord){return strcmp(thePaper.textFormatted[i].c_str(),theWord.word.c_str());});
            if(wordNode == nullptr){
                wordIndex.insert(inWord(thePaper.textFormatted[i],thePaper.id,1));
                uniqueWords++;
            }else{
                if(wordNode->data.docFreq.contains([&](const std::pair<DSString,size_t>& freq){return freq.first == thePaper.id;})){
                    wordNode->data.docFreq[wordNode->data.docFreq.find([&](const std::pair<DSString,size_t>& freq){return freq.first == thePaper.id;})].second++;
                }else{
                    wordNode->data.docFreq.push_back(std::pair(thePaper.id,1));
                }
            }
        }
        for(int i = 0; i < thePaper.authors.size(); i++){
            try{
                authorIndex[thePaper.authors[i]].push_back(thePaper.id);
            }
            catch(std::exception e){
                DSVector<DSString> initializedDocVec;
                initializedDocVec.push_back(thePaper.id);
                authorIndex.insert(thePaper.authors[i], initializedDocVec);
                uniqueAuthors++;
            }
        }
        metadata.push_back(documentMetadata{thePaper.id,thePaper.title,thePaper.authors});
        count++;
        if(count%500==0){std::cout<<"#"<<std::flush;}
    }
    std::cout<<std::endl;
    wordIndex.inOrder([&](DSTree<inWord>::Node* word){topWords.push_back(&word->data);});
    topWords.sort([](inWord* w1, inWord* w2){return w1->docFreq.size() > w2->docFreq.size();});
}

DSVector<std::pair<DSString, size_t>> Index::getWordFreq(DSString word) {
    DSTree<inWord>::Node* wordNode = wordIndex.find([&](inWord& theWord){return strcmp(word.c_str(),theWord.word.c_str());});
    DSVector<std::pair<DSString, size_t>> theVector;
    if(wordNode == nullptr){throw std::out_of_range("no such word");}
    for(int i = 0;i < wordNode->data.docFreq.size(); i++){
        theVector.push_back(wordNode->data.docFreq[i]);
    }
    return theVector;
}

DSVector<std::pair<DSString, size_t>> Index::getDoubleWordFreq(DSString word) {
    DSTree<inWord>::Node* wordNode = doubleWordIndex.find([&](inWord& theWord){return strcmp(word.c_str(),theWord.word.c_str());});
    DSVector<std::pair<DSString, size_t>> theVector;
    if(wordNode == nullptr){throw std::out_of_range("no such word");}
    for(int i = 0;i < wordNode->data.docFreq.size(); i++){
        theVector.push_back(wordNode->data.docFreq[i]);
    }
    return theVector;
}

DSVector<DSString> Index::getAuthorDoc(DSString author) {
    return authorIndex[author];
}

void Index::clearIndex() {
    metadata = DSVector<documentMetadata>();
    wordIndex.clear();
    authorIndex.clear();
}

void Index::printStats() {
    std::cout<<"\nTotal articles indexed: "<<totalArticles<<std::endl;
    std::cout<<"Average words per article: "<<avgWords<<std::endl;
    std::cout<<"Total unique words: "<<wordIndex.size()<<std::endl;


    std::cout<<"Top words by frequency: "<<std::endl;
    for(int i = 0; i < 15; i++){
        std::cout<<i<<". "<<topWords[i]->word<<std::endl;
    }
    std::cout<<"Total unique authors: "<<uniqueAuthors<<std::endl;
}

void Index::printMetadata(DSString id) {
    documentMetadata theData = metadata[metadata.find([&](documentMetadata data){return data.id == id;})];
    if(theData.title!=""){
        std::cout<<std::endl<<"Title: "<<theData.title<<std::endl;
    }else{
        std::cout<<std::endl<<"ID: "<<theData.id<<std::endl;
    }

    std::cout<<"Authors: ";
    for(int i = 0; i <theData.authors.size();i++){
        std::cout<<theData.authors[i];
        if(i < theData.authors.size()-1){
            std::cout<<", ";
        }
    }
    std::cout<<std::endl<<std::endl;
}