#include "func.h"
#include "share/bitdef.h"
#include <sstream>
#include <fstream>
#include <string>
#include <iostream>

int main(int argc, char * args[]) {
    if (! apply_parameter(argc, args)) {
        show_usage();
        return EXIT_FAILURE;
    }

    long filesize = get_filesize(run_param::byte_code_file);
    program_block.reserve(filesize);
    std::ifstream program_file(run_param::byte_code_file, std::ios::in | std::ios::binary);
    program_file.read((char*)program_block.data(), filesize);

    std::string error_msg;
    bool run = true;
    while (run) {
        uint8_t instruction = (uint8_t)*(program_block.data() + program_counter);
        run = run_instruction(instruction, error_msg);
    }
    std::cerr << "running result / error reason:\n" << error_msg << '\n';

    display_stack();
    return EXIT_SUCCESS;
}
