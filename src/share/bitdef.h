#pragma once

#include <string>
#include <map>
#include <set>

enum ins {
     PUSH   = 0x05,
     DUP    = 0x06,
     POP    = 0x07,

     ADD    = 0X09,
     SUB    = 0X0a,
     MULTI  = 0X0b,
     DIV    = 0X0c,
     MOD    = 0x0d,

     IF     = 0X11,
     IFNO   = 0X10,

     NOP    = 0X01,
     HALT   = 0X00
};


extern std::map<std::string, uint8_t> insmap;
extern std::set<std::string> ins_no_opnum;
extern std::set<std::string> ins_single_opnum;

void init_opnum();
void init_insmap();

extern const std::string _push;
extern const std::string _dup;
extern const std::string _pop;

extern const std::string _add;
extern const std::string _sub;
extern const std::string _multi;
extern const std::string _div;
extern const std::string _mod;

extern const std::string _if;
extern const std::string _ifno;

extern const std::string _nop;
extern const std::string _halt;
