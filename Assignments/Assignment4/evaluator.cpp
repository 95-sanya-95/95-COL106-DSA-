/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "evaluator.h"

Evaluator::Evaluator(){
    symtable = new SymbolTable();
}

Evaluator::~Evaluator(){
    
    while( !expr_trees.empty()){
        delete expr_trees.back();
        expr_trees.pop_back();
    }
    delete symtable;
}

void Evaluator::parse(vector<string> code){

    vector<ExprTreeNode*> stack(0);
    ExprTreeNode* root = new ExprTreeNode();
    root->type=":=";
    ExprTreeNode* left_var = new ExprTreeNode();
    left_var->type = "VAR";
    left_var->id = code[0];
    root->left = left_var;

    ExprTreeNode* root1 = new ExprTreeNode();
    ExprTreeNode* current = root1;

    vector<string> exp(code.begin()+2, code.end());
    for(int i=0; i<exp.size(); i++){

        if(exp[i]=="("){
            ExprTreeNode* Node = new ExprTreeNode();
            stack.push_back(current);
            current->left = Node;
            current = Node;
        }

        else if(exp[i]=="+" || exp[i]=="-"|| exp[i]=="*"||exp[i]=="/"){
            if(exp[i]=="+"){
                current->type = "ADD";
                stack.push_back(current);
                ExprTreeNode* Node = new ExprTreeNode();
                current->right = Node;
                current = Node;
            }
            else if(exp[i]=="-"){
                current->type = "SUB";
                stack.push_back(current);
                ExprTreeNode* Node = new ExprTreeNode();
                current->right = Node;
                current = Node;
            }
            else if(exp[i]=="*"){
                current->type = "MUL";
                stack.push_back(current);
                ExprTreeNode* Node = new ExprTreeNode();
                current->right = Node;
                current = Node;
            }
            else if(exp[i]=="/"){
                current->type = "DIV";
                stack.push_back(current);
                ExprTreeNode* Node = new ExprTreeNode();
                current->right = Node;
                current = Node;
            }
            else{
                current->type = "MOD";
                stack.push_back(current);
                ExprTreeNode* Node = new ExprTreeNode();
                current->right = Node;
                current = Node;
            }
        }
    
        else if(exp[i]==")"){
                if(stack.size()>0){
                    current = stack[stack.size()-1];
                    stack.pop_back();
                }
        }

        else{
            string s = exp[i];
            if(s[0]=='a' || s[0]=='b'||s[0]=='c'||s[0]=='d'||s[0]=='e'||s[0]=='f'||s[0]=='g'||s[0]=='h'||s[0]=='i'||
            s[0]=='j'||s[0]=='k'||s[0]=='l'||s[0]=='m'||s[0]=='n'||s[0]=='o'||s[0]=='p'||s[0]=='q'||s[0]=='r'||s[0]=='s'||
            s[0]=='t'||s[0]=='u'||s[0]=='v'||s[0]=='w'||s[0]=='x'||s[0]=='y'||s[0]=='z' ){

                // ExprTreeNode* curr = new ExprTreeNode();
                // curr->type = "VAR";
                // curr->id = exp[i];
                current->type = "VAR";
                current->id = exp[i];
                if(stack.size()>0){
                current = stack[stack.size()-1];
                stack.pop_back();
                }
            }

            else{
                UnlimitedInt* e = new UnlimitedInt(exp[i]);
                UnlimitedInt* q = new UnlimitedInt(1);
                UnlimitedRational* f = new UnlimitedRational(e,q);
                current->type = "VAL";
                current->val = f;
                current->evaluated_value = f;
                if(stack.size()>0){
                current = stack[stack.size()-1];
                stack.pop_back();
                }
                
            }
        }
    }
    root->right = root1;
    expr_trees.push_back(root);

}

