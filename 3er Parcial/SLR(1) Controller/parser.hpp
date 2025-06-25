#ifndef PARSER_HPP
#define PARSER_HPP

#include <string>
#include <stack>
#include <map>
#include "scanner.hpp"

using namespace std;

class parser {
public:
    parser(const string& filename);
    bool parse();

private:
    scanner s;
    scanner::token current_token;
    string current_lexeme;

    stack<int> state_stack;
    stack<string> symbol_stack;

    map<pair<int, string>, string> action_table;
    map<pair<int, string>, int> goto_table;

    void init_tables();
    string token_to_string(scanner::token t);
};

#endif // PARSER_HPP