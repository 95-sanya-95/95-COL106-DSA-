#include "stack_b.h"  

#include <iostream>
using namespace std;
#include <stdexcept>


Stack_B::Stack_B(){
        try{
        stk = new int[1024];
        }
        catch (exception error){
            throw runtime_error("Out of Memory");
        }
        capacity = 1024;
        size =0;
    }

    // Destructor
Stack_B::~Stack_B(){
    delete [] stk;
    }

void Stack_B::push(int data){
    if (size % 1024 == 0){
        int* new_stack = new int[capacity*2];

        for (int i=0; i<=(size -1); i++){
                new_stack[i]= stk[i];
            }
            delete stk;
            stk = new_stack;
            capacity = capacity*2;
            stk[size] = data;
            size = size +1;
        }
        else{
            stk[size] = data;
            size = size +1;
        }
    };

int Stack_B::pop(){
        if (size == 0){
            throw std::runtime_error("Empty Stack");
        }
        
        else if ((size -1)*4 == capacity && capacity>1024){
            int* new_stack = new int[capacity/2];
            int last;
            for (int i=0; i<=(size -2); i++){
                    new_stack[i]= stk[i];
                }
                last = stk [size -1];  //returning the last element 
                delete stk;
                stk = new_stack;
                capacity = capacity/2;
                size = size -1;
                return last;
        }
        else{
            int last;
            last = stk [size -1];//returning the last element 
            size = size -1;
            return last;
        }
    };

int Stack_B::get_element_from_top(int idx){
        if (idx >= size){
            throw runtime_error("Index out of range");
        }
        else {
        return stk[size - idx -1];
        }
    }

int Stack_B::get_element_from_bottom(int idx){
        if (idx >= size){
            throw runtime_error("Index out of range");
        }
        else {  
        return stk[idx];
        }
    }

void Stack_B::print_stack(bool top_or_bottom){
        if (top_or_bottom){    
        for (int i=0; i<=(size-1); i++){
                cout << stk[size - i-1] << endl;
            }
        }
        else{
            for (int i=0; i<=(size-1); i++){
                cout << stk[i] << endl;
                }
        }
    }

int Stack_B::add(){
        if (size <= 1){
            throw runtime_error("Not Enough Arguments");
        }
        else{
            int add = stk[size -2] + stk[size -1];
            Stack_B::pop();
            Stack_B::pop();
            Stack_B::push(add);
            return add;
        }
    }

int Stack_B::subtract(){
        if (size <= 1){
            throw runtime_error("Not Enough Arguments");
        }
        else{
            int sub = stk[size -2] - stk[size -1];
            Stack_B::pop();
            Stack_B::pop();
            Stack_B::push(sub);
            return sub;
        }
    }

int Stack_B::multiply(){
        if (size <= 1){
            throw runtime_error("Not Enough Arguments");
        }
        else{
            int mult =(stk[size -2] * stk[size -1]);
            Stack_B::pop();
            Stack_B::pop();
            Stack_B::push(mult);
            return mult;
        }
    }

int Stack_B::divide(){
        if (size <= 1){
            throw runtime_error("Not Enough Arguments");
        }
        else if(stk[size -1] ==0){
            throw runtime_error("Divide by Zero Error");
        }
        else{
            int div = (stk[size -2]) / stk[size -1];
            if ((stk[size -2])*(stk[size -1]) <0){
                div = div -1;
            }
            Stack_B::pop();
            Stack_B::pop();
            Stack_B::push(div);
            return div;
        }
    }

int* Stack_B::get_stack(){  // Get a pointer to the array
        return stk;
    } 

int Stack_B::get_size(){ // Get the size of the stack
        return size;
    }