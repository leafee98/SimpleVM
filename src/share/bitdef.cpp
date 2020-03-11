#include "bitdef.h"

namespace share {
    void init() {
        //enum_bit::init();
        // enum_opname::init();
        bitdef::init();
    }

    // void enum_bit::init() {
        const uint8_t enum_bit::NOP       = 0x01;
        const uint8_t enum_bit::HALT      = 0x00;

        const uint8_t enum_bit::REGA      = 0x10;
        const uint8_t enum_bit::REGB      = 0x11;
        const uint8_t enum_bit::REGC      = 0x12;

        const uint8_t enum_bit::LOADA     = 0x14;
        const uint8_t enum_bit::LOADB     = 0x15;
        const uint8_t enum_bit::LOADC     = 0x16;

        const uint8_t enum_bit::READ      = 0x24;
        const uint8_t enum_bit::PUSH      = 0x25;
        const uint8_t enum_bit::DUP       = 0x26;
        const uint8_t enum_bit::POP       = 0x27;

        const uint8_t enum_bit::IF        = 0x31;
        const uint8_t enum_bit::IFNO      = 0x30;

        const uint8_t enum_bit::ADD       = 0x40;
        const uint8_t enum_bit::SUB       = 0x41;
        const uint8_t enum_bit::MULTI     = 0x42;
        const uint8_t enum_bit::DIV       = 0x43;
        const uint8_t enum_bit::MOD       = 0x44;
    // };

    // struct enum_opname {
    //     static const std::string NOP;
    //     static const std::string HALT;

    //     static const std::string REGA;
    //     static const std::string REGB;
    //     static const std::string REGC;

    //     static const std::string LOADA;
    //     static const std::string LOADB;
    //     static const std::string LOADC;

    //     static const std::string READ;
    //     static const std::string PUSH;
    //     static const std::string DUP;
    //     static const std::string POP;

    //     static const std::string IF;
    //     static const std::string IFNO;

    //     static const std::string ADD;
    //     static const std::string SUB;
    //     static const std::string MULTI;
    //     static const std::string DIV;
    //     static const std::string MOD;  
    // };

    // void enum_opname::init() {
        const std::string enum_opname::NOP       = "NOP";
        const std::string enum_opname::HALT      = "HALT";

        const std::string enum_opname::REGA      = "REGA";
        const std::string enum_opname::REGB      = "REGB";
        const std::string enum_opname::REGC      = "REGC";

        const std::string enum_opname::LOADA     = "LOADA";
        const std::string enum_opname::LOADB     = "LOADB";
        const std::string enum_opname::LOADC     = "LOADC";

        const std::string enum_opname::READ      = "READ";
        const std::string enum_opname::PUSH      = "PUSH";
        const std::string enum_opname::DUP       = "DUP";
        const std::string enum_opname::POP       = "POP";

        const std::string enum_opname::IF        = "IF";
        const std::string enum_opname::IFNO      = "IFNO";

        const std::string enum_opname::ADD       = "ADD";
        const std::string enum_opname::SUB       = "SUB";
        const std::string enum_opname::MULTI     = "MULTI";
        const std::string enum_opname::DIV       = "DIV";
        const std::string enum_opname::MOD       = "MOD";
    // }

    // const std::string enum_opname::NOP       = "NOP";
    // const std::string enum_opname::HALT      = "HALT";

    // const std::string enum_opname::REGA      = "REGA";
    // const std::string enum_opname::REGB      = "REGB";
    // const std::string enum_opname::REGC      = "REGC";

    // const std::string enum_opname::LOADA     = "LOADA";
    // const std::string enum_opname::LOADB     = "LOADB";
    // const std::string enum_opname::LOADC     = "LOADC";

    // const std::string enum_opname::READ      = "READ";
    // const std::string enum_opname::PUSH      = "PUSH";
    // const std::string enum_opname::DUP       = "DUP";
    // const std::string enum_opname::POP       = "POP";

    // const std::string enum_opname::IF        = "IF";
    // const std::string enum_opname::IFNO      = "IFNO";

    // const std::string enum_opname::ADD       = "ADD";
    // const std::string enum_opname::SUB       = "SUB";
    // const std::string enum_opname::MULTI     = "MULTI";
    // const std::string enum_opname::DIV       = "DIV";
    // const std::string enum_opname::MOD       = "MOD";



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

        bit[enum_opname::IF]    = enum_bit::IF;
        bit[enum_opname::IFNO ] = enum_bit::IFNO;

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

        oneparam_op.insert(enum_opname::IF);
        oneparam_op.insert(enum_opname::IFNO);

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
        if (opname == enum_opname::IF || opname == enum_opname::IFNO)
            return 3;
        return 0;
    }
}