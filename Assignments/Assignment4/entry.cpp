/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "entry.h"

SymEntry::SymEntry(){
    key = "";
    val = nullptr;
    left = nullptr;
    right = nullptr;
}

SymEntry::SymEntry(string k, UnlimitedRational* v){
    key = k;
    
    left = nullptr;
    right = nullptr;
    val = new UnlimitedRational(v->get_p(), v->get_q());
}

SymEntry::~SymEntry(){
    delete val; 
    delete left;
    delete right;
}