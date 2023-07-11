//
// Created by magne on 6/22/2021.
//


#include "DocumentParser.h"

Paper DocumentParser::parseJSON(DSString& filePath) {
    // references:
    // https://stackoverflow.com/questions/609203/read-file-names-from-a-directory/609236#609236
    // https://www.codegrepper.com/code-examples/cpp/how+to+read+and+parse+a+json+file+with+rapidjson
    // https://rapidjson.org/
    // and eric's sample.cpp from zulip chat (used heavily for data collection)

    // create json Document (doc) from json file address (filePath)
    FILE *theJson = fopen(filePath.c_str(), "r");
    rapidjson::FileReadStream input(theJson, buffer, sizeof(buffer));
    rapidjson::Document doc;
    doc.ParseStream(input);
    fclose(theJson);

    // collect data from json Document (doc) and put into Paper datatype (thePaper)
    // we are collecting title, id, full text, full abstract, and authors' last names
    Paper thePaper;
    thePaper.title = doc["metadata"]["title"].GetString();
    thePaper.id = doc["paper_id"].GetString();
    DSVector<DSString> text;
//    for (int i = 0; i < doc["abstract"].Size(); i++)
//        text.push_back(doc["abstract"][i]["text"].GetString());
    for (int i = 0; i < doc["body_text"].Size(); i++)
        text.push_back(doc["body_text"][i]["text"].GetString());

    // add all authors' last names to thePaper's author DSVector<DSString> (thanks eric)
    rapidjson::Value::MemberIterator attributeIterator = doc.FindMember( "metadata" );
    const rapidjson::Value& attributes = doc["metadata"][ "authors" ];
    assert(attributes.IsArray()); // attributes is an array
    for (rapidjson::Value::ConstValueIterator itr = attributes.Begin(); itr != attributes.End(); ++itr) {
        const rapidjson::Value& attribute = *itr;
        for (rapidjson::Value::ConstMemberIterator itr2 = attribute.MemberBegin(); itr2 != attribute.MemberEnd(); ++itr2) {
            if(itr2->name.IsString() && itr2->value.IsString()){
                if(strlen(itr2 -> value.GetString()) > 0) {
                    if (DSString(itr2->name.GetString()) == DSString("last"))
                        thePaper.authors.push_back(DSString(itr2->value.GetString()));
                }
            }
        }
    }

    // format the paper, removing stop words and stemming all remaining words
    thePaper.format(stopWords, text);

    // return the completed Paper
    return thePaper;
}

DocumentParser::DocumentParser(){
    // prepare stop word vector
    std::ifstream in("stopWords.txt");
    char buf[30];
    while (in.is_open()){
        in.getline(buf, 30, '\n');
        DSString myWord(buf);
        if (myWord != DSString(""))
            stopWords.push_back(myWord);
        else
            in.close();
    }
}
