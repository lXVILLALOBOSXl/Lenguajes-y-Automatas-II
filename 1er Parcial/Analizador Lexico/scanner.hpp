#ifndef scanner_hpp
#define scanner_hpp

#include <iostream>
#include <fstream>
#include <string>
#include <set>

using namespace std;


class scanner {

public: typedef enum { integer, real, oct, hex, identif, reserved, delimiter, punctuation, operators, whitespace, _eof, err } token;

private:

    // Reserved words are: print, true, false
    set<string> reserved_words;

    static const int udef;

    ifstream file;
    unsigned long q; 

    int line;

    string lexeme;

    char read(){ return file.get(); }
    void fallback() { file.seekg(-1, file.cur); }

    void failure() { file.clear(); file.seekg(q); }
    void success() { q = file.tellg(); }

    token id();
    token num();
    token delim();
    token punct();
    token op();
    token ws();
    bool eof();

public:

 


    scanner(string fname): file(fname) {

        line = 1;

        q = 0;
        reserved_words.insert("print");
        reserved_words.insert("true");
        reserved_words.insert("false");
        
    }

    int get_line() { return line; }
    string get_lexeme() { return lexeme; }

    token next();
};


#endif /* scanner_hpp */