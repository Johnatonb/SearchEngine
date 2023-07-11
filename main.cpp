#include <iostream>
#include "DSString.h"
#include "DSVector.h"
#include "DSTree.h"
#include <filesystem>
#include "DocumentParser.h"
#include "Index.h"
#include "QueryEngine.h"

//Sorting my vector uses almost all the functionality of the vector
void vector_test(){
    DSTree<DSString> myVector;

    myVector.insert(DSString("9"));
    myVector.insert(DSString("8"));
    myVector.insert(DSString("4"));
    myVector.insert(DSString("3"));
    myVector.insert(DSString("7"));
    myVector.insert(DSString("2"));
    myVector.insert(DSString("6"));
    myVector.insert(DSString("1"));
    myVector.insert(DSString("5"));
    myVector.insert(DSString("0"));
    myVector.inOrder([](DSTree<DSString>::Node* node){std::cout<<node->data;});

    std::cout<<std::endl;
    std::cout<<myVector.find("1")->data<<std::endl;
}



int main(int argc, char** argv) {
    //vector_test();
    DSString arg = argv[1];
    QueryEngine queryProcessor(arg);

}
