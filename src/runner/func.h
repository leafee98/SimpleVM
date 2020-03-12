#pragma once

#include "share/bitdef.h"
#include <vector>

long get_filesize(const std::string & file);
void run(std::string & error_msg);
void show_status();
bool apply_parameter(int argc, char * args[]);
void show_usage();

extern unsigned runf;
// flag on running
namespace run_flag {
    extern const unsigned show_stack;
    extern const unsigned show_instruction;
    extern const unsigned help;
}

namespace run_param {
    extern std::string byte_code_file;
}

namespace sys {
    // program counter
    extern int counter;
    // instruction segment
    extern std::vector<int8_t> ins_seg;
    // program stack
    extern std::vector<int32_t> stack;
    // registers
    extern int32_t reg_a;
    extern int32_t reg_b;
    extern int32_t reg_c;
}


namespace run_ins {
    void ins_nop(std::string & err_msg);
    void ins_halt(std::string & err_msg);

    void ins_rega(std::string & err_msg);
    void ins_regb(std::string & err_msg);
    void ins_regc(std::string & err_msg);
    void ins_loada(std::string & err_msg);
    void ins_loadb(std::string & err_msg);
    void ins_loadc(std::string & err_msg);

    void ins_read(std::string & err_msg);
    void ins_push(std::string & err_msg);
    void ins_dup(std::string & err_msg);
    void ins_pop(std::string & err_msg);

    void ins_jmp(std::string & err_msg);
    void ins_if(std::string & err_msg);
    void ins_ifno(std::string & err_msg);

    void ins_add(std::string & err_msg);
    void ins_sub(std::string & err_msg);
    void ins_multi(std::string & err_msg);
    void ins_div(std::string & err_msg);
    void ins_mod(std::string & err_msg);
}
