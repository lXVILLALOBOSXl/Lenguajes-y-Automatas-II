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

bool scanner::next() {
    
    if (id()) return true;
    
    return false;

}