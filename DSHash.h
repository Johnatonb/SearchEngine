//
// Created by johnk on 6/22/2021.
//
#pragma once
#include "DSString.h"
#include "list.h"

#ifndef INC_21SU_SRCH_ENG_DSHASH_H
#define INC_21SU_SRCH_ENG_DSHASH_H

template<typename T1, typename T2>
class DSHash {
public:
    struct Node{
        T1 key;
        T2 value;
        Node(const T1& k, const T2& v): key(k), value(v){};
    };
    void insert(T1 key, T2 val);
    void clear();
    ~DSHash();
    DSHash();
    T2& operator[](T1& theKey);
private:
    list<Node>* data = nullptr;
    size_t size = 0;
    size_t cap = 100003;

    size_t hash(const T1& key);
    void rehash();
};

template<typename T1, typename T2>
DSHash<T1, T2>::DSHash() {
    data = new list<Node>[100003];
}

template<typename T1, typename T2>
size_t DSHash<T1, T2>::hash(const T1 &key) {
    return std::hash<std::string>()(key.c_str());
}

template<typename T1, typename T2>
void DSHash<T1, T2>::insert(T1 key, T2 val) {
    if ((double) size / (double) cap >= 1 && size!=0)
        rehash();
    size_t loc = hash(key) % cap;
    data[loc].push_front(Node(key, val));
    size++;
}

template<typename T1, typename T2>
void DSHash<T1, T2>::rehash() {
    DSHash<T1, T2> newTable;
    newTable.cap = cap*2;
    newTable.data = new list<Node>[newTable.cap];
    for (size_t i = 0; i < cap; i++){
        if (data[i].getSize()>0){
            for (int j = 0; j < data[i].getSize(); j++){
                size_t loc = hash(data[i].at(j).key) % newTable.cap;
                newTable.data[loc].push_front(Node(data[i].at(j).key, data[i].at(j).value));
                newTable.size++;
            }
        }
    }
    delete[] data;
    cap*=2;
    data = newTable.data;
    size = newTable.size;
}

template<typename T1, typename T2>
T2& DSHash<T1, T2>::operator[](T1 &theKey) {
    size_t loc = hash(theKey) % cap;
    for (int i = 0; i< data[loc].getSize(); i++){
        if (data[loc].at(i).key == theKey){
            return data[loc].at(i).value;
        }


    }
    throw std::out_of_range("key does not exist in hash table...");
}

template<typename T1, typename T2>
void DSHash<T1, T2>::clear() {
    delete[] data;
    data = new list<Node>[100003];
}

template<typename T1, typename T2>
DSHash<T1, T2>::~DSHash() {
    delete[] data;
}


#endif //INC_21SU_SRCH_ENG_DSHASH_H
