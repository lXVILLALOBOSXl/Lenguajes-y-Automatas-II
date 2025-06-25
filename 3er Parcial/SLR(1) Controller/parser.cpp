#include "parser.hpp"
#include <iostream>

parser::parser(const string& filename) : s(filename) {
    init_tables();
}

void parser::init_tables() {
    //Tabla de acciones
    action_table[std::make_pair(1, "not")] = "S6";
    action_table[std::make_pair(1, "(")] = "S7";
    action_table[std::make_pair(1, "false")] = "S8";
    action_table[std::make_pair(1, "true")] = "S9";
    action_table[std::make_pair(1, "id")] = "S10";
    action_table[std::make_pair(2, "$")] = "A";
    action_table[std::make_pair(3, "?")] = "S11";
    action_table[std::make_pair(3, ":")] = "R(quest, 1)";
    action_table[std::make_pair(3, "or")] = "S12";
    action_table[std::make_pair(3, ")")] = "R(quest, 1)";
    action_table[std::make_pair(3, "$")] = "R(quest, 1)";
    action_table[std::make_pair(4, "?")] = "R(prop, 1)";
    action_table[std::make_pair(4, ":")] = "R(prop, 1)";
    action_table[std::make_pair(4, "or")] = "R(prop, 1)";
    action_table[std::make_pair(4, "and")] = "S13";
    action_table[std::make_pair(4, ")")] = "R(prop, 1)";
    action_table[std::make_pair(4, "$")] = "R(prop, 1)";
    action_table[std::make_pair(5, "?")] = "R(clause, 1)";
    action_table[std::make_pair(5, ":")] = "R(clause, 1)";
    action_table[std::make_pair(5, "or")] = "R(clause, 1)";
    action_table[std::make_pair(5, "and")] = "R(clause, 1)";
    action_table[std::make_pair(5, ")")] = "R(clause, 1)";
    action_table[std::make_pair(5, "$")] = "R(clause, 1)";
    action_table[std::make_pair(6, "not")] = "S6";
    action_table[std::make_pair(6, "(")] = "S7";
    action_table[std::make_pair(6, "false")] = "S8";
    action_table[std::make_pair(6, "true")] = "S9";
    action_table[std::make_pair(6, "id")] = "S10";
    action_table[std::make_pair(7, "not")] = "S6";
    action_table[std::make_pair(7, "(")] = "S7";
    action_table[std::make_pair(7, "false")] = "S8";
    action_table[std::make_pair(7, "true")] = "S9";
    action_table[std::make_pair(7, "id")] = "S10";
    action_table[std::make_pair(8, "?")] = "R(atom, 1)";
    action_table[std::make_pair(8, ":")] = "R(atom, 1)";
    action_table[std::make_pair(8, "or")] = "R(atom, 1)";
    action_table[std::make_pair(8, "and")] = "R(atom, 1)";
    action_table[std::make_pair(8, ")")] = "R(atom, 1)";
    action_table[std::make_pair(8, "$")] = "R(atom, 1)";
    action_table[std::make_pair(9, "?")] = "R(atom, 1)";
    action_table[std::make_pair(9, ":")] = "R(atom, 1)";
    action_table[std::make_pair(9, "or")] = "R(atom, 1)";
    action_table[std::make_pair(9, "and")] = "R(atom, 1)";
    action_table[std::make_pair(9, ")")] = "R(atom, 1)";
    action_table[std::make_pair(9, "$")] = "R(atom, 1)";
    action_table[std::make_pair(10, "?")] = "R(atom, 1)";
    action_table[std::make_pair(10, ":")] = "R(atom, 1)";
    action_table[std::make_pair(10, "or")] = "R(atom, 1)";
    action_table[std::make_pair(10, "and")] = "R(atom, 1)";
    action_table[std::make_pair(10, ")")] = "R(atom, 1)";
    action_table[std::make_pair(10, "$")] = "R(atom, 1)";
    action_table[std::make_pair(11, "not")] = "S6";
    action_table[std::make_pair(11, "(")] = "S7";
    action_table[std::make_pair(11, "false")] = "S8";
    action_table[std::make_pair(11, "true")] = "S9";
    action_table[std::make_pair(11, "id")] = "S10";
    action_table[std::make_pair(12, "not")] = "S6";
    action_table[std::make_pair(12, "(")] = "S7";
    action_table[std::make_pair(12, "false")] = "S8";
    action_table[std::make_pair(12, "true")] = "S9";
    action_table[std::make_pair(12, "id")] = "S10";
    action_table[std::make_pair(13, "not")] = "S6";
    action_table[std::make_pair(13, "(")] = "S7";
    action_table[std::make_pair(13, "false")] = "S8";
    action_table[std::make_pair(13, "true")] = "S9";
    action_table[std::make_pair(13, "id")] = "S10";
    action_table[std::make_pair(14, "?")] = "R(atom, 2)";
    action_table[std::make_pair(14, ":")] = "R(atom, 2)";
    action_table[std::make_pair(14, "or")] = "R(atom, 2)";
    action_table[std::make_pair(14, "and")] = "R(atom, 2)";
    action_table[std::make_pair(14, ")")] = "R(atom, 2)";
    action_table[std::make_pair(14, "$")] = "R(atom, 2)";
    action_table[std::make_pair(15, ")")] = "S19";
    action_table[std::make_pair(16, ":")] = "S20";
    action_table[std::make_pair(17, "?")] = "R(prop, 3)";
    action_table[std::make_pair(17, ":")] = "R(prop, 3)";
    action_table[std::make_pair(17, "or")] = "R(prop, 3)";
    action_table[std::make_pair(17, "and")] = "S13";
    action_table[std::make_pair(17, ")")] = "R(prop, 3)";
    action_table[std::make_pair(17, "$")] = "R(prop, 3)";
    action_table[std::make_pair(18, "?")] = "R(clause, 3)";
    action_table[std::make_pair(18, ":")] = "R(clause, 3)";
    action_table[std::make_pair(18, "or")] = "R(clause, 3)";
    action_table[std::make_pair(18, "and")] = "R(clause, 3)";
    action_table[std::make_pair(18, ")")] = "R(clause, 3)";
    action_table[std::make_pair(18, "$")] = "R(clause, 3)";
    action_table[std::make_pair(19, "?")] = "R(atom, 3)";
    action_table[std::make_pair(19, ":")] = "R(atom, 3)";
    action_table[std::make_pair(19, "or")] = "R(atom, 3)";
    action_table[std::make_pair(19, "and")] = "R(atom, 3)";
    action_table[std::make_pair(19, ")")] = "R(atom, 3)";
    action_table[std::make_pair(19, "$")] = "R(atom, 3)";
    action_table[std::make_pair(20, "not")] = "S6";
    action_table[std::make_pair(20, "(")] = "S7";
    action_table[std::make_pair(20, "false")] = "S8";
    action_table[std::make_pair(20, "true")] = "S9";
    action_table[std::make_pair(20, "id")] = "S10";
    action_table[std::make_pair(21, ":")] = "R(quest, 5)";
    action_table[std::make_pair(21, ")")] = "R(quest, 5)";
    action_table[std::make_pair(21, "$")] = "R(quest, 5)";


    //Tabla de transiciones GOTO
    goto_table[std::make_pair(1, "quest")] = 2;
    goto_table[std::make_pair(1, "prop")] = 3;
    goto_table[std::make_pair(1, "clause")] = 4;
    goto_table[std::make_pair(1, "atom")] = 5;
    goto_table[std::make_pair(6, "atom")] = 14;
    goto_table[std::make_pair(7, "quest")] = 15;
    goto_table[std::make_pair(7, "prop")] = 3;
    goto_table[std::make_pair(7, "clause")] = 4;
    goto_table[std::make_pair(7, "atom")] = 5;
    goto_table[std::make_pair(11, "quest")] = 16;
    goto_table[std::make_pair(11, "prop")] = 3;
    goto_table[std::make_pair(11, "clause")] = 4;
    goto_table[std::make_pair(11, "atom")] = 5;
    goto_table[std::make_pair(12, "clause")] = 17;
    goto_table[std::make_pair(12, "atom")] = 5;
    goto_table[std::make_pair(13, "atom")] = 18;
    goto_table[std::make_pair(20, "quest")] = 21;
    goto_table[std::make_pair(20, "prop")] = 3;
    goto_table[std::make_pair(20, "clause")] = 4;
    goto_table[std::make_pair(20, "atom")] = 5;
}

