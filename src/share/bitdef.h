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

const std::string _push = "PUSH";
const std::string _dup  = "DUP";
const std::string _pop  = "POP";

const std::string _add  = "ADD";
const std::string _sub  = "SUB";
const std::string _multi = "MULTI";
const std::string _div  = "DIV";
const std::string _mod  = "MOD";

const std::string _if   = "IF";
const std::string _ifno = "IFNO";

const std::string _nop  = "NOP";
const std::string _halt = "HALT";

std::map<std::string, uint8_t> insmap;

// call this function before use opmap
void init_insmap() {
    insmap[_push ] = PUSH;
    insmap[_dup  ] = DUP;
    insmap[_pop  ] = POP;

    insmap[_add  ] = ADD;
    insmap[_sub  ] = SUB;
    insmap[_multi] = MULTI;
    insmap[_div  ] = DIV;
    insmap[_mod  ] = MOD;

    insmap[_if   ] = IF;
    insmap[_ifno ] = IFNO;

    insmap[_nop  ] = NOP;
    insmap[_halt ] = HALT;
}

std::set<std::string> ins_no_opnum;
std::set<std::string> ins_single_opnum;

void init_opnum() {
     ins_single_opnum.emplace(_push);
     ins_no_opnum.emplace(_dup);
     ins_no_opnum.emplace(_pop);

     ins_no_opnum.emplace(_add);
     ins_no_opnum.emplace(_sub);
     ins_no_opnum.emplace(_multi);
     ins_no_opnum.emplace(_div);
     ins_no_opnum.emplace(_mod);

     ins_single_opnum.emplace(_if);
     ins_single_opnum.emplace(_ifno);

     ins_no_opnum.emplace(_nop);
     ins_no_opnum.emplace(_halt);
}