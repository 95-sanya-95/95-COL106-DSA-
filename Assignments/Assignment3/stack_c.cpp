#include "stack_c.h"

#include <iostream>
using namespace std;
#include <stdexcept>

Stack_C::Stack_C(){
    try{
   stk = new List;
}
    catch (exception error){
        throw runtime_error("Out of Memory");
    }
}

Stack_C::~Stack_C(){
    delete stk;
}

void Stack_C::push(int data){
    stk->insert(data);   //memory limit exceed case ????
}

int Stack_C::pop(){
    int t;
    t = stk->delete_tail();
    return t;
}

int Stack_C::get_element_from_top(int idx){ //from top means from tail
    Node * current = stk->get_head();
    int q= stk->get_size();
    for (int t=0; t<=q-idx-1; t++){
        current = current->next;
    }
    int p = current->get_value();
    return p;
}

int Stack_C::get_element_from_bottom(int idx){
    Node * current = stk->get_head();
    for (int t=0; t<=idx; t++){
        current = current->next;
    }
    int p = current->get_value();
    return p;
}

void Stack_C::print_stack(bool top_or_bottom){
    int q= stk->get_size();
    int arr[q];
    if (top_or_bottom ==1){
        for (int i=0; i<=(q-1); i++){
                cout << arr[q-i-1] << endl;
            }
    }
    else{
        Node * current = stk->get_head();
        int q= stk->get_size();
        for (int t=0; t<=q-1; t++){
            cout<< current->get_value() <<endl;
            arr[t]=current->get_value();
            current = current->next;
        }
    }
}

int Stack_C::add(){
    if (stk->get_size()<=1){
        throw runtime_error("Not Enough Arguments");
    }
    else{
        int p = stk->delete_tail();
        int q = stk->delete_tail();
        int add = p +q;
        stk->insert(add);
        return add;
    }
}

int Stack_C::subtract(){
    if (stk->get_size()<=1){
        throw runtime_error("Not Enough Arguments");
    }
    else{
        int p = stk->delete_tail();
        int q = stk->delete_tail();
        int sub = q - p;
        stk->insert(sub);
        return sub;
    }
}

int Stack_C::multiply(){
    if (stk->get_size()<=1){
        throw runtime_error("Not Enough Arguments");
    }
    else{
        int p = stk->delete_tail();
        int q = stk->delete_tail();
        int mult = q * p;
        stk->insert(mult);
        return mult;
    }
}

int Stack_C::divide(){
    if (stk->get_size()<=1){
        throw runtime_error("Not Enough Arguments");
    }
    else{
        int p = stk->delete_tail();
        int q = stk->delete_tail();
        if (p ==0){
            throw runtime_error("Divide by Zero Error");
        }
        else{
        int div = (q) / p;
            if ((p)*(q) <0){
                div = div -1;
            }
        stk->insert(div);
        return div;
        }
    }
}

List * Stack_C::get_stack(){
    return stk;
}

int Stack_C::get_size(){
    int p = stk->get_size();
    return p;
}