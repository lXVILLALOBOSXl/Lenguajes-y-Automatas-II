#include "scanner.hpp"

const int scanner::udef = -1;

scanner::token scanner::id() {

    int actual = 0;
    int prior = udef;

    lexeme = "";

    while (actual != udef) {
        
        char c = read();
        prior = actual;

        switch (actual) {
            case 0:
                if (isalpha(c)) {
                    actual = 2;
                    lexeme += c;
                } else if (c == '_') {
                    actual = 1;
                    lexeme += c;
                } else {
                    actual = udef;
                }
                break;
            case 1:
                if (isdigit(c) or c == '_') {
                    actual = 1;
                    lexeme += c;
                }else if (isalpha(c)) {
                    actual = 2;
                    lexeme += c;
                } else {
                    actual = udef;
                }
                break;
            case 2:
                if (isalpha(c) or isdigit(c) or c == '_') {
                    actual = 2;
                    lexeme += c;
                } else {
                    actual = udef;
                }
                break;
        }


    }


    if (lexeme == "or"){
        fallback();
        success();
        return _or;
    } else if (lexeme == "and"){
        fallback();
        success();
        return _and;
    } else if (lexeme == "not"){
        fallback();
        success();
        return _not;
    } else if (lexeme == "false"){
        fallback();
        success();
        return _false;
    } else if (lexeme == "true"){
        fallback();
        success();
        return _true;
    } 

    if (prior == 2) { // Identif
        fallback();
        success();
        return _identif;
    } 

    failure();
    return err;
}   

scanner::token scanner::ws() {

    int actual = 0;
    int prior = udef;

    while (actual != udef) {

        prior = actual;
        char c = read();

        switch (actual) {

            case 0:
                if (c == '\t'){
                    actual = 1;
                } else if (c == '\n'){
                    actual = 2;
                    line++;
                } else if (c == ' '){
                    actual = 3;
                } else {
                    actual = udef;
                }
                break;
            case 1:
                actual = udef;
                break;
            case 2:
                actual = udef;
                break;
            case 3:
                actual = udef;
                break;

        }
    }

    if (prior == 1) { // Whitespace
        fallback();
        success();
        return tab;
    }else if (prior == 2) { // Whitespace
        fallback();
        success();
        return _enter;
    }else if (prior == 3) { // Whitespace
        fallback();
        success();
        return whitespace;
    }

    failure();
    return err;

    
}

// void scanner::wsp() {
//     while (isspace(read()));

//     fallback();
//     success();
// }

bool scanner::eof() {
    return file.eof() or file.peek() == EOF;
}

bool scanner::unique(char c) {
    lexeme = "";
   if (read() == c) {
        lexeme += c;
        success();
        return true;
    } 
    failure();
    return false;
}

scanner::token scanner::next() {

    token t = ws();
    if (t == whitespace) return whitespace;
    
    t = id();
    if (t == _identif) return _identif;
    if (t == _true) return _true;
    if (t == _false) return _false;
    if (t == _not) return _not;
    if (t == _or) return _or;
    if (t == _and) return _and;
    if (unique('?')) return _question_mark;
    if (unique(':')) return _dots;
    if (unique('(')) return lpar;
    if (unique(')')) return rpar;


    if (eof()) return _eof;
    
    return err;


}