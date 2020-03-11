#include "share/bitdef.h"
#include "func.h"
#include <string>
#include <fstream>
#include <iostream>

namespace params {
    std::string source;
    std::string target;
    bool compile = true;
    bool help = false;;
}

bool apply_param(int argc, char * args[]) {
    for (int i = 1; i < argc; ++i) {
        std::string arg = args[i];
        if ((arg == "-h" || arg == "--help")
                && params::help == false) {
            params::help = true;
        } else if ((arg == "-d" || arg == "--decompile")
                && params::compile == true) {
            params::compile = false;
        } else if ((arg == "-s" || arg == "--source")
                && params::source.size() == 0) {
            params::source = args[++i];
        } else if ((arg == "-t" || arg == "--target")
                && params::target.size() == 0) {
            params::target = args[++i];
        } else {
            if (params::source.size() == 0) {
                params::source = args[i];
            } else if (params::target.size() == 0) {
                params::target = args[i];
            } else {
                return false;
            }
        }
    }
    return true;
}

void display_help() {
    std::cout <<
            "compiler [-d] [-s] <source file> [-t] <target file>\n"
            "\n"
            "  -h, --help           display this help and exit\n"
            "  -s, --source         specify the source file\n"
            "  -t, --target         specify the target file\n"
            "  -d, --decompile      decompile the target file to source file\n";
}

int main(int argc, char * args[]) {
    share::init();

    if (! apply_param(argc, args)) {
        std::cout << "invalid parameter or duplicated parameter.\n";
        return EXIT_FAILURE;
    }

    if (params::help) {
        display_help();
        return EXIT_SUCCESS;
    }

    if (params::compile) {
        std::string err_msg;
        std::vector<int> line_tags;

        if (compiler::check_permission(params::source, err_msg)) {
            if (compiler::check_syntax(params::source, line_tags, err_msg)) {
                if (compiler::compile(params::source, params::target,
                        line_tags, err_msg)) {
                    // do nothing, the target file was built successfully.
                } else {
                    std::cout << "compile error:\n  " << err_msg << '\n';
                    return EXIT_FAILURE;
                }
            } else {
                std::cout << "syntax error:\n  " << err_msg << '\n';
            }
        } else {
            std::cout << "permission error:\n  " << err_msg << '\n';
            return EXIT_FAILURE;
        }
    } else {
        compiler::decompile(params::target, params::source);   
    }

    return EXIT_SUCCESS;
}