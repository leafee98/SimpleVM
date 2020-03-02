#pragma once

#include "share/bitdef.h"
#include <string>
#include <sstream>
#include <fstream>
#include <algorithm>
#include <vector>

void trim_str(std::string & s) {
    static auto notspace = [](int c) { return ! isspace(c); };
    s.erase(
        std::find_if(s.rbegin(), s.rend(), notspace).base(), s.end());
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), notspace));
}

bool check_syntax_oneline(std::string s, std::string & error_code) {
    trim_str(s);

    if (s.size() == 0 && s[0] == '#')
        return true;

    std::stringstream ss(s);
    std::string instruction;
    ss >> instruction;

    // upper the instruction
    std::transform(instruction.begin(), instruction.end(),
            instruction.begin(), toupper);

    bool check = true;
    if (ins_no_opnum.count(instruction)) {
        // there should be nothing remained, for there's no spaces remained;
        check = ss.get() == -1;

        if (!check)
            error_code = "there should be nothing after " + instruction;
    } else if (ins_single_opnum.count(instruction)) {
        // remove spaces before number
        while (isspace(ss.peek()))
            ss.get();

        if (ss.peek() == '-') ss.get();

        // the remain show all be digit, for the spaces at the end of string were removed.
        int c;
        while (check && (c = ss.get()) != -1)
            check = isdigit(c);

        if (!check)
            error_code = "there should be only number after " + instruction;
    } else {
        check = false;
        error_code = "unknown instruction: " + instruction;
    }
    return check;
}

bool stynax_check(const std::string & path, std::string & error_msg) {
    bool fine = true;
    std::ifstream infile(path, std::ios::in);
    std::string line; int linecnt = 0;
    while (std::getline(infile, line) && linecnt++) {
        if(! check_syntax_oneline(line, error_msg)) {
            error_msg.append("\nerror on line: ");
            error_msg += linecnt;
            error_msg.append("\n    ").append(line).append("\n");
            fine = false;
            break;
        }
    }
    return fine;
}

void compile_oneline(std::string s, std::ofstream & outfile) {
    std::vector<int8_t> res;

    trim_str(s);
    if (s.size() == 0)
        return;
    std::stringstream ss(s);
    std::string instruction;
    ss >> instruction;

    // upper the instruction
    std::transform(instruction.begin(), instruction.end(),
            instruction.begin(), toupper);

    if (ins_single_opnum.count(instruction)) {
        int32_t n;
        ss >> n;
        outfile.write((char*)&insmap[instruction], sizeof(uint8_t));
        outfile.write((char*)&n, sizeof(n));
    } else {
        outfile.write((char*)&insmap[instruction], sizeof(uint8_t));
    }
}

void compile(const std::string & sources, const std::string & target) {
    std::ifstream sources_file(sources, std::ios::in);
    std::ofstream target_file(target, std::ios::binary | std::ios::out);
    std::string line;
    while (std::getline(sources_file, line, '\n')) {
        compile_oneline(line, target_file);
    }
}