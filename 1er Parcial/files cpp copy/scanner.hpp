#ifndef scanner_hpp
#define scanner_hpp

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class scanner {

public: typedef enum { integer, real, identif, _eof, err } token;

private:

    static const int udef;


    ifstream file;
    unsigned long q; 

    char read(){ return file.get(); }
    void fallback() { file.seekg(-1, file.cur); }

    void failure() { file.seekg(q); }
    void success() { q = file.tellg(); }

    void wsp();
    bool id();
    token num();
    bool eof();

public:


    scanner(string fname): file(fname) {

        q = 0;
    }

    token next();
};


#endif /* scanner_hpp */