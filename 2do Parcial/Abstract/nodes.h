//
// nodes.h
// abstract
//
//
//

#ifndef nodes_h
#define nodes_h


typedef enum { mult, sum, diff, neg, _div, numeric} tnode;

typedef struct snode{

    tnode type;
    float value;

    snode *left;
    snode *right;
    
} node;

extern node *newnode(float);
extern node *newnode(node *);
extern node *newnode(tnode, node *, node *);


#endif /* nodes_h */