UnlimitedRational * calc(ExprTreeNode* temp,SymbolTable* symtable){
    if(temp->type == "VAR"){
            UnlimitedRational *found=symtable->search(temp->id);
            // cout<<temp->id<<endl;
            // cout<<ur->get_frac_str()<<endl;
            UnlimitedInt* a=found->get_p();
            UnlimitedInt* b=found->get_q();
            // string s1=a->to_string();
            // string s2=b->to_string();
            // UnlimitedInt* num=new UnlimitedInt(s1);
            // UnlimitedInt* den=new UnlimitedInt(s2);
            // UnlimitedRational* finally=new UnlimitedRational(a,b);
            // cout<<finally->get_frac_str()<<endl;
            temp->val=new UnlimitedRational(a,b);
            temp->evaluated_value=new UnlimitedRational(a,b);
            return temp->val;
    
    }
    else if(temp->type == "VAL"){
        return temp->val;
    }
    UnlimitedRational *left =calc(temp->left,symtable);
    // cout<<"rmm"<<endl;
    UnlimitedRational *right =calc(temp->right,symtable);
    if(temp->type=="ADD"){
        temp->evaluated_value = UnlimitedRational::add(left, right);
    }
    if(temp->type=="SUB"){
        temp->evaluated_value = UnlimitedRational::sub(left, right);
    }
    if(temp->type=="MUL"){
        temp->evaluated_value = UnlimitedRational::mul(left, right);
    }
    if(temp->type=="DIV"){
        temp->evaluated_value = UnlimitedRational::div(left, right);
    }
    if(temp->type=="MOD"){
        UnlimitedInt* l = new UnlimitedInt(left->get_p_str());
        UnlimitedInt* r = new UnlimitedInt(right->get_p_str());
        UnlimitedInt* num = UnlimitedInt::mod(l, r);
        UnlimitedInt* den = new UnlimitedInt(1);
        temp->evaluated_value = new UnlimitedRational(num ,den);
    }
    return temp->evaluated_value;;
}

void Evaluator:: eval(){
    if(expr_trees.empty()){
        return;
    }
    ExprTreeNode* root=expr_trees.back();
    UnlimitedRational *right_val = calc(root->right, symtable);
    ExprTreeNode* var = root->left;
    UnlimitedRational* sanya = new UnlimitedRational(right_val->get_p(), right_val->get_q());
    var->evaluated_value = sanya;
    var->val = sanya;
    string name = var->id;
    symtable->insert(name, sanya);
}


// UnlimitedRational *evaltree(ExprTreeNode *root, SymbolTable *symtable)
// {
//     if (root->type == "VAL")
//     {
//         return root->val;
//     }
//     else if (root->type == "VAR")
//     {
//         UnlimitedRational *x = symtable->search(root->id);
//         root->val = new UnlimitedRational(x->get_p(), x->get_q());
//         root->evaluated_value = new UnlimitedRational(x->get_p(), x->get_q());
//         return root->val;
//     }
//     else
//     {
//         UnlimitedRational *a = evaltree(root->left, symtable);
//         UnlimitedRational *b = evaltree(root->right, symtable);
//         if (root->type == "ADD")
//         {
//             root->evaluated_value = UnlimitedRational::add(a, b);
//         }
//         else if (root->type == "SUB")
//         {
//             root->evaluated_value = UnlimitedRational::sub(a, b);
//         }
//         else if (root->type == "MUL")
//         {
//             root->evaluated_value = UnlimitedRational::mul(a, b);
//         }
//         else if (root->type == "DIV")
//         {
//             root->evaluated_value = UnlimitedRational::div(a, b);
//         }
//         return root->evaluated_value;
//     }
// }
// void Evaluator::eval()
// {
//     ExprTreeNode *to_evaluate = expr_trees.back();
//     UnlimitedRational *x = evaltree(to_evaluate->right, symtable);
//     UnlimitedRational *temp = new UnlimitedRational(x->get_p(), x->get_q());
//     to_evaluate->left->evaluated_value = temp;
//     ExprTreeNode *var = to_evaluate->left;
//     symtable->insert(var->id, var->evaluated_value);
// }

