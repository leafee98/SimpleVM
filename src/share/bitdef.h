#pragma once

#include <iostream>
#include <string>
#include <map>
#include <set>

namespace share {
    void init();

    class enum_bit {
        public:
            inline static const uint8_t NOP       = 0x01;
            inline static const uint8_t HALT      = 0x00;

            inline static const uint8_t REGA      = 0x10;
            inline static const uint8_t REGB      = 0x11;
            inline static const uint8_t REGC      = 0x12;

            inline static const uint8_t LOADA     = 0x14;
            inline static const uint8_t LOADB     = 0x15;
            inline static const uint8_t LOADC     = 0x16;

            inline static const uint8_t READ      = 0x24;
            inline static const uint8_t PUSH      = 0x25;
            inline static const uint8_t DUP       = 0x26;
            inline static const uint8_t POP       = 0x27;


            inline static const uint8_t JMP       = 0x30;
            inline static const uint8_t IF        = 0x31;
            inline static const uint8_t IFNO      = 0x32;

            inline static const uint8_t ADD       = 0x40;
            inline static const uint8_t SUB       = 0x41;
            inline static const uint8_t MULTI     = 0x42;
            inline static const uint8_t DIV       = 0x43;
            inline static const uint8_t MOD       = 0x44;

            // static const uint8_t NOP       ;
            // static const uint8_t HALT      ;

            // static const uint8_t REGA      ;
            // static const uint8_t REGB      ;
            // static const uint8_t REGC      ;

            // static const uint8_t LOADA     ;
            // static const uint8_t LOADB     ;
            // static const uint8_t LOADC     ;

            // static const uint8_t READ      ;
            // static const uint8_t PUSH      ;
            // static const uint8_t DUP       ;
            // static const uint8_t POP       ;

            // static const uint8_t IF        ;
            // static const uint8_t IFNO      ;

            // static const uint8_t ADD       ;
            // static const uint8_t SUB       ;
            // static const uint8_t MULTI     ;
            // static const uint8_t DIV       ;
            // static const uint8_t MOD       ;

            // static void init();
    };

    class enum_opname {
        public:
            inline static const std::string NOP       = "NOP";
            inline static const std::string HALT      = "HALT";

            inline static const std::string REGA      = "REGA";
            inline static const std::string REGB      = "REGB";
            inline static const std::string REGC      = "REGC";

            inline static const std::string LOADA     = "LOADA";
            inline static const std::string LOADB     = "LOADB";
            inline static const std::string LOADC     = "LOADC";

            inline static const std::string READ      = "READ";
            inline static const std::string PUSH      = "PUSH";
            inline static const std::string DUP       = "DUP";
            inline static const std::string POP       = "POP";

            inline static const std::string JMP       = "JMP";
            inline static const std::string IF        = "IF";
            inline static const std::string IFNO      = "IFNO";

            inline static const std::string ADD       = "ADD";
            inline static const std::string SUB       = "SUB";
            inline static const std::string MULTI     = "MULTI";
            inline static const std::string DIV       = "DIV";
            inline static const std::string MOD       = "MOD";

            // static const std::string NOP;
            // static const std::string HALT;

            // static const std::string REGA;
            // static const std::string REGB;
            // static const std::string REGC;

            // static const std::string LOADA;
            // static const std::string LOADB;
            // static const std::string LOADC;

            // static const std::string READ;
            // static const std::string PUSH;
            // static const std::string DUP;
            // static const std::string POP;

            // static const std::string IF;
            // static const std::string IFNO;

            // static const std::string ADD;
            // static const std::string SUB;
            // static const std::string MULTI;
            // static const std::string DIV;
            // static const std::string MOD;  

            // static void init();
    };

    class bitdef {
        private:
            static std::map<std::string, uint8_t> bit;
            static std::map<uint8_t, std::string> opname;
            static std::set<std::string> noparam_op;
            static std::set<std::string> oneparam_op;

        public:
            static void init();
            static uint8_t getbit(const std::string & opname);
            static std::string getopname(uint8_t bit);

            // return 0 if not a valid operation,
            // 1 if without any parameter,
            // 2 if a digit parameter is required.
            // 3 if a identifier parameter is required.
            static int validate_opname(const std::string & opname);
    };
}