#include "func.h"

#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include <sys/stat.h>

namespace sys {
    // program counter
    int counter = 0;
    // instruction segment
    std::vector<int8_t> ins_seg;
    // program stack
    std::vector<int32_t> stack;
    // registers
    int32_t reg_a = 0, reg_b = 0, reg_c = 0;
}

unsigned runf = 0;
// flag of running
namespace run_flag {
    const unsigned show_stack        = 1U << 0;
    const unsigned show_ins          = 1U << 1;
    const unsigned help              = 1U << 2;
}

namespace run_param {
    std::string byte_code_file;
}

void show_usage() {
    std::cout 
        << "runner <byte code file> [-v]\n"
        << "\n"
        << "    --help               show this help text.\n"
        << "    --show-status        show the status of stack step by step\n"
        << "    --show-instruction   show the instruction step by step.\n";
}

bool apply_parameter(int argc, char * args[]) {
    if (argc < 2)
        return false;
    
    for (int i = 1; i < argc; ++i) {
        if (!(runf & run_flag::help) && args[i] == std::string("--help")) {
            runf |= run_flag::help;
        } else if (!(runf & run_flag::show_stack) 
                && args[i] == std::string("--show-status")) {
            runf |= run_flag::show_stack;
        } else if (!(runf & run_flag::show_ins) &&
                args[i] == std::string("--show-instruction")) {
            runf |= run_flag::show_ins;
        } else {
            if (run_param::byte_code_file.size() == 0)
                run_param::byte_code_file = args[i];
            else {
                return false;
            }
        }
    }

    return true;   
}

long get_filesize(const std::string & file) {
    struct stat stat_buf;
    int rc = stat(file.c_str(), &stat_buf);
    return rc == 0 ? stat_buf.st_size : -1;
}

void show_status() {
    std::cout << "Register A/B/C: " << sys::reg_a << " / " << sys::reg_b
            << " / " << sys::reg_c << "; Stack (from top to end): ";
    for (auto it = sys::stack.rbegin(); it != sys::stack.rend(); ++it)
        std::cout << *it << "/ ";
    std::cout << "\n";
}

void run(std::string & err_msg) {
    using namespace run_ins;
    uint8_t instruction;

    while (err_msg.size() == 0) {
        if (sys::counter < sys::ins_seg.size())
            instruction = (uint8_t)*(sys::ins_seg.data() + sys::counter);
        else {
            err_msg = "run outside of instruction segement without HALT";
            continue;
        }

        switch (instruction) {
            case share::enum_bit::NOP:      ins_nop(err_msg);      break;
            case share::enum_bit::HALT:     ins_halt(err_msg);     break;

            case share::enum_bit::REGA:     ins_rega(err_msg);     break;
            case share::enum_bit::REGB:     ins_regb(err_msg);     break;
            case share::enum_bit::REGC:     ins_regc(err_msg);     break;

            case share::enum_bit::LOADA:    ins_loada(err_msg);    break;
            case share::enum_bit::LOADB:    ins_loadb(err_msg);    break;
            case share::enum_bit::LOADC:    ins_loadc(err_msg);    break;

            case share::enum_bit::READ:     ins_read(err_msg);     break;
            case share::enum_bit::PUSH:     ins_push(err_msg);     break;
            case share::enum_bit::DUP:      ins_dup(err_msg);      break;
            case share::enum_bit::POP:      ins_pop(err_msg);      break;

            case share::enum_bit::JMP:      ins_jmp(err_msg);      break;
            case share::enum_bit::IF:       ins_if(err_msg);       break;
            case share::enum_bit::IFNO:     ins_ifno(err_msg);     break;
            
            case share::enum_bit::ADD:      ins_add(err_msg);      break;
            case share::enum_bit::SUB:      ins_sub(err_msg);      break;
            case share::enum_bit::MULTI:    ins_multi(err_msg);    break;
            case share::enum_bit::DIV:      ins_div(err_msg);      break;
            case share::enum_bit::MOD:      ins_mod(err_msg);      break;

            default:
                std::stringstream ss;
                ss.setf(std::ios::hex | std::ios::showbase);
                ss << instruction;
                err_msg = "unknown instruction: " + ss.str();
                break;
        }
    }
}

namespace run_ins {
    void ins_nop(std::string & err_msg) {
        sys::counter += 1;

        if (runf & run_flag::show_ins)      std::cout << "Instruction: NOPE\n";
        if (runf & run_flag::show_stack)    show_status();
    };
    void ins_halt(std::string & err_msg) {
        err_msg = "shutdown instruction";

        if (runf & run_flag::show_ins)      std::cout << "Instruction: HALT\n";
        if (runf & run_flag::show_stack)    show_status();
    };

