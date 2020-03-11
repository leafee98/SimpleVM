#pragma once

#include "share/bitdef.h"
#include <filesystem>
#include <string>
#include <fstream>
#include <regex>
#include <vector>

namespace compiler {

    // extern share::bitdef bitdef;
    using share::bitdef;

    struct line_tag {
        static const int NONE;
        static const int COMMENT;
        static const int IDENTIFIER;
        static const int NOPARAM_OP;
        static const int LOGIC_OP;
        static const int DIGIT_OP;
    };

    struct line_regex {
        static const std::regex identifier;
        static const std::regex noparam;
        static const std::regex logic;
        static const std::regex digit;
    };

    std::string & trim_str(std::string & s);

    bool check_permission(std::string source_file, std::string & err_msg);

    bool check_syntax(std::string source_file, std::vector<int> & line_tags,
            std::string & err_msg);

    bool compile(std::string source_file, std::string target_file,
            const std::vector<int> & line_tags, std::string & err_msg);

    void decompile(std::string target_file, std::string source_file);
}
