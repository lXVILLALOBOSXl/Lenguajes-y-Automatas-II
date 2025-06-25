#include "parser.hpp"

bool parser::match(scanner::token x){
    if (t == x){
        t = s.next();
        return true;
    }
    return false;

    
}

bool parser::exp(){
    if (t == scanner::lpar or t == scanner::dash or t == scanner::_num) return term() and _exp();

    return false;
}

bool parser::_exp(){
    if (t == scanner::sum) return match(scanner::sum) and term() and _exp();
    if (t == scanner::rpar or t == scanner::_eof) return true;
    return false;
}

bool parser::term(){
    if (t == scanner::lpar or t == scanner::dash or t == scanner::_num) return fact() and _term();
    return false;

}


bool parser::_term(){
    if (t == scanner::mult) return match(scanner::mult) and fact() and _term();
    if (t == scanner::rpar or t == scanner::sum or t == scanner::_eof) return true;
    return false;
}

bool parser::fact(){
    if (t == scanner::lpar) return match(scanner::lpar) and exp() and match(scanner::rpar);
    if (t == scanner::dash) return match(scanner::dash) and fact();
    if (t == scanner::_num) return match(scanner::_num);
    return false;
}

bool parser::parse(){
    t = s.next();
    return exp() and match(scanner::_eof);
}