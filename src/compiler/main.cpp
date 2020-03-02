#include "share/bitdef.h"
#include "func.hpp"
#include <string>
#include <fstream>
#include <iostream>

int main(int argc, char * args[]) {
    if (argc != 3) {
        return EXIT_FAILURE;
    }
    init_insmap();
    init_opnum();

    std::string error_msg;
    if (stynax_check(args[1], error_msg)) {
        compile(args[1], args[2]);
    } else {
        std::cerr << error_msg;
    }


    std::cout << "done" << std::endl;

    return EXIT_SUCCESS;
}