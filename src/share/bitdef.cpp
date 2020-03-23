#include "bitdef.h"

namespace share {
    void init() {
        //enum_bit::init();
        // enum_opname::init();
        bitdef::init();
    }

    std::map<std::string, uint8_t> bitdef::bit;
    std::map<uint8_t, std::string> bitdef::opname;
    std::set<std::string> bitdef::noparam_op;
    std::set<std::string> bitdef::oneparam_op;

    void bitdef::init() {
        bit[enum_opname::NOP]   = enum_bit::NOP;
        bit[enum_opname::HALT]  = enum_bit::HALT;

        bit[enum_opname::REGA]  = enum_bit::REGA;
        bit[enum_opname::REGB]  = enum_bit::REGB;
        bit[enum_opname::REGC]  = enum_bit::REGC;
        
        bit[enum_opname::LOADA] = enum_bit::LOADA;
        bit[enum_opname::LOADB] = enum_bit::LOADB;
        bit[enum_opname::LOADC] = enum_bit::LOADC;

        bit[enum_opname::READ]  = enum_bit::READ;
        bit[enum_opname::PUSH]  = enum_bit::PUSH;
        bit[enum_opname::DUP]   = enum_bit::DUP;
        bit[enum_opname::POP]   = enum_bit::POP;

        bit[enum_opname::JMP]   = enum_bit::JMP;
        bit[enum_opname::IF]    = enum_bit::IF;
        bit[enum_opname::IFNO ] = enum_bit::IFNO;
        bit[enum_opname::IFP]   = enum_bit::IFP;

        bit[enum_opname::ADD]   = enum_bit::ADD;
        bit[enum_opname::SUB]   = enum_bit::SUB;
        bit[enum_opname::MULTI] = enum_bit::MULTI;
        bit[enum_opname::DIV]   = enum_bit::DIV;
        bit[enum_opname::MOD]   = enum_bit::MOD;

        noparam_op.insert(enum_opname::NOP);
        noparam_op.insert(enum_opname::HALT);

        noparam_op.insert(enum_opname::REGA);
        noparam_op.insert(enum_opname::REGB);
        noparam_op.insert(enum_opname::REGC);

        noparam_op.insert(enum_opname::LOADA);
        noparam_op.insert(enum_opname::LOADB);
        noparam_op.insert(enum_opname::LOADC);

        noparam_op.insert(enum_opname::READ);
        oneparam_op.insert(enum_opname::PUSH);
        noparam_op.insert(enum_opname::DUP);
        noparam_op.insert(enum_opname::POP);

        oneparam_op.insert(enum_opname::JMP);
        oneparam_op.insert(enum_opname::IF);
        oneparam_op.insert(enum_opname::IFNO);
        oneparam_op.insert(enum_opname::IFP);

        noparam_op.insert(enum_opname::ADD);
        noparam_op.insert(enum_opname::SUB);
        noparam_op.insert(enum_opname::MULTI);
        noparam_op.insert(enum_opname::DIV);
        noparam_op.insert(enum_opname::MOD);

        for (std::map<std::string, uint8_t>::iterator 
                it = bit.begin(); it != bit.end(); ++it) {
            opname[it->second] = it->first;
        }
    }


    uint8_t bitdef::getbit(const std::string & opname) {
        return bit[opname];
    }

    std::string bitdef::getopname(uint8_t bit) {
        return opname[bit];
    }

    int bitdef::validate_opname(const std::string & opname) {
        if (noparam_op.count(opname))
            return 1;
        if (opname == enum_opname::PUSH)
            return 2;
        if (opname == enum_opname::IF 
            || opname == enum_opname::IFNO
            || opname == enum_opname::IFP
            || opname == enum_opname::JMP)
            return 3;
        return 0;
    }
}