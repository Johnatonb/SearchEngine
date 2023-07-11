//
// Created by johnk on 6/10/2021.
//

#pragma once
#include <functional>
#include <cstring>

#ifndef INC_21SU_PA02_TEMPLATE_DSVECTOR_H
#define INC_21SU_PA02_TEMPLATE_DSVECTOR_H

template<typename T>
class DSVector{
private:
    T* data = nullptr;
    size_t Size = 0;
    size_t Capacity = 1;

    void heapify(DSVector<T> &vec,int i, int heapSize);
    void heapsort(DSVector<T> &vec);
    void heapify(DSVector<T> &vec,int i, int heapSize, std::function<bool(T,T)> lessThan);
    void heapsort(DSVector<T> &vec,std::function<bool(T,T)> lessThan);

    int partition(DSVector<T> &vec, int low, int high);
    int partition(DSVector<T> &vec, int low, int high, std::function<bool(T,T)> lessThan);
    void quicksort(DSVector<T> &vec, int low, int high);
    void quicksort(DSVector<T> &vec, int low, int high, std::function<bool(T,T)> lessThan);
public:
    DSVector() = default;
    DSVector(const DSVector &vec);
    ~DSVector();

    class iterator{
    protected:
        T* itr = nullptr;
    public:
        explicit iterator(T* p);
        iterator(const iterator &i);
        iterator& operator=(const iterator &i);
        T& operator*();
        iterator& operator++();
        bool operator==(iterator &i);
        bool operator!=(iterator &i);
    };
    DSVector& operator=(const DSVector&);
    T& operator[](const size_t&) const;
    bool operator==(const DSVector&) const;
    bool operator<(const DSVector&) const;
    bool operator>(const DSVector&) const;
    bool operator!=(const DSVector&) const;

    iterator& begin() const;
    iterator& end() const;

    [[nodiscard]] bool empty() const;
    [[nodiscard]] size_t size() const;
    void reserve(const size_t&);
    void clear();
    [[nodiscard]] size_t capacity() const;

    void insert(const size_t&, T);
    //I talked with Dr. Fontenot and he that I didn't have to implement push_front after discussing its utility
    void push_back(T);
    void pop_back();

    int find(std::function<bool(T)> pred);
    int find(const T&);
    bool contains(std::function<bool(T)> pred);
    bool contains(const T&);

    void sort();
    void sort(std::function<bool(T,T)> lessThan);
};

template<typename T>
DSVector<T>::iterator::iterator(T *p) {
    itr = p;
}

template<typename T>
DSVector<T>::iterator::iterator(const iterator &i) {
    itr = i.itr;
}

template<typename T>
typename DSVector<T>::iterator& DSVector<T>::iterator::operator=(const iterator &i) {
    itr = i.itr;
    return *this;
}

template<typename T>
T& DSVector<T>::iterator::operator*() {
    if(!itr){throw std::range_error("This is not a valid iterator");}
    return itr->data;
}

template<typename T>
typename DSVector<T>::iterator& DSVector<T>::iterator::operator++(){
    if(!itr){throw std::range_error("This is not a valid iterator");}
    itr++;
    return *this;
}

template<typename T>
bool DSVector<T>::iterator::operator==(DSVector::iterator &i){
    return (itr == i);
}

template<typename T>
bool DSVector<T>::iterator::operator!=(DSVector::iterator &i){
    return (itr != i);
}

template<typename T>
DSVector<T>::DSVector(const DSVector &vec){
    data = new T[vec.capacity()];
    for(int j = 0; j< vec.Size;j++)
        data[j] = vec[j];
    Size = vec.size();
    Capacity = vec.Capacity;
}

template<typename T>
DSVector<T>::~DSVector(){
    delete[] data;
}

template<typename T>
DSVector<T>& DSVector<T>::operator=(const DSVector &i){
    if(&i.data == &data){return *this;}
    if(data) delete[] data;
    data = new T[i.capacity()];
    for(int j = 0; j< i.Size;j++)
        data[j] = i[j];
    Size = i.Size;
    Capacity = i.Capacity;
    return *this;
}

template<typename T>
T& DSVector<T>::operator[](const size_t &pos) const{
    if(pos>=Size){throw std::range_error("This is out of bounds");}
    return *(data + pos);
}

template<typename T>
bool DSVector<T>::operator==(const DSVector& vec) const{
    if(Capacity!=vec.Size){return false;}
    return memcmp(data,vec.data,vec.Size);
}

template<typename T>
bool DSVector<T>::operator<(const DSVector& vec) const{
    return Size < vec.Size;
}

template<typename T>
bool DSVector<T>::operator>(const DSVector& vec) const{
    return Size > vec.Size;
}

template<typename T>
bool DSVector<T>::operator!=(const DSVector& vec) const{
    return !(*this == vec);
}

template<typename T>
typename DSVector<T>::iterator& DSVector<T>::begin() const{
    return iterator(data);
}

template<typename T>
typename DSVector<T>::iterator& DSVector<T>::end() const{
    return iterator(data + Size);
}

template<typename T>
[[nodiscard]] bool DSVector<T>::empty() const{
    return data == nullptr;
}

template<typename T>
[[nodiscard]] size_t DSVector<T>::size() const{
    return Size;
}

template<typename T>
void DSVector<T>::reserve(const size_t &i) {
    if(i < Size){return;}
    T* temp;
    temp = new T[i];
    for(int j = 0; j< Size;j++)
        temp[j] = data[j];
    delete[] data;
    data = temp;
    Capacity = i;
}

