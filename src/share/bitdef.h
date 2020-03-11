#pragma once

#include <iostream>
#include <string>
#include <map>
#include <set>

namespace share {
    void init();

    class enum_bit {
        public:
            static const uint8_t NOP       ;
            static const uint8_t HALT      ;

            static const uint8_t REGA      ;
            static const uint8_t REGB      ;
            static const uint8_t REGC      ;

            static const uint8_t LOADA     ;
            static const uint8_t LOADB     ;
            static const uint8_t LOADC     ;

            static const uint8_t READ      ;
            static const uint8_t PUSH      ;
            static const uint8_t DUP       ;
            static const uint8_t POP       ;

            static const uint8_t IF        ;
            static const uint8_t IFNO      ;

            static const uint8_t ADD       ;
            static const uint8_t SUB       ;
            static const uint8_t MULTI     ;
            static const uint8_t DIV       ;
            static const uint8_t MOD       ;

            // static void init();
    };

    class enum_opname {
        public:
            static const std::string NOP;
            static const std::string HALT;

            static const std::string REGA;
            static const std::string REGB;
            static const std::string REGC;

            static const std::string LOADA;
            static const std::string LOADB;
            static const std::string LOADC;

            static const std::string READ;
            static const std::string PUSH;
            static const std::string DUP;
            static const std::string POP;

            static const std::string IF;
            static const std::string IFNO;

            static const std::string ADD;
            static const std::string SUB;
            static const std::string MULTI;
            static const std::string DIV;
            static const std::string MOD;  

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