#ifndef scanner_hpp
#define scanner_hpp

#include <iostream>
#include <fstream>
#include <string>
#include <set>

using namespace std;


class scanner {

public: typedef enum { integer, real, oct, hex, identif, _true, _false, _print, lbra, rbra, lpar, rpar, _point, _comma, _pandcomma, dots, ampersand, bar, excla, arrow, tab, _enter, whitespace, _comment, _eof, err } token;

private:

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
    token comment();
    bool eof();

public:

 


    scanner(string fname): file(fname) {

        line = 1;

        q = 0;
        
    }
    
    // Destructor to close the file
    ~scanner() { file.close(); }

    int get_line() { return line; }
    string get_lexeme() { return lexeme; }

    token next();
};


#endif /* scanner_hpp */