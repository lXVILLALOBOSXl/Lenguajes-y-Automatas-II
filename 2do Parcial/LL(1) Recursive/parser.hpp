#ifndef parser_hpp
#define parser_hpp

#include <stdio.h>
#include "scanner.hpp"

class parser {

scanner s;

scanner::token t;

bool exp();
bool _exp();
bool term();
bool _term();
bool fact();

bool match(scanner::token);
    

public:
    
    parser(string fname): s(fname) {}

    bool parse();
};

#endif /* parser_hpp */