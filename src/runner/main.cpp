#include "func.hpp"
#include "share/bitdef.h"
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <stack>
#include <iostream>

int program_counter = 0;
std::vector<int8_t> program_block;
std::stack<int32_t> program_stack;

bool run_instruction(uint8_t instruction, std::string & error_msg);
void display_stack();

int main(int argc, char * args[]) {
    if (argc < 2) {
        return EXIT_FAILURE;
    }

    long filesize = get_filesize(args[1]);
    program_block.reserve(filesize);
    std::ifstream program_file(args[1], std::ios::in | std::ios::binary);
    program_file.read((char*)program_block.data(), filesize);

    std::string error_msg;
    bool run = true;
    while (run) {
        uint8_t instruction = (uint8_t)*(program_block.data() + program_counter);
        run = run_instruction(instruction, error_msg);
    }
    std::cerr << error_msg << '\n';

    display_stack();
    return EXIT_SUCCESS;
}

bool run_instruction(uint8_t instruction, std::string & error_msg) {
    int32_t opnum, opnum1, opnum2, offset;
    switch (instruction) {
        case PUSH:
            opnum = *(int32_t*)(program_block.data() + program_counter + 1);
            program_stack.push(opnum);
            program_counter += 5;
            break;
        case DUP:
            opnum = *(int32_t*)(program_block.data() + program_counter + 1);
            program_stack.push(program_stack.top());
            program_counter += 1;
            break;
        case POP:
            opnum = *(int32_t*)(program_block.data() + program_counter + 1);
            program_stack.pop();
            program_counter += 1;
            break;
        case ADD:
            opnum = *(int32_t*)(program_block.data() + program_counter + 1);
            opnum2 = program_stack.top(); program_stack.pop();
            opnum1 = program_stack.top(); program_stack.pop();
            program_stack.push(opnum1 + opnum2);
            program_counter += 1;
            break;
        case SUB:
            opnum = *(int32_t*)(program_block.data() + program_counter + 1);
            opnum2 = program_stack.top(); program_stack.pop();
            opnum1 = program_stack.top(); program_stack.pop();
            program_stack.push(opnum1 - opnum2);
            program_counter += 1;
            break;
        case MULTI:
            opnum = *(int32_t*)(program_block.data() + program_counter + 1);
            opnum2 = program_stack.top(); program_stack.pop();
            opnum1 = program_stack.top(); program_stack.pop();
            program_stack.push(opnum1 * opnum2);
            program_counter += 1;
            break;
        case DIV:
            opnum = *(int32_t*)(program_block.data() + program_counter + 1);
            opnum2 = program_stack.top(); program_stack.pop();
            opnum1 = program_stack.top(); program_stack.pop();
            program_stack.push(opnum1 / opnum2);
            program_counter += 1;
            break;
        case MOD:
            opnum = *(int32_t*)(program_block.data() + program_counter + 1);
            opnum2 = program_stack.top(); program_stack.pop();
            opnum1 = program_stack.top(); program_stack.pop();
            program_stack.push(opnum1 % opnum2);
            program_counter += 1;
            break;
        
        case IF:
            opnum = *(int32_t*)(program_block.data() + program_counter + 1);
            offset = *(int32_t*)(program_block.data() + program_counter);
            opnum = program_stack.top(); program_stack.pop();
            if (opnum == 0)
                program_counter += offset;
            else
                program_counter += 5;
            break;
        case IFNO:
            std::cout << "D: " << _ifno<< '\n';
            opnum = *(int32_t*)(program_block.data() + program_counter + 1);
            offset = *(int32_t*)(program_block.data() + program_counter);
            opnum = program_stack.top(); program_stack.pop();
            if (opnum != 0)
                program_counter += offset;
            else
                program_counter += 5;
            break;

        case NOP:
            opnum = *(int32_t*)(program_block.data() + program_counter + 1);
            program_counter += 1;
            break;
        case HALT:
            opnum = *(int32_t*)(program_block.data() + program_counter + 1);
            error_msg = "shutdown instruction";
            return false;

        default:
            std::stringstream ss; ss.setf(std::ios::hex | std::ios::showbase); ss << instruction;
            error_msg = "unknown instruction: " + ss.str();
            return false;
    }
    return true;
}

void display_stack() {
    while (program_stack.size() > 0) {
        std::cout << ' ' << program_stack.top() << '\n';
        program_stack.pop();
    }
    std::cout << "---" << std::endl;
}