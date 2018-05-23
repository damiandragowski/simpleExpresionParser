#include <iostream>
#include <string>
using namespace std;

struct TreeNode {
    TreeNode *left, *right;
    double val;
    string op;
};

std::string::size_type pointer;

string getToken(string & exp, bool consume=true) {
    if ( pointer < exp.length() ) {
        if ( exp[pointer] == 'x' ||
             exp[pointer] == '+' || exp[pointer] == '-'
        ||   exp[pointer] == '*' || exp[pointer] == '/'
        ||   exp[pointer] == '(' || exp[pointer] == ')' ) {
            return exp.substr((consume)?pointer++:pointer,1);
        } else {
            try {
                std::string::size_type t = pointer;
                double val = std::stod(exp.substr(pointer), &t);
                if ( consume )
                    pointer += t;
                return to_string(val);
            } catch ( invalid_argument & e ) {

            }
        }
    } else {
        return "";
    }   
}


/* Grammar E -> F{BF}
           F -> P{CP}
           B -> {"+" | "-"} 
           C -> {"*" | "/"}           
           P -> "(" + E + ")" | val */
TreeNode * E(string & exp);
TreeNode * F(string & exp);
TreeNode * B(string & exp);
TreeNode * C(string & exp);


auto P = [&](string &exp) -> TreeNode* {
    string token = getToken(exp, true);
    TreeNode * t = NULL;
    if ( token == "(" ) { // "(" + E + ")"
        t = E(exp);
        token = getToken(exp, true);
        if ( token != ")") {
            cout << "ERROR PARSING" << endl;
            t = NULL;
        }
    } else if (token == "x") { // val
        t = new TreeNode;
        t->right = t->left = NULL;
        t->op = "VAR";
        t->val = 0;
    } else { // val
        t = new TreeNode;
        t->right = t->left = NULL;
        t->op = "VALUE";
        t->val = std::stod(token);
    }
    return t;
};



TreeNode * B(string & exp) { //  B -> {"+" | "-"}
    TreeNode * t = NULL;
    string token = getToken(exp, false);
    if ( token == "+" ) {
        token = getToken(exp, true);
        t = new TreeNode;
        t->right = t->left = NULL;
        t->op = "+";
        t->val = 0;        
    } else if ( token == "-" ) {
        token = getToken(exp, true);
        t = new TreeNode;
        t->right = t->left = NULL;
        t->op = "-";
        t->val = 0;        
    }
    
    return t;
}

TreeNode * C(string & exp) { // C -> {"*" | "/"}    
    TreeNode * t = NULL;
    string token = getToken(exp, false);
    if ( token == "*" ) {
        token = getToken(exp, true);
        t = new TreeNode;
        t->right = t->left = NULL;
        t->op = "*";
        t->val = 0;        
    } else if ( token == "/" ) {
        token = getToken(exp, true);
        t = new TreeNode;
        t->right = t->left = NULL;
        t->op = "/";
        t->val = 0;        
    }
    return t;
}

TreeNode * E(string & exp) { // E -> F{BF}
    TreeNode * t = NULL;
    string token;
    t = F(exp);
    while ( (token = getToken(exp, false))!= "" && (token=="+"|| token=="-")) {
        TreeNode * t1 = B(exp);
        if ( t1 ) {
            TreeNode * t2;
            t2 = F(exp);
            t1->left = t;
            t1->right = t2;
            t = t1;
        }
    }
    return t;
}

TreeNode * F(string & exp) { // F -> P{CP}
    TreeNode * t = NULL;
    string token;
    t = P(exp);
    while ( (token = getToken(exp, false))!= "" && (token=="*"|| token=="/")) {
        TreeNode * t1 = C(exp);
        if ( t1 ) {
            TreeNode * t2;
            t2 = P(exp);
            t1->left = t;
            t1->right = t2;
            t = t1;
        }
    }
    return t;
}

double computeTree(TreeNode * root, double x) {
    if ( root == NULL ) 
        return 0;
    if ( root->op == "VALUE" ) {
        return root->val;
    } else if ( root->op == "+") {
        return computeTree(root->left, x) + computeTree(root->right, x);
    } else if ( root->op == "-") {
        return computeTree(root->left, x) - computeTree(root->right, x);
    } else if ( root->op == "*") {
        return computeTree(root->left, x) * computeTree(root->right, x);
    } else if ( root->op == "/") {
        return computeTree(root->left, x) / computeTree(root->right, x);
    } else if ( root->op == "VAR") {
        return x;        
    } else {
        return 0;
    }

}

int main() {
    string exp = "x*x*x";
    pointer = 0;

    string token;

    TreeNode * t = E(exp);

    cout << computeTree(t, 10) << endl;

    return 0;
}   