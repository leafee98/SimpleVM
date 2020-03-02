#include "func.h"

#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include <sys/stat.h>

int run_flag = 0;
int program_counter = 0;
std::vector<int8_t> program_block;
std::vector<int32_t> program_stack;

namespace runf {
    const int show_stack        = 1 << 0;
    const int show_instruction  = 1 << 1;
}

namespace run_param {
    std::string byte_code_file;
}

long get_filesize(const std::string & file) {
    struct stat stat_buf;
    int rc = stat(file.c_str(), &stat_buf);
    return rc == 0 ? stat_buf.st_size : -1;
}

bool run_instruction(uint8_t instruction, std::string & error_msg) {
    int32_t opnum, opnum1, opnum2, offset;

    static auto ins_push = [&]() {
        opnum = *(int32_t*)(program_block.data() + program_counter + 1);
        program_stack.push_back(opnum);
        program_counter += 5;

        if (run_flag & runf::show_instruction)  std::cout << "INSTRUCTION: " << _push << ' ' << opnum << '\n';
        if (run_flag & runf::show_stack)        display_stack();
    };
    static auto ins_dup = [&]() {
        program_stack.push_back(program_stack.back());
        program_counter += 1;

        if (run_flag & runf::show_instruction)  std::cout << "INSTRUCTION: " << _dup << '\n';
        if (run_flag & runf::show_stack)        display_stack();
    };
    static auto ins_pop = [&]() {
        program_stack.pop_back();
        program_counter += 1;

        if (run_flag & runf::show_instruction)  std::cout << "INSTRUCTION: " << _pop << '\n';
        if (run_flag & runf::show_stack)        display_stack();
    };

    static auto ins_add = [&]() {
        opnum2 = program_stack.back(); program_stack.pop_back();
        opnum1 = program_stack.back(); program_stack.pop_back();
        program_stack.push_back(opnum1 + opnum2);
        program_counter += 1;

        if (run_flag & runf::show_instruction)  std::cout << "INSTRUCTION: " << _add << '\n';
        if (run_flag & runf::show_stack)        display_stack();
    };
    static auto ins_sub = [&]() {
        opnum2 = program_stack.back(); program_stack.pop_back();
        opnum1 = program_stack.back(); program_stack.pop_back();
        program_stack.push_back(opnum1 - opnum2);
        program_counter += 1;

        if (run_flag & runf::show_instruction)  std::cout << "INSTRUCTION: " << _sub << '\n';
        if (run_flag & runf::show_stack)        display_stack();
    };
    static auto ins_multi = [&]() {
        opnum2 = program_stack.back(); program_stack.pop_back();
        opnum1 = program_stack.back(); program_stack.pop_back();
        program_stack.push_back(opnum1 * opnum2);
        program_counter += 1;

        if (run_flag & runf::show_instruction)  std::cout << "INSTRUCTION: " << _multi << '\n';
        if (run_flag & runf::show_stack)        display_stack();
    };
    static auto ins_div = [&]() {
        opnum2 = program_stack.back(); program_stack.pop_back();
        opnum1 = program_stack.back(); program_stack.pop_back();
        program_stack.push_back(opnum1 / opnum2);
        program_counter += 1;

        if (run_flag & runf::show_instruction)  std::cout << "INSTRUCTION: " << _div << '\n';
        if (run_flag & runf::show_stack)        display_stack();
    };
    static auto ins_mod = [&]() {
        opnum2 = program_stack.back(); program_stack.pop_back();
        opnum1 = program_stack.back(); program_stack.pop_back();
        program_stack.push_back(opnum1 % opnum2);
        program_counter += 1;

        if (run_flag & runf::show_instruction)  std::cout << "INSTRUCTION: " << _mod << '\n';
        if (run_flag & runf::show_stack)        display_stack();
    };

    static auto ins_if = [&]() {
        offset = *(int32_t*)(program_block.data() + program_counter + 1);
        opnum = program_stack.back(); program_stack.pop_back();
        if (opnum == 0)
            program_counter += offset;
        else
            program_counter += 5;

        if (run_flag & runf::show_instruction)  std::cout << "INSTRUCTION: " << _if << ' ' << offset << '\n';
        if (run_flag & runf::show_stack)        display_stack();
    };
    static auto ins_ifno = [&]() {
        offset = *(int32_t*)(program_block.data() + program_counter + 1);
        opnum = program_stack.back(); program_stack.pop_back();
        if (opnum != 0)
            program_counter += offset;
        else
            program_counter += 5;

        if (run_flag & runf::show_instruction)  std::cout << "INSTRUCTION: " << _ifno << ' ' << offset << '\n';
        if (run_flag & runf::show_stack)        display_stack();
    };

    static auto ins_nop = [&]() {
        program_counter += 1;

        if (run_flag & runf::show_instruction)  std::cout << "INSTRUCTION: " << _nop << '\n';
        if (run_flag & runf::show_stack)        display_stack();
    };
    static auto ins_halt = [&]() {
        error_msg = "shutdown instruction";

        if (run_flag & runf::show_instruction)  std::cout << "INSTRUCTION: " << _halt<< '\n';
        if (run_flag & runf::show_stack)        display_stack();
    };

    switch (instruction) {
        case PUSH:  ins_push();     break;
        case DUP:   ins_dup();      break;
        case POP:   ins_pop();      break;

        case ADD:   ins_add();      break;
        case SUB:   ins_sub();      break;
        case MULTI: ins_multi();    break;
        case DIV:   ins_div();      break;
        case MOD:   ins_mod();      break;
        
        case IF:    ins_if();       break;
        case IFNO:  ins_ifno();     break;

        case NOP:   ins_nop();      break;
        case HALT:  ins_halt();     break;

        default:
            std::stringstream ss; ss.setf(std::ios::hex | std::ios::showbase); ss << instruction;
            error_msg = "unknown instruction: " + ss.str();
            break;
    }
    return error_msg.size() == 0;
}

void display_stack() {
    for (auto it = program_stack.rbegin(); it != program_stack.rend(); ++it)
        std::cout << ' ' << *it << '\n';
    std::cout << "---" << std::endl;
}

bool apply_parameter(int argc, char * args[]) {
    if (argc < 2)
        return false;
    
    for (int i = 1; i < argc; ++i) {
        if (args[i] == std::string("--show-stack")) {
            run_flag |= runf::show_stack;
        } else if (args[i] == std::string("--show-instruction")) {
            run_flag |= runf::show_instruction;
        } else {
            run_param::byte_code_file = args[i];
        }
    }

    return true;   
}

void show_usage() {
    std::cout 
            << "runner <byte code file> [-v]\n"
            << "\n"
            << "    --show-stack        show the status of stack step by step\n"
            << "    --show-instruction  show the instruction run on this step\n";
}