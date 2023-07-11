//
// Created by magne on 6/27/2021.
//

#include "QueryEngine.h"
#include "porter2_stemmer.h"

QueryEngine::QueryEngine(DSString& arg) {
    bool running = true;
    while (running) {
        std::cout << "1 - add a folder of data to index\n";
        std::cout << "2 - enter a search query\n";
        std::cout << "3 - clear indexer of all data\n";
        std::cout << "4 - print indexer statistics\n";
        std::cout << "5 - get a document's information\n";
        std::cout << "6 - end program\n\n";
        std::cout << "enter a number: ";
        char entry;
        std::cin >> entry;
        if (entry == '6') {
            running = false;
            std::cout << "see ya\n";
        }
        else if (entry == '5'){
            std::cout << "\nEnter a document ID (40 characters): ";
            char docID[41];
            std::cin.ignore();
            std::cin.clear();
            std::cin >> docID;
            // do something here
        }
        else if (entry == '4'){
            theIndex.printStats();
        }
        else if (entry == '3'){
            theIndex.clearIndex();
        }
        else if (entry == '2'){
            startSearch();
        }
        else if (entry == '1'){
            std::cout << "Data folder should exist in cmake-build-debug. (ex: \"ds_03\")\nEnter folder name: ";
            char folderName[40];
            std::cin >> folderName;
            std::cout << "Processing Documents... \n";
            theIndex.indexFolder(folderName);
            std::cout << "Processing Completed!\n";
        }
        else{
            std::cout << "Invalid entry, try again.\n";
        }
    }
}

void QueryEngine::startSearch() {
    std::cout << "\n\n Enter your query: ";
    std::string queryBuffer;
    std::cin.ignore();
    std::cin.clear();
    std::getline(std::cin, queryBuffer);
    DSString query = queryBuffer.c_str();
    if (query.c_str()[query.getLength()-1] != ' ')
        query = query + " ";
    queryEntries = query.tokenize();
    DSVector<std::pair<DSString, size_t>> temp;
    for (int i = 0; i < queryEntries.size(); i++){
        DSString theEntry = queryEntries[i];
        if (theEntry == DSString("AUTHOR")){
            DSVector<DSString> temp2 = theIndex.getAuthorDoc(queryEntries[++i]);
            if(results.empty()==true){
                for(int j = 0; j < temp2.size();j++){
                    results.push_back(std::pair<DSString,size_t>(temp2[j],0));
                }
            }else{
                for (int j = 0; j < results.size(); j++){
                    if (temp.contains([&](std::pair<DSString,size_t> p){return p.first == results[j].first;}))
                        temp.push_back(results[j]);
                }
                results = temp;
            }
        }
        else if (theEntry == DSString("NOT")){
            temp = searchWord(++i);
            DSVector<std::pair<DSString, size_t>> temp2;
            for (int j = 0; j < results.size(); j++){
                if (!temp.contains([&](std::pair<DSString,size_t> p){return p.first == results[j].first;}))
                    temp2.push_back(results[j]);
            }
            results = temp2;
        }
        else if (theEntry == DSString("AND")){
            DSVector<std::pair<DSString, size_t>> temp2;
            temp = searchWord(++i);
            for (int j = 0; j < temp.size(); j++){
                if (results.contains([&](std::pair<DSString,size_t> p){return p.first == temp[j].first;})) {
                    temp2.push_back(temp[j]);
                }
            }
            results = temp2;

        }
        else if (theEntry == DSString("OR")){
            temp = searchWord(++i);
            for (int j = 0; j < temp.size(); j++){
                if (!results.contains([&](std::pair<DSString,size_t> p){return p.first == temp[j].first;})){
                    results.push_back(temp[j]);
                }
            }
        }
        else{
            results = searchWord(i);
        }
    }
    results.sort([&](std::pair<DSString,size_t> left, std::pair<DSString,size_t> right){return left.second > right.second;});
    for (int k = 0; k < results.size() && k < 15; k++){
        theIndex.printMetadata(results[k].first);
    }
}

DSString QueryEngine::formatWord(DSString &word) {
    std::string s = word.c_str();
    Porter2Stemmer::trim(s);
    Porter2Stemmer::stem(s);
    DSString output = s.c_str();
    return output;
}

DSVector<std::pair<DSString, size_t>> QueryEngine::searchWord(int& i) {
    try {
        if (queryEntries[i].c_str()[0] == '[') {
            DSString word1 = formatWord(queryEntries[i]);
            DSString word2 = formatWord(queryEntries[++i]);
            word1 = word1 + " " + word2;
            return theIndex.getDoubleWordFreq(word1.c_str());
        }
        DSString myWord = formatWord(queryEntries[i]);
        return theIndex.getWordFreq(myWord.c_str());
    }
    catch (std::exception E) {
        std::cout << "invalid query, try again\n\n";
    }
}
