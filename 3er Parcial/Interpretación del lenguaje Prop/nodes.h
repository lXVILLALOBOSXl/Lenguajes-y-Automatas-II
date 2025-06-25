//
// nodes.h
// abstract
//
//
//

#ifndef nodes_h
#define nodes_h

#include <string>

using namespace std;

typedef enum {  t_and, t_or, t_not, t_implies, t_eq, t_neq, t_select, t_id, t_const } tnode;

typedef struct snode {
    tnode type;
    bool value; 
    string id; 
    snode* left;
    snode* middle;  
    snode* right;
} node;

extern node* new_const(bool value);
extern node* new_id(const string&);
extern node* new_unary(tnode, node*);
extern node* new_binary(tnode, node*, node*);
extern node* new_ternary(tnode, node*, node*, node*);



#endif /* nodes_h */