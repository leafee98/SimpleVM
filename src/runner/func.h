#ifndef FUNC_H_
#define FUNC_H_
//#pragma once

#include "share/bitdef.h"
#include <vector>

extern int run_flag;
extern int program_counter;
extern std::vector<int8_t> program_block;
extern std::vector<int32_t> program_stack;

long get_filesize(const std::string & file);
bool run_instruction(uint8_t instruction, std::string & error_msg);
void display_stack();
bool apply_parameter(int argc, char * args[]);
void show_usage();

namespace runf {
    extern const int show_stack;
    extern const int show_instruction;
}

namespace run_param {
    extern std::string byte_code_file;
}

#endif