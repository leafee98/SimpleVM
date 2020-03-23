#include "func.h"

#include <iomanip>

namespace compiler {

    const std::regex line_regex::identifier = std::regex(R"(:([a-zA-Z_]\w*))");
    const std::regex line_regex::noparam = std::regex(R"((\w+))");
    const std::regex line_regex::logic = std::regex(R"((\w+)\s+([a-zA-Z_]\w*))");
    const std::regex line_regex::digit = std::regex(R"((\w+)\s+(-?\d+))");

    const int line_tag::NONE = -1;
    const int line_tag::COMMENT = 0;
    const int line_tag::IDENTIFIER = 1;
    const int line_tag::NOPARAM_OP = 2;
    const int line_tag::LOGIC_OP = 3;
    const int line_tag::DIGIT_OP = 4;

    std::string & trim_str(std::string & s) {
        static auto notspace = [](int c) { return ! isspace(c); };
        s.erase(std::find_if(s.rbegin(), s.rend(), notspace).base(), s.end());
        s.erase(s.begin(), std::find_if(s.begin(), s.end(), notspace));
        return s;
    }

    std::string & upper_str(std::string & s) {
        std::transform(s.begin(), s.end(), s.begin(), toupper);
        return s;
    }

    bool check_permission(std::string source_file, std::string & err_msg) {
        if (! std::filesystem::exists(source_file)) {
            err_msg = "no such file: " + source_file;
            return false;
        }

        std::ifstream fin(source_file, std::ios::in);
        if (! fin.good()) {
            err_msg = "source_file unreadable";
            return false;
        }
        fin.close();
        
        return true;
    }

    bool check_syntax(std::string source_file, std::vector<int> & line_tags,
            std::string & err_msg) {
        static auto validate_comment = [](std::string line) {
            if (line[0] == '#')     return true;
            else                    return false;
        };
        static auto validate_identifier = [](std::string line) {
            return std::regex_match(line, line_regex::identifier);
        };
        static auto validate_noparam = [](std::string line) {
            std::smatch m;
            return std::regex_match(line, m, line_regex::noparam) 
                    && bitdef::validate_opname(m[1].str()) == 1;
        };
        static auto validate_logic = [](std::string line) {
            std::smatch m;
            return std::regex_match(line, m, line_regex::logic)
                    && bitdef::validate_opname(m[1].str()) == 3;
        };
        static auto validate_digit = [](std::string line) {
            std::smatch m;
            return std::regex_match(line, m, line_regex::digit)
                    && bitdef::validate_opname(m[1].str()) == 2;
        };

        line_tags.clear();
        std::ifstream fin(source_file, std::ios::in);
        std::string line;
        for (int line_number = 1; std::getline(fin, line); ++line_number) {
            trim_str(line);
            upper_str(line);

            if (line.size() == 0) {
                line_tags.emplace_back(line_tag::NONE);
            } else if (validate_comment(line)) {
                line_tags.emplace_back(line_tag::COMMENT);
            } else if (validate_identifier(line)) {
                line_tags.emplace_back(line_tag::IDENTIFIER);
            } else if (validate_noparam(line)) {
                line_tags.emplace_back(line_tag::NOPARAM_OP);
            } else if (validate_logic(line)) {
                line_tags.emplace_back(line_tag::LOGIC_OP);
            } else if (validate_digit(line)) {
                line_tags.emplace_back(line_tag::DIGIT_OP);
            } else {
                err_msg = "syntax error on line " + std::to_string(line_number);
                fin.close();
                return false;
            }
        }

        fin.close();
        return true;
    }

