#include "scanner.hpp"


const int scanner::udef = -1;

bool scanner::id() {

    int actual = 0, prior = udef;

    while (actual != udef) {
        
        char c = read();
        prior = actual;

        switch (actual) {
            case 0:
                if (isalpha(c)) actual = 2;
                else if (c == '_') actual = 1;
                else actual = udef;

                break;
                
            case 1:

                if (isdigit(c) or c == '_') actual = 1;
                else if (isalpha(c)) actual = 2;
                else actual = udef;

                break;
                
            case 2:

                if (isalnum(c) or c == '_') actual = 2;
                else actual = udef;
                
        } 
    }
    
    if (prior == 2) {
        fallback();
        success();
        return true;
    }

    failure();
    return false;
}

scanner::token scanner::num() {

    int actual = 0;
    int prior = udef;

    while (actual != udef) {

        prior = actual;
        char c = read();

        switch (actual) {

            case 0:
                if (c == '0') actual = 1;
                else if (isdigit(c)) actual = 3;
                else actual = udef;
                break;
            case 1:
                if (isdigit(c)) actual = 2;
                else if (c == '.') actual = 4;
                else if (isalpha(c)) actual = 6; // Prevent transition 0a
                else actual = udef;
                break;
            case 2:
                if (isdigit(c)) actual = 2; 
                else if (c == '.') actual = 4; 
                else actual = udef;
                break;
            case 3:
                if (isdigit(c)) actual = 3;
                else if (c == '.') actual = 4;
                else if (isalpha(c)) actual = 6; // Prevent transition 123a
                else actual = udef;
                break;
            case 4:
            case 5:
                if (isdigit(c)) actual = 5;
                else if (isalpha(c)) actual = 6; // Prevent transition 1.2a
                else actual = udef;
                break;
            case 6: // Error state
                actual = udef;
                break;
        } 
    }
    if (prior == 1 or prior == 3){ // Integer
        fallback();
        success();
        return integer;
    }else if (prior == 5){ // Real
        fallback();
        success();
        return real;
    }
    
    failure();
    return err;
    
}

void scanner::wsp() {
    while (isspace(read()));

    fallback();
    success();
}

bool scanner::eof() {
    return file.eof() or file.peek() == EOF;
}

scanner::token scanner::next() {
    wsp();

    if (id()) return identif;

    token t = num();
    if (t == integer) return integer;
    if (t == real) return real;

    if (eof()) return _eof;
 

    return err;  
}