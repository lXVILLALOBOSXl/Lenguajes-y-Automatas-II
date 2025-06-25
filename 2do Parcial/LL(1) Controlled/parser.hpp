#ifndef parser_hpp
#define parser_hpp

#include <stdio.h>
#include "scanner.hpp"
#include <map>
#include <vector>
#include <stack>

class parser {

scanner s;

scanner::token t;

bool exp();
bool _exp();
bool term();
bool _term();
bool fact();

// typedef enum {n = 100, o } terminals;
typedef enum {EXP = 200, _EXP, TERM, _TERM, FACT } generators;
static  std::map<generators, std::map<scanner::token, std::vector< generators > > > table;
static const stack<scanner::token> stack;



bool match(scanner::token);
    

public:
    
    parser(string fname): s(fname) {}

    bool parse();
};

#endif /* parser_hpp */