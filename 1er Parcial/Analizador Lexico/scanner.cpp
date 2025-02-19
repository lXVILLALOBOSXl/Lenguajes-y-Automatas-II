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
                    actual = 1;
                    lexeme += c; 
                } else if (c == '_') {
                    actual = 2;
                    lexeme += c; 
                } else {
                    actual = udef;
                }
                break;
            case 1:
                if (isalnum(c) or c == '_') {
                    actual = 1;
                    lexeme += c; 
                }else {
                    actual = udef;
                }
                break;
            case 2:
                if (isalpha(c)) {
                    actual = 1;
                    lexeme += c; 
                } else if (isdigit(c) or c == '_') {
                    actual = 2;
                    lexeme += c; 
                } else {
                    actual = udef;
                }
                break;
        }


    }


    if (find(reserved_words.begin(), reserved_words.end(), lexeme) != reserved_words.end()) {
        prior = 3;
    }  

    if (prior == 1) { // Identif
        fallback();
        success();
        return identif;
    } else if (prior == 3) { // Reserved
        fallback();
        success();
        return reserved;
    }

    failure();
    return err;
}   

scanner::token scanner::num() {

    int actual = 0;
    int prior = udef;

    lexeme = "";

    while (actual != udef) {

        prior = actual;
        char c = read();

        switch (actual) {

            case 0:
                if (c == '0') {
                    actual = 1;
                    lexeme += c;
                } else if (c == '1' or c == '2' or c == '3' or c == '4' or c == '5' or c == '6' or c == '7' or c == '8' or c == '9') {
                    actual = 2;
                    lexeme += c;
                } else {
                    actual = udef;
                }
                break;
            case 1:
                if (c == 'x' or c == 'X') {
                    actual = 5;
                    lexeme += c;
                } else if (c == '0' or c == '1' or c == '2' or c == '3' or c == '4' or c == '5' or c == '6' or c == '7' ) {
                    actual = 3;
                    lexeme += c;
                }  else if (c == '.') {
                    actual = 6;
                    lexeme += c;
                } else if (c == '8' or c == '9' or isalpha(c) or c == '_') {
                    actual = 4;
                    lexeme += c;
                } else {
                    actual = udef;
                }
                break;
            case 2:
                if (isdigit(c)) {
                    actual = 2;
                    lexeme += c;
                } else if (c == '.') {
                    actual = 6;
                    lexeme += c;
                } else if (isalpha(c) or c == '_') {
                    actual = 7;
                    lexeme += c;
                } else {
                    actual = udef;
                }
                break;
            case 3:
                if (c == '0' or c == '1' or c == '2' or c == '3' or c == '4' or c == '5' or c == '6' or c == '7' ) {
                    actual = 3;
                    lexeme += c;
                } else if (c == '8' or c == '9' or isalpha(c) or c == '_') {
                    actual = 4;
                    lexeme += c;
                } else {
                    actual = udef;
                }
                break;
            case 4:
                actual = udef;
                break;
            case 5:
                if (isdigit(c) or (c >= 'A' and c <= 'F') or (c >= 'a' and c <= 'f')) {
                    actual = 8;
                    lexeme += c;
                } else {
                    actual = udef;
                }
                break;
            case 6:
                if (isdigit(c)) {
                    actual = 9;
                    lexeme += c;
                } else {
                    actual = udef;
                }
                break;
            case 7:
                actual = udef;
                break;
            case 8:
                if (isdigit(c) or (c >= 'A' and c <= 'F') or (c >= 'a' and c <= 'f')) {
                    actual = 11;
                    lexeme += c;
                } else {
                    actual = udef;
                }
                break;
            case 9:
                if (isdigit(c)) {
                    actual = 9;
                    lexeme += c;
                } else if (isalpha(c) or c == '_') {
                    actual = 10;
                    lexeme += c;
                } else {
                    actual = udef;
                }
                break;
            case 10:
                actual = udef;
                break;
            case 11:
                if (isdigit(c) or (c >= 'A' and c <= 'F') or (c >= 'a' and c <= 'f')) {
                    actual = 8;
                    lexeme += c;
                } else if (c >= 'G' and c <= 'Z' or c >= 'g' and c <= 'z') {
                    actual = 12;
                    lexeme += c;
                } else {
                    actual = udef;
                }
                break;
            case 12:
                actual = udef;
                break;
        } 
    }
    if (prior == 1 or prior == 3){ // Octal
        fallback();
        success();
        return oct;
    }else if (prior == 9){ // Real
        fallback();
        success();
        return real;
    }else if (prior == 11){ // Hex
        fallback();
        success();
        return hex;
    }else if (prior == 2){ // Integer
        fallback();
        success();
        return integer;
    }
    
    failure();
    return err;
    
}

scanner::token scanner::delim() {

    int actual = 0;
    int prior = udef;

    while (actual != udef) {

        prior = actual;
        char c = read();

        switch (actual) {

            case 0:
                if (c == '(' or c == ')' or c == '[' or c == ']' or c == '{' or c == '}') {
                    actual = 1;
                } else {
                    actual = udef;
                }
                break;
            case 1:
                actual = udef;
                break;

        }
    }

    if (prior == 1) { // Delimiter
        fallback();
        success();
        return delimiter;
    }

    failure();
    return err;
}

scanner::token scanner::punct() {

    int actual = 0;
    int prior = udef;

    while (actual != udef) {

        prior = actual;
        char c = read();

        switch (actual) {

            case 0:
                if (c == '.' or c == ',' or c == ';') {
                    actual = 1;
                } else {
                    actual = udef;
                }
                break;
            case 1:
                actual = udef;
                break;

        }
    }

    if (prior == 1) { // Punctuation
        fallback();
        success();
        return punctuation;
    }

    failure();
    return err;
}

scanner::token scanner::op() {

    int actual = 0;
    int prior = udef;

    while (actual != udef) {

        prior = actual;
        char c = read();

        switch (actual) {

            case 0:
                if (c == ':' or c == '&' or c == '|' or c == '!' ) {
                    actual = 2;
                } else if (c == '-'){
                    actual = 1;
                } else {
                    actual = udef;
                }
                break;
            case 1:
                if (c == '>') {
                    actual = 2;
                } else {
                    actual = udef;
                }
                break;
            case 2:
                actual = udef;
                break;

        }
    }

    if (prior == 2) { // Operator
        fallback();
        success();
        return operators;
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
                if (c == '\t' or c == ' ' or c == '\n') {
                    actual = 1;
                    if (c == '\n') {
                        line++;
                    }
                } else {
                    actual = udef;
                }
                break;
            case 1:
                actual = udef;
                break;

        }
    }

    if (prior == 1) { // Whitespace
        fallback();
        success();
        return whitespace;
    }

    failure();
    return err;
}

bool scanner::eof() {
    return file.eof() or file.peek() == EOF;
}

scanner::token scanner::next() {

    token t = ws();
    if (t == whitespace) return whitespace;
    
    t = id();
    if (t == identif) return identif;
    else if (t == reserved) return reserved;

    t = num();
    if (t == integer) return integer;
    else if (t == real) return real;
    else if (t == oct) return oct;
    else if (t == hex) return hex;

    t = delim();
    if (t == delimiter) return delimiter;

    t = punct();
    if (t == punctuation) return punctuation;

    t = op();
    if (t == operators) return operators;

    // t = ws();
    // if (t == whitespace) return whitespace;

    if (eof()) return _eof;
    
    return err;


}