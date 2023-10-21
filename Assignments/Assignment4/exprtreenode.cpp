/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "exprtreenode.h"
                                        // NEED TO GET CHECKED 
ExprTreeNode::ExprTreeNode(){
    type = "";
    left = nullptr;
    right = nullptr;
    val = nullptr;
    id="";
    evaluated_value = nullptr;
}

ExprTreeNode::ExprTreeNode(string t, UnlimitedRational* v){
    type = t;
    if (t == "VAL"){
        val = new UnlimitedRational(v->get_p(), v->get_q());
        evaluated_value = nullptr;
        left = nullptr;
        right = nullptr;
        id="";
    }
    else if(t == "VAR"){
        evaluated_value = v;
        id ="";
        left = nullptr;
        right = nullptr;
    }
    else{
        evaluated_value = v;
        id ="";
        left = nullptr;
        right = nullptr;
    }
}                          // DOUBTS REGARDING STRING OF THE VARIABLE

ExprTreeNode::ExprTreeNode(string t, UnlimitedInt* v){
    UnlimitedInt* den = new UnlimitedInt(1);
    type = t;
    if (t == "VAL"){
        val = new UnlimitedRational(v ,den);
        evaluated_value = nullptr;
        id="";
        left = nullptr;
        right = nullptr;
        delete den;
    }
    else if(t == "VAR"){
        evaluated_value = new UnlimitedRational(v ,den);
        id ="";
        left = nullptr;
        val = nullptr;
        right = nullptr;
        delete den;
    }
    else{
        evaluated_value = new UnlimitedRational(v ,den);
        id ="";
        val = nullptr;
        left = nullptr;
        right = nullptr;
        delete den;
    }
}

ExprTreeNode::~ExprTreeNode(){
    delete val;
    delete evaluated_value;
    delete left;
    delete right;
}
