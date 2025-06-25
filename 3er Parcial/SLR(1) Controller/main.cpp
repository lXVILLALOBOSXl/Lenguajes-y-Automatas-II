#include <iostream>
#include "parser.hpp"

int main(int argc, const char * argv[]) {

    
    string file_name;
    cin >> file_name;
    
    parser p(file_name);
    if (p.parse()) std::cout << "Ok\n";
    else std::cout << "Error sintáctico\n";   

    return 0;
}