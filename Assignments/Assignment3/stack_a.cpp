#include "stack_a.h"

#include <iostream>
using namespace std;
#include <stdexcept>

Stack_A::Stack_A(){
    size = 0;
};

void Stack_A:: push(int data){
        if (size ==1024){
            throw runtime_error("Stack Full");
        }
        else{
        size = size +1;
        stk[size -1] = data;
        }
    };

int Stack_A::pop(){
        if (size == 0){
            throw runtime_error("Empty Stack");
        }
        else {
        int last;
        last = stk [size -1];  //returning the last element 
        size = size -1;
        return last ; 
        } 
    };

int Stack_A::get_element_from_top(int idx){
        if (idx >= size){
            throw runtime_error("Index out of range");
        }
        else {
        return stk[size - idx -1];
        }
    };

int Stack_A::get_element_from_bottom(int idx){
        if (idx >= size){
            throw runtime_error("Index out of range");
        }
        else {  
        return stk[idx];
        }
    };

void Stack_A::print_stack(bool top_or_bottom){
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
    };

    int Stack_A::add(){
        if (size <= 1){
            throw runtime_error("Not Enough Arguments");
        }
        else{
            int add = stk[size -2] + stk[size -1];
            Stack_A::pop();
            Stack_A::pop();
            Stack_A::push(add);
            return add;
        }
    };

    int Stack_A::subtract(){
        if (size <= 1){
            throw runtime_error("Not Enough Arguments");
        }
        else{
            int sub = stk[size -2] - stk[size -1];
            Stack_A::pop();
            Stack_A::pop();
            Stack_A::push(sub);
            return sub;
        }
    };

    int Stack_A::multiply(){
        if (size <= 1){
            throw runtime_error("Not Enough Arguments");
        }
        else{
            int mult =(stk[size -2] * stk[size -1]);
            Stack_A::pop();
            Stack_A::pop();
            Stack_A::push(mult);
            return mult;
        }
    };

    int Stack_A::divide(){
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
            Stack_A::pop();
            Stack_A::pop();
            Stack_A::push(div);
            return div;
        }
    };//floor(static_cast<double>(stk[size -2]) / stk[size -1])

    int* Stack_A::get_stack(){
        int *ptr = stk;     // ASSIGNING POINTER TO AN ARRAY....
        return ptr;           
    }; // Get a pointer to the array

    int Stack_A::get_size(){
        return size;
    };// Get the size of the stack

// int main(){
//     Stack_A lst;
//     lst.push(25);
//     lst.push(10);
//     lst.push(-6);
//     lst.push(4);
//     lst.push(-15);
//     lst.push(4);
//     lst.push(5);
//     lst.push(11);
//     lst.push(-9);
//     lst.push(-7);
//     cout << lst.add() << endl;
//     cout <<lst.add()<< endl;
//     cout <<lst.add()<< endl;
//     cout <<lst.subtract()<< endl;
//     cout <<lst.subtract()<< endl;
//     cout <<lst.divide()<< endl;
//     cout <<lst.divide()<< endl;
//     cout <<lst.multiply()<< endl;
//     cout <<lst.multiply()<< endl;
// }