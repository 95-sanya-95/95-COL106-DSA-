#include "list.h"

#include <iostream>
using namespace std;
#include <stdexcept>


List::List(){
    size=0;
    try{
    sentinel_head = new Node(true);
    sentinel_tail = new Node(true);
    }
    catch (exception error){
        throw runtime_error("Out of Memory");
    }
    sentinel_head->next = sentinel_tail;
    sentinel_tail->prev = sentinel_head;
};

List::~List(){
    while (sentinel_head->next != sentinel_tail){
        Node * temp = sentinel_head->next->next;
        delete sentinel_head->next;
        sentinel_head->next = temp;
    }
    delete sentinel_head;
    delete sentinel_tail;
};

void List::insert(int v){

        Node * newnode = new Node(v, sentinel_tail, sentinel_tail->prev);
        sentinel_tail->prev->next = newnode; //**
        sentinel_tail->prev = newnode;
        size = size +1;

};

int List::delete_tail(){
    if (sentinel_head->next == sentinel_tail){
        throw runtime_error("Empty Stack");
    }
    else{
        Node * A = sentinel_tail->prev->prev;
        Node * B = sentinel_tail->prev;
        int del;
        del = B->get_value();
        
        A->next = sentinel_tail;
        sentinel_tail->prev = A;
        delete B;
        
        size = size-1;
        return del;
    }
};

int List::get_size(){
    return size;
};

Node* List::get_head(){
    return sentinel_head;
};
