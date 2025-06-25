#include <iostream>
#include "nodes.h"

extern FILE *yyin; // File for Flex
extern int yyparse(); // Parser

extern node *tree; // Abstract syntax tree

void level(int i){
    while (i--)
    {
        printf("  ");
    }
}

void print(node *p, int i){

    if (p == NULL) return;

    switch (p->type){
        case sum:
            level(i);
            printf("+\n");
            print(p->left, i + 1);
            print(p->right, i + 1);
            break;

        case diff:
            level(i);
            printf("-\n");
            print(p->left, i + 1);
            print(p->right, i + 1);
            break;

        case mult:
            level(i);
            printf("*\n");
            print(p->left, i + 1);
            print(p->right, i + 1);
            break;

        case _div:
            level(i);
            printf("/\n");
            print(p->left, i + 1);
            print(p->right, i + 1);
            break;

        case neg:
            level(i);
            printf("neg\n");
            print(p->left, i + 1);
            break;

        case numeric:
            level(i);
            printf("%f\n", p->value);
            break;
    }
    
}

double solve(node *p){
    // if (p == NULL) return;

    switch (p->type){
        case sum: return solve(p->left) + solve(p->right);
        case diff: return solve(p->left) - solve(p->right);    
        case mult: return solve(p->left) * solve(p->right);
        case _div: return solve(p->left) / solve(p->right);
        case neg: return -solve(p->left);
        case numeric: return p->value;
    }
}

int main(int argc, const char * argv[]) {
    
    yyin = fopen("test.txt", "r");

    if (yyparse() == 0){
        print(tree, 0);
        printf("\nResultado: %f\n", solve(tree));
        printf("Ok\n");
    }
    else printf("Error\n");

    fclose(yyin);
    
    
    return 0;
}