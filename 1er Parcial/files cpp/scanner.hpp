#ifndef scanner_hpp
#define scanner_hpp

#include <iostream>
#include <fstream>
#include <string>

using namespace std;


class scanner {

    static const int udef;

    ifstream file;
    unsigned long q; 

    char read(){ return file.get(); }
    void fallback() { file.seekg(-1, file.cur); }

    void failure() { file.seekg(q); }
    void success() { q = file.tellg(); }

    bool id();

public:

    scanner(string fname): file(fname) {

        q = 0;
    }

    bool next();
};


#endif /* scanner_hpp */