// void evaluateAndPrint(ExprTreeNode* node) {
//     if (node == nullptr) {
//         return;
//     }
//     evaluateAndPrint(node->left);
//     evaluateAndPrint(node->right);
//     if (node->evaluated_value != nullptr) {
//         cout << "Node ID: " << node->id << ", Evaluated Value: " << node->evaluated_value->get_frac_str() << endl;
//     } else {
//         cout << "Node ID: " << node->id << " has no evaluated value." << endl;
//     }
// }

// int main() {
//     Evaluator evaluator;
//     cout<<"FOR FIRST PARSE TREE: "<<endl;
//     cout<<endl;
//     vector<string> code;
//     code.push_back("a");
//     code.push_back(":=");
//     code.push_back("234");
//     evaluator.parse(code);
//     // cout<< "HELL" <<endl;
//     evaluator.eval();
//     evaluateAndPrint(evaluator.expr_trees[0]);
//     cout<<evaluator.symtable->get_root()->val->get_frac_str()<<endl;
//     cout<<endl;
//     cout<<"FOR SECOND PARSE TREE: "<<endl;
//     cout<<endl;

//     vector<string> code2;
//     code2.push_back("b");
//     code2.push_back(":=");
//     code2.push_back("(");
//     code2.push_back("(");
//     code2.push_back("a");
//     code2.push_back("+");
//     code2.push_back("43");
//     code2.push_back(")");
//     code2.push_back("*");
//     code2.push_back("2");
//     code2.push_back(")");

//     evaluator.parse(code2);
//     // cout<< "HELL" <<endl;
//     evaluator.eval();
//     evaluateAndPrint(evaluator.expr_trees[1]);

//     cout<<endl;
//     cout<<"FOR THIRD PARSE TREE : "<<endl;
//     cout<<endl;
//     vector<string> code3;
//     code3.push_back("c");
//     code3.push_back(":=");
//     code3.push_back("(");
//     code3.push_back("(");
//     code3.push_back("(");
//     code3.push_back("a");
//     code3.push_back("+");
//     code3.push_back("b");
//     code3.push_back(")");
//     code3.push_back("*");
//     code3.push_back("-32627");
//     code3.push_back(")");
//     code3.push_back("-");
//     code3.push_back("703938");
//     code3.push_back(")");
//     evaluator.parse(code3);
//     cout<<"YUPP3"<<endl;
//     evaluator.eval();
//     evaluateAndPrint(evaluator.expr_trees[2]);

//     cout<<endl;
//     cout<<"FOR FOURTH PARSE TREE : "<<endl;
//     cout<<endl;

//     vector<string> code4;
//     code4.push_back("d");
//     code4.push_back(":=");
//     code4.push_back("(");
//     code4.push_back("(");
//     code4.push_back("a");
//     code4.push_back("/");
//     code4.push_back("62827373");
//     code4.push_back(")");
//     code4.push_back("*");
//     code4.push_back("(");
//     code4.push_back("b");
//     code4.push_back("/");
//     code4.push_back("c");
//     code4.push_back(")");
//     code4.push_back(")");
//     evaluator.parse(code4);
//     evaluator.eval();
//     evaluateAndPrint(evaluator.expr_trees[3]);

//     cout<<endl;
//     cout<<"FOR FIFTH PARSE TREE : "<<endl;
//     cout<<endl;

//     vector<string> code5;
//     code5.push_back("e");
//     code5.push_back(":=");
//     code5.push_back("d");
//     evaluator.parse(code5);
//     evaluator.eval();
//     evaluateAndPrint(evaluator.expr_trees[4]);

//     cout<<evaluator.symtable->search("e")->get_frac_str()<<endl;
//     cout<<endl;
//     cout<<"FOR SIXTH PARSE TREE : "<<endl;
//     cout<<endl;

//     vector<string> code6;
//     code6.push_back("f");
//     code6.push_back(":=");
//     code6.push_back("(");
//     code6.push_back("e");
//     code6.push_back("/");
//     code6.push_back("-58373822900038939928302283293");
//     code6.push_back(")");
//     evaluator.parse(code6);
//     cout<<"hmm"<<endl;
//     evaluator.eval();
//     evaluateAndPrint(evaluator.expr_trees[5]);

    
//     return 0;
// }