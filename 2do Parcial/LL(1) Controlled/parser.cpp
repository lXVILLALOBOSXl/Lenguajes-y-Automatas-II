#include "parser.hpp"

// Define static const map<generators, map<scanner::token, int>> table;
std::map<parser::generators, std::map<scanner::token, std::vector< parser::generators > > > parser::table = {
    {parser::EXP, {
        {scanner::sum, {scanner::err}},
        {scanner::mult, {scanner::err}},
        {scanner::lpar, {parser::TERM, parser::_EXP}},
        {scanner::rpar, {scanner::err}},
        {scanner::dash, {parser::TERM, parser::_EXP}},
        {scanner::_num, {parser::TERM, parser::_EXP}},
        {scanner::_eof, {scanner::err}}
    }},
    {parser::_EXP, {
        {scanner::sum, {scanner::sum, parser::TERM, parser::_EXP}},
        {scanner::mult, {scanner::err}},
        {scanner::lpar, {scanner::err}},
        {scanner::rpar, {}},
        {scanner::dash, {scanner::err}},
        {scanner::_num, {scanner::err}},
        {scanner::_eof, {}}
    }},
    {parser::TERM, {
        {scanner::sum, {scanner::err}},
        {scanner::mult, {scanner::err}},
        {scanner::lpar, {parser::FACT, parser::_TERM}},
        {scanner::rpar, {scanner::err}},
        {scanner::dash, {parser::FACT, parser::_TERM}},
        {scanner::_num, {parser::FACT, parser::_TERM}},
        {scanner::_eof, {scanner::err}}
    }},
    {parser::_TERM, {
        {scanner::sum, {}},
        {scanner::mult, {scanner::mult, parser::FACT, parser::_TERM}},
        {scanner::lpar, {scanner::err}},
        {scanner::rpar, {}},
        {scanner::dash, {scanner::err}},
        {scanner::_num, {scanner::err}},
        {scanner::_eof, {}}
    }},
    {parser::FACT, {
        {scanner::sum, {scanner::err}},
        {scanner::mult, {scanner::err}},
        {scanner::lpar, {scanner::lpar, parser::EXP, scanner::rpar}},
        {scanner::rpar, {scanner::err}},
        {scanner::dash, {scanner::dash, parser::FACT}},
        {scanner::_num, {scanner::_num}},
        {scanner::_eof, {scanner::err}}
    }}
};

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
    return exp();
}