//
// Created by magne on 6/7/2021.
//

#ifndef UNTITLED1_LIST_H
#define UNTITLED1_LIST_H

#include <iostream>

template <typename T>
class list {
private:
    struct list_node{
        T data;
        list_node* next, *prev;
        list_node(const T& arg, list_node* n = nullptr, list_node* p = nullptr):data(arg), next(n), prev(p) {};
        ~list_node(){
            delete next;
        }

    };
    list_node* front = nullptr;
    list_node* back = nullptr;
    int count_nodes = 0;

public:
    list() = default;
    list(const list&) = delete;
    ~list(){
        delete front;
    }

    void push_front(const T& val){
        list_node* tmp = new list_node(val);
        if (front == nullptr)
            front = back = tmp;
        else{
            front->prev = tmp;
            tmp->next = front;
            front = tmp;
        }
        count_nodes++;
    }
    void print_list(){
        list_node* curr = front;
        while (curr != nullptr){
            std::cout << curr->data << std::endl;
            curr = curr->next;
        }
    }

    T& at(int index){
        if (index > count_nodes || index < 0){
            throw std::out_of_range("list at() index out of range");
        }
        list_node* tmp = front;
        for (int i = 0; i < index; i++){
            tmp = tmp->next;
        }
        return tmp->data;
    }

    class iterator {
    protected:
        list_node* cur = nullptr;
    public:
        explicit iterator(list_node* c){
            cur = c;
        }
        iterator(const iterator& arg ){
            cur = arg.cur;
        }
        iterator& operator= (const iterator& arg){
            cur = arg.cur;
            return *this;
        }
        T& operator*(){
            if (!cur){
                throw std::range_error("");
            }
            return cur->data;
        }
        iterator& operator++(){
            if (!cur){
                throw std::range_error("");
            }
            cur = cur->next;
            return *this;
        }
        bool operator==(const iterator& rhs){
            return (cur == rhs.cur);
        }
        bool operator!=(const iterator& rhs){
            return (cur != rhs.cur);
        }
    };

    iterator begin(){
        return iterator(front);
    }
    iterator end(){
        return iterator(back->next);
    }

    void insert(int loc, const T& val){
        list_node* cur = at(loc);
        if (loc == 0){
            push_front(val);
        }
        else{
            list_node* temp = new list_node(val);
            temp->next = cur;
            temp->prev = cur->prev;
            cur->prev->next = temp;
            cur->prev = temp;
        }
        count_nodes++;
    }
    int getSize(){
        return count_nodes;
    }
};


template <typename K, typename V1, typename V2>
class triple{
public:
    K first;
    V1 second;
    V2 third;
    triple(const K& a1, const V1& a2, const V2& a3):
        first(a1), second(a2), third(a3) {}
};

#endif //UNTITLED1_LIST_H