string parser::token_to_string(scanner::token t) {
    switch (t) {
        case scanner::_identif: return "id";
        case scanner::_question_mark: return "?";
        case scanner::_or: return "or";
        case scanner::_dots: return ":";
        case scanner::_and: return "and";
        case scanner::_not: return "not";
        case scanner::lpar: return "(";
        case scanner::rpar: return ")";
        case scanner::_false: return "false";
        case scanner::_true: return "true";
        case scanner::_eof: return "$";
        default: return "UNKNOWN";
    }
}

bool parser::parse() {
    state_stack = stack<int>();
    symbol_stack = stack<string>();

    state_stack.push(1); // estado inicial

    current_token = s.next();
    current_lexeme = s.get_lexeme();

    while (true) {
        int current_state = state_stack.top();
        string a = token_to_string(current_token);

        map<pair<int, string>, string>::iterator action_it = action_table.find(std::make_pair(current_state, a));
        if (action_it == action_table.end()) {
            return false; // error sintáctico
        }

        string action = action_it->second;

        if (action == "A") {
            return true; // aceptar
        } else if (action[0] == 'S') {
            int next_state = stoi(action.substr(1));
            state_stack.push(next_state);
            symbol_stack.push(a);
            current_token = s.next();
            current_lexeme = s.get_lexeme();
        } else if (action[0] == 'R') {
            string prod = action.substr(2, action.length() - 3);
            size_t comma = prod.find(',');
            string head = prod.substr(0, comma);
            int body_len = stoi(prod.substr(comma + 1));

            for (int i = 0; i < body_len; ++i) {
                if (!symbol_stack.empty()) symbol_stack.pop();
                if (!state_stack.empty()) state_stack.pop();
            }

            int top_state = state_stack.top();
            state_stack.push(goto_table[std::make_pair(top_state, head)]);
            symbol_stack.push(head);
        } else {
            return false;
        }
    }
}
