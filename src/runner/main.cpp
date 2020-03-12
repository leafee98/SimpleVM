#include "func.h"
#include "share/bitdef.h"
#include <sstream>
#include <fstream>
#include <string>
#include <iostream>

int main(int argc, char * args[]) {
    if (! apply_parameter(argc, args)) {
        std::cout << "invalid parameter or duplicated parameter.\n";
        show_usage();
        return EXIT_FAILURE;
    }

    if (runf & run_flag::help) {
        show_usage();
        return EXIT_SUCCESS;
    }

    long filesize = get_filesize(run_param::byte_code_file);
    sys::ins_seg.reserve(filesize);
    std::ifstream program_file(run_param::byte_code_file,
            std::ios::in | std::ios::binary);
    program_file.read((char*)sys::ins_seg.data(), filesize);

    std::string error_msg;
    run(error_msg);
    std::cerr << "running result / error reason:\n  " << error_msg << '\n';

    show_status();
    return EXIT_SUCCESS;
}