    bool compile(std::string source_file, std::string target_file,
            const std::vector<int> & line_tags, std::string & err_msg) {
        // id's name, where it is.
        std::map<std::string, uint32_t> identifiers;
        // where it's required, id's name.
        std::map<uint32_t, std::string> ident_tofill; 
        uint32_t program_offset = 0;

        std::smatch tmp_match_result;
        std::string tmp_identifier;
        std::string tmp_instruction;
        uint8_t tmp_instruction_bit;
        int32_t tmp_digit;

        const int DIGIT_SIZE = 4;
        const int INSTRUCTION_SIZE = 1;
        
        std::ifstream fin(source_file, std::ios::in);
        std::ofstream fout(target_file, std::ios::out | std::ios::binary);

        std::string line;

        for (unsigned i = 0, lcnt = line_tags.size();
                std::getline(fin, line, '\n') && i < lcnt; ++i) {
            trim_str(line);
            upper_str(line);

            switch (line_tags[i]) {
                case line_tag::NONE:
                    // do nothing
                    break;
                case line_tag::COMMENT:
                    // do nothing;
                    break;
                case line_tag::IDENTIFIER:
                    std::regex_match(line, tmp_match_result,
                            line_regex::identifier);
                    tmp_identifier = tmp_match_result[1].str();

                    if (identifiers.count(tmp_identifier)) {
                        err_msg = "error on line " + std::to_string(i + 1)
                                + ", duplicate identifier: " + tmp_identifier;
                        fin.close(); fout.close();
                        return false;
                    }
                    identifiers[tmp_identifier] = program_offset;

                    fout.write((char*)&share::enum_bit::NOP, 1);
                    program_offset += 1;
                    break;

                case line_tag::NOPARAM_OP:
                    std::regex_match(line, tmp_match_result, 
                            line_regex::noparam);
                    tmp_instruction = tmp_match_result[1].str();

                    tmp_instruction_bit = bitdef::getbit(tmp_instruction);
                    fout.write((char*)&tmp_instruction_bit, INSTRUCTION_SIZE);
                    program_offset += 1;
                    break;

                case line_tag::LOGIC_OP:
                    std::regex_match(line, tmp_match_result, 
                            line_regex::logic);
                    tmp_instruction = tmp_match_result[1].str();
                    tmp_identifier = tmp_match_result[2].str();

                    // store the identifiers' offset to fill
                    ident_tofill[program_offset + 1] = tmp_identifier;

                    tmp_instruction_bit = bitdef::getbit(tmp_instruction);
                    tmp_digit = 0;
                    fout.write((char*)&tmp_instruction_bit, INSTRUCTION_SIZE);
                    fout.write((char*)&tmp_digit, DIGIT_SIZE);
                    program_offset += 5;
                    break;

                case line_tag::DIGIT_OP:
                    std::regex_match(line, tmp_match_result,
                            line_regex::digit);
                    tmp_instruction = tmp_match_result[1].str();
                    tmp_digit = stoi(tmp_match_result[2].str());

                    tmp_instruction_bit = bitdef::getbit(tmp_instruction);
                    fout.write((char*)&tmp_instruction_bit, INSTRUCTION_SIZE);
                    fout.write((char*)&tmp_digit, DIGIT_SIZE);
                    
                    program_offset += 5;
                    break;
            }
        }

        for (auto x : ident_tofill) {
            if (identifiers.count(x.second) <= 0) {
                err_msg = "no such identifier: " + x.second;
                fin.close(), fout.close();
                return false;
            }

            fout.seekp(x.first);
            tmp_digit = identifiers[x.second];
            fout.write((char*)&tmp_digit, DIGIT_SIZE);
        }

        fin.close(); fout.close();
        return true;
    }

    void decompile(std::string target_file, std::string source_file) {
        static const std::string ident_prefix = "indentifier_";

        std::ifstream fin(target_file, std::ios::in | std::ios::binary);
        std::ofstream fout(source_file, std::ios::out);

        std::vector<std::string> lines;
        std::map<uint32_t, std::string> pos_ident;

        // temporary variables
        uint8_t ins_bit;
        std::string ins_str;
        int32_t tmp_int32;
        uint32_t tmp_uint32;

        uint32_t pro_cnt = 0, ident_cnt = 1;

        // take NOP aside, treat it as identifier
        // record all identifier here
        for (unsigned ins_cnt = 0; fin.read((char*)&ins_bit, 1); ++ins_cnt) {
            if (ins_bit == share::enum_bit::NOP) {
                pos_ident[pro_cnt] = ident_prefix + std::to_string(ident_cnt);
                ++ident_cnt;
                ++pro_cnt;
            } else if (bitdef::validate_opname(bitdef::getopname(ins_bit)) == 1) {
                ++pro_cnt;
            } else {
                fin.read((char*)&tmp_int32, 4);
                pro_cnt += 5;
            }
        } 

        fin.clear();
        fin.seekg(0);
        pro_cnt = 0;

        for (unsigned ins_cnt = 0; fin.read((char*)&ins_bit, 1); ++ins_cnt) {
            ins_str = bitdef::getopname(ins_bit);
            int validate_result = bitdef::validate_opname(ins_str);

            // if there is an identifier, write it to source file.
            if (pos_ident.count(pro_cnt) > 0) {
                lines.emplace_back(':' + pos_ident[pro_cnt] + '\n');
                pro_cnt += 1;
                continue;
            }

            switch (validate_result) {
                case 1:
                    ins_str += "\n";
                    lines.emplace_back(ins_str);
                    pro_cnt += 1;
                    break;
                case 2:
                    fin.read((char*)&tmp_int32, sizeof(int32_t));
                    ins_str += " " + std::to_string(tmp_int32) + '\n';
                    lines.emplace_back(ins_str);
                    pro_cnt += 5;
                    break;
                case 3:
                    fin.read((char*)&tmp_uint32, sizeof(uint32_t));
                    ins_str += " " + pos_ident[tmp_uint32] + '\n';
                    lines.emplace_back(ins_str);
                    pro_cnt += 5;
                    break;
            }
        }

        // write the result in vector lines to file;
        for (auto x : lines) {
            fout << x;
        }

        fin.close(); fout.close();
    }

}