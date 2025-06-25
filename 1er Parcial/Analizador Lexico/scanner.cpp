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


    if (lexeme == "true"){
        fallback();
        success();
        return _true;
    } else if (lexeme == "false"){
        fallback();
        success();
        return _false;
    } else if (lexeme == "print"){
        fallback();
        success();
        return _print;
    }  

    if (prior == 2) { // Identif
        fallback();
        success();
        return identif;
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

    lexeme = "";

    while (actual != udef) {

        prior = actual;
        char c = read();

        switch (actual) {

            case 0:
                if (c == '(') {
                    actual = 1;
                    lexeme += c;
                } else if (c == ')') {
                    actual = 2;
                    lexeme += c;
                } else if (c == '[') {
                    actual = 3;
                    lexeme += c;
                } else if (c == ']') {
                    actual = 4;
                    lexeme += c;
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
            case 4:
                actual = udef;
                break;

        }
    }

    if (prior == 1) { // Delimiter
        fallback();
        success();
        return lpar;
    }else if (prior == 2) { // Delimiter
        fallback();
        success();
        return rpar;
    }else if (prior == 3) { // Delimiter
        fallback();
        success();
        return lbra;
    }else if (prior == 4) { // Delimiter
        fallback();
        success();
        return rbra;
    }

    failure();
    return err;
}

scanner::token scanner::punct() {

    int actual = 0;
    int prior = udef;

    lexeme = "";

    while (actual != udef) {

        prior = actual;
        char c = read();

        switch (actual) {

            case 0:
                if (c == '.') {
                    actual = 1;
                    lexeme += c;
                } else if (c == ',') {
                    actual = 2;
                    lexeme += c;
                } else if (c == ';') {
                    actual = 3;
                    lexeme += c;
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

    if (prior == 1) { 
        fallback();
        success();
        return _point;
    }else if (prior == 2) { 
        fallback();
        success();
        return _comma;
    }else if (prior == 3) { 
        fallback();
        success();
        return _pandcomma;
    }

    failure();
    return err;
}

scanner::token scanner::op() {

    int actual = 0;
    int prior = udef;

    lexeme = "";

    while (actual != udef) {

        prior = actual;
        char c = read();

        switch (actual) {

            case 0:
                if (c == ':'){
                    actual = 1;
                    lexeme += c;
                } else if (c == '&'){
                    actual = 2;
                    lexeme += c;
                } else if (c == '|'){
                    actual = 3;
                    lexeme += c;
                } else if (c == '!'){
                    actual = 4;
                    lexeme += c;
                } else if (c == '-'){
                    actual = 5;
                    lexeme += c;
                }  else {
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
            case 4:
                actual = udef;
                break;
            case 5:
                if (c == '>'){
                    actual = 6;
                    lexeme += c;
                } else {
                    actual = udef;
                }
                break;
            case 6:
                actual = udef;
                break;

        }


    }

    if (prior == 1) { 
        fallback();
        success();
        return dots;
    }else if (prior == 2) {
        fallback();
        success();
        return ampersand;
    }else if (prior == 3) {
        fallback();
        success();
        return bar;
    }else if (prior == 4) {
        fallback();
        success();
        return excla;
    }else if (prior == 6) {
        fallback();
        success();
        return arrow;
    }

    failure();
    return err;
}

scanner::token scanner::comment() {

    int actual = 0;
    int prior = udef;

    lexeme = "";

    while (actual != udef) {

        prior = actual;
        char c = read();

        switch (actual) {

            case 0:
                if (c == '#'){
                    actual = 1;
                    lexeme += c;
                } else {
                    actual = udef;
                }
                break;
            case 1:
                if (c == '\n'){
                    actual = 2;
                } else {
                    actual = 1;
                    lexeme += c;
                }
                break;
            case 2:
                actual = udef;
                break;

        }

    }

    if (prior == 2) { // Comment
        fallback();
        success();
        return _comment;
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

bool scanner::eof() {
    return file.eof() or file.peek() == EOF;
}

scanner::token scanner::next() {

    token t = ws();
    if (t == whitespace) return whitespace;
    
    t = id();
    if (t == identif) return identif;
    else if (t == _true) return _true;
    else if (t == _false) return _false;
    else if (t == _print) return _print;

    t = num();
    if (t == integer) return integer;
    else if (t == real) return real;
    else if (t == oct) return oct;
    else if (t == hex) return hex;

    t = delim();
    if (t == lpar) return lpar;
    else if (t == rpar) return rpar;
    else if (t == lbra) return lbra;
    else if (t == rbra) return rbra;

    t = punct();
    if (t == _point) return _point;
    else if (t == _comma) return _comma;
    else if (t == _pandcomma) return _pandcomma;

    t = op();
    if (t == dots) return dots;
    else if (t == ampersand) return ampersand;
    else if (t == bar) return bar;
    else if (t == excla) return excla;
    else if (t == arrow) return arrow;

    t = comment();
    if (t == _comment) return _comment;

    if (eof()) return _eof;
    
    return err;


}