#ifndef scanner_hpp
#define scanner_hpp

#include <iostream>
#include <fstream>
#include <string>
#include <set>

using namespace std;


class scanner {

public: typedef enum { _identif, _question_mark, _dots, _or, _and, _not, lpar, rpar, _false, _true, tab, _enter, whitespace, _eof, err } token;

private:

    static const int udef;

    ifstream file;
    unsigned long q; 

    int line;

    string lexeme;

    char read(){ return file.get(); }
    void fallback() { file.seekg(-1, file.cur); }

    void failure() {file.seekg(q); }
    void success() { q = file.tellg(); }

    token id();
    token ws();
    // void wsp();
    bool eof();
    bool unique(char);

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