template<typename T>
void DSVector<T>::clear() {
    for(int i = 0; i < Size; i++){
        ~data[i];
    }
    Size = 0;
}

template<typename T>
[[nodiscard]] size_t DSVector<T>::capacity() const{
    return Capacity;
}

template<typename T>
void DSVector<T>::insert(const size_t &pos, T value){
    if(Size+1>Capacity){reserve(Capacity*2);}
    if(pos>=Capacity){throw std::range_error("This is out of bounds");}
    for(int i = Size; i > pos; i--){data[i] = data[i-1];}
    data[pos] = value;
    Size++;
}

template<typename T>
void DSVector<T>::push_back(T value){
    if(Size == 0){data = new T[1];}
    else if(Size+1>Capacity){reserve(Capacity*2);}
    data[Size] = value;
    Size++;
}

template<typename T>
void DSVector<T>::pop_back(){
    ~data[Size-1];
    Size--;
}

template<typename T>
int DSVector<T>::find(const T& key) {
    for(int i = 0; i < Size; i++){
        T  temp = data[i];
        if(data[i] == key){

            return i;
        }
    }
    return -1;
}

template<typename T>
int DSVector<T>::find(std::function<bool(T)> pred) {
    for(int i = 0; i < Size; i++){
        if(pred(data[i])){return i;}
    }
    return -1;
}

template<typename T>
bool DSVector<T>::contains(const T& key) {
    return find(key) != -1;
}

template<typename T>
bool DSVector<T>::contains(std::function<bool(T)> pred) {
    return find(pred) != -1;
}

template<typename T>
int DSVector<T>::partition(DSVector<T> &vec, int low, int high){
    T pivot = vec[high];
    int i = low;
    for(int j = low; j < high; j++){
        if(vec[j] < pivot){

            T temp = vec[i];
            vec[i] = vec[j];
            vec[j] = temp;
            i++;
        }
    }
    T temp = vec[i];
    vec[i] = vec[high];
    vec[high] = temp;
    return i;
}

template<typename T>
int DSVector<T>::partition(DSVector<T> &vec, int low, int high, std::function<bool(T,T)> lessThan){
    T pivot = vec[high];
    int i = low;
    for(int j = low; j < high; j++){
        if(lessThan(vec[j],pivot)){
            //Performs a swap
            T temp = vec[i];
            vec[i] = vec[j];
            vec[j] = temp;
            i++;
        }
    }
    //Performs a swap
    T temp = vec[i];
    vec[i] = vec[high];
    vec[high] = temp;
    return i;
}

template<typename T>
void DSVector<T>::quicksort(DSVector<T> &vec, int low, int high){
    if(low<high){
        int p = partition(vec,low,high);
        quicksort(vec,low,p-1);
        quicksort(vec,p+1,high);
    }
}

template<typename T>
void DSVector<T>::quicksort(DSVector<T> &vec, int low, int high, std::function<bool(T,T)> lessThan){
    if(low<high){
        int p = partition(vec,low,high, lessThan);
        quicksort(vec,low,p-1, lessThan);
        quicksort(vec,p+1,high, lessThan);
    }
}

template<typename T>
void DSVector<T>::heapify(DSVector<T> &vec, int n, int i){
    int left = 2*i+1;
    int right = 2*i+2;
    int largest = i;
    if(left < n && vec[i] < vec[left]){
        largest = left;
    }
    if(right < n && vec[largest] < vec[right]){
        largest = right;
    }
    if(largest != i){
        T temp = vec[i];
        vec[i] = vec[largest];
        vec[largest] = temp;
        heapify(vec,n,largest);
    }
}

template<typename T>
void DSVector<T>::heapsort(DSVector<T> &vec){
    for(int i = Size/2 - 1; i >= 0; i--){
        heapify(vec,i,Size);
    }
    for(int i = Size-1; i >= 0; i--){
        T temp = vec[0];
        vec[0] = vec[i];
        vec[i] = temp;
        heapify(vec,i,0);
    }
}

template<typename T>
void DSVector<T>::heapify(DSVector<T> &vec,int n, int i, std::function<bool(T,T)> lessThan){
    int left = 2*i+1;
    int right = 2*i+2;
    int largest = i;
    if(left < n && lessThan(vec[i],vec[left])){
        largest = left;
    }
    if(right < n && lessThan(vec[largest],vec[right])){
        largest = right;
    }
    if(largest != i){
        T temp = vec[i];
        vec[i] = vec[largest];
        vec[largest] = temp;
        heapify(vec,n,largest,lessThan);
    }
}

template<typename T>
void DSVector<T>::heapsort(DSVector<T> &vec,std::function<bool(T,T)> lessThan){
    for(int i = Size/2 - 1; i >= 0; i--){
        heapify(vec,i,Size,lessThan);
    }
    for(int i = Size-1; i >= 0; i--){
        T temp = vec[0];
        vec[0] = vec[i];
        vec[i] = temp;
        heapify(vec,i,0,lessThan);
    }
}

template<typename T>
void DSVector<T>::sort(){
    quicksort(*this,0,Size - 1);
}

template<typename T>
void DSVector<T>::sort(std::function<bool(T,T)> lessThan){
    quicksort(*this,0,Size - 1,lessThan);
}

#endif //INC_21SU_PA02_TEMPLATE_DSVECTOR_H
