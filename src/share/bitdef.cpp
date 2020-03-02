#include "bitdef.h"

const std::string _push  = "PUSH";
const std::string _dup   = "DUP";
const std::string _pop   = "POP";

const std::string _add   = "ADD";
const std::string _sub   = "SUB";
const std::string _multi = "MULTI";
const std::string _div   = "DIV";
const std::string _mod   = "MOD";

const std::string _if    = "IF";
const std::string _ifno  = "IFNO";

const std::string _nop   = "NOP";
const std::string _halt  = "HALT";

std::map<std::string, uint8_t> insmap;
std::set<std::string> ins_no_opnum;
std::set<std::string> ins_single_opnum;

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