    void ins_rega(std::string & err_msg) {
        sys::reg_a = sys::stack.back();
        sys::stack.pop_back();
        sys::counter += 1;

        if (runf & run_flag::show_ins)      std::cout << "Instruction: REGA\n";
        if (runf & run_flag::show_stack)    show_status();
    };
    void ins_regb(std::string & err_msg) {
        sys::reg_b = sys::stack.back();
        sys::stack.pop_back();
        sys::counter += 1;

        if (runf & run_flag::show_ins)      std::cout << "Instruction: REGB\n";
        if (runf & run_flag::show_stack)    show_status();
    };
    void ins_regc(std::string & err_msg) {
        sys::reg_c = sys::stack.back();
        sys::stack.pop_back();
        sys::counter += 1;

        if (runf & run_flag::show_ins)      std::cout << "Instruction: REGC\n";
        if (runf & run_flag::show_stack)    show_status();
    };
    void ins_loada(std::string & err_msg) {
        sys::stack.push_back(sys::reg_a);
        sys::counter += 1;

        if (runf & run_flag::show_ins)      std::cout << "Instruction: LOADA\n";
        if (runf & run_flag::show_stack)    show_status();
    };
    void ins_loadb(std::string & err_msg) {
        sys::stack.push_back(sys::reg_b);
        sys::counter += 1;

        if (runf & run_flag::show_ins)      std::cout << "Instruction: LOADB\n";
        if (runf & run_flag::show_stack)    show_status();
    };
    void ins_loadc(std::string & err_msg) {
        sys::stack.push_back(sys::reg_c);
        sys::counter += 1;

        if (runf & run_flag::show_ins)      std::cout << "Instruction: LOADC\n";
        if (runf & run_flag::show_stack)    show_status();
    };

    void ins_read(std::string & err_msg) {
        int32_t opnum;
        std::cout << "Please input opnum: ";
        std::cin >> opnum;
        sys::stack.push_back(opnum);
        sys::counter += 1;

        if (runf & run_flag::show_ins)      std::cout << "Instruction: READ\n";
        if (runf & run_flag::show_stack)    show_status();
    };
    void ins_push(std::string & err_msg) {
        int32_t opnum;
        opnum = *(int32_t*)(sys::ins_seg.data() + sys::counter + 1);
        sys::stack.push_back(opnum);
        sys::counter += 5;

        if (runf & run_flag::show_ins)      std::cout << "Instruction: PUSH\n";
        if (runf & run_flag::show_stack)    show_status();
    };
    void ins_dup(std::string & err_msg) {
        sys::stack.push_back(sys::stack.back());
        sys::counter += 1;

        if (runf & run_flag::show_ins)      std::cout << "Instruction: DUP\n";
        if (runf & run_flag::show_stack)    show_status();
    };
    void ins_pop(std::string & err_msg) {
        sys::stack.pop_back();
        sys::counter += 1;

        if (runf & run_flag::show_ins)      std::cout << "Instruction: POP\n";
        if (runf & run_flag::show_stack)    show_status();
    };

    void ins_jmp(std::string & err_msg) {
        uint32_t offset;
        offset = *(int32_t*)(sys::ins_seg.data() + sys::counter + 1);
        sys::counter = offset;

        if (runf & run_flag::show_ins)      std::cout << "Instruction: JMP\n";
        if (runf & run_flag::show_stack)    show_status();
    };
    void ins_if(std::string & err_msg) {
        uint32_t offset;
        offset = *(int32_t*)(sys::ins_seg.data() + sys::counter + 1);
        int32_t opnum = sys::stack.back(); sys::stack.pop_back();
        if (opnum == 0)
            sys::counter = offset;
        else
            sys::counter += 5;

        if (runf & run_flag::show_ins)      std::cout << "Instruction: IF\n";
        if (runf & run_flag::show_stack)    show_status();
    };
    void ins_ifno(std::string & err_msg) {
        uint32_t offset;
        offset = *(int32_t*)(sys::ins_seg.data() + sys::counter + 1);
        int32_t opnum = sys::stack.back(); sys::stack.pop_back();
        if (opnum != 0)
            sys::counter = offset;
        else
            sys::counter += 5;

        if (runf & run_flag::show_ins)      std::cout << "Instruction: IFNO\n";
        if (runf & run_flag::show_stack)    show_status();
    };

    void ins_add(std::string & err_msg) {
        sys::stack.push_back(sys::reg_a + sys::reg_b);
        sys::counter += 1;

        if (runf & run_flag::show_ins)      std::cout << "Instruction: ADD\n";
        if (runf & run_flag::show_stack)    show_status();
    };
    void ins_sub(std::string & err_msg) {
        sys::stack.push_back(sys::reg_a - sys::reg_b);
        sys::counter += 1;

        if (runf & run_flag::show_ins)      std::cout << "Instruction: SUB\n";
        if (runf & run_flag::show_stack)    show_status();
    };
    void ins_multi(std::string & err_msg) {
        sys::stack.push_back(sys::reg_a * sys::reg_b);
        sys::counter += 1;

        if (runf & run_flag::show_ins)      std::cout << "Instruction: MULTI\n";
        if (runf & run_flag::show_stack)    show_status();
    };
    void ins_div(std::string & err_msg) {
        sys::stack.push_back(sys::reg_a / sys::reg_b);
        sys::counter += 1;

        if (runf & run_flag::show_ins)      std::cout << "Instruction: DIV\n";
        if (runf & run_flag::show_stack)    show_status();
    };
    void ins_mod(std::string & err_msg) {
        sys::stack.push_back(sys::reg_a % sys::reg_b);
        sys::counter += 1;

        if (runf & run_flag::show_ins)      std::cout << "Instruction: MOD\n";
        if (runf & run_flag::show_stack)    show_status();
    };
}