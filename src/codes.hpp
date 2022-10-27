#pragma once

#include <map>
#include <string>

typedef unsigned char BYTE;

std::map<std::string, BYTE>registers = {
    // 8-bit
    {"ah", 1},
    {"al", 1},
    {"ch", 1},
    {"cl", 1},
    {"dh", 1},
    {"dl", 1},
    {"bh", 1},
    {"bl", 1},
    {"spl", 1},
    {"bpl", 1},
    {"sil", 1},
    {"dil", 1},

    // 16-bit
    {"ax", 2},
    {"cx", 2},
    {"dx", 2},
    {"bx", 2},
    {"sp", 2},
    {"bp", 2},
    {"si", 2},
    {"di", 2},

    // 32-bit
    {"eax", 4},
    {"ecx", 4},
    {"edx", 4},
    {"ebx", 4},
    {"esp", 4},
    {"ebp", 4},
    {"esi", 4},
    {"edi", 4},

    // 64-bit
    {"rax", 8},
    {"rcx", 8},
    {"rdx", 8},
    {"rbx", 8},
    {"rsp", 8},
    {"rbp", 8},
    {"rsi", 8},
    {"rdi", 8}
};

struct OP
{
    std::string opcode;
    std::string reg; // register
    
    bool operator<(const OP &other) const
    {
        return (opcode < other.opcode || reg < other.reg);
    }

    bool operator>(const OP &other) const
    {
        return (opcode > other.opcode || reg > other.reg);
    }

    bool operator==(const OP &other) const
    {
        return (opcode == other.opcode && reg == other.reg);
    }
};

std::map<std::pair<std::string, std::string>, std::vector<BYTE>>opcodes = {
    {{"add", "al"}, {0x04}},
    {{"add", "ah"}, {0x80, 0xc4}},
    {{"add", "ax"}, {0x05}},
    {{"add", "eax"}, {0x05}},

    {{"mov", "al"}, {0xb0}},
    {{"mov", "cl"}, {0xb1}},
    {{"mov", "dl"}, {0xb2}},
    {{"mov", "bl"}, {0xb3}},

    {{"mov", "ah"}, {0xb4}},
    {{"mov", "ch"}, {0xb5}},
    {{"mov", "dh"}, {0xb6}},
    {{"mov", "bh"}, {0xb7}},

    {{"mov", "ax"}, {0xb8}},
    {{"mov", "cx"}, {0xb9}},
    {{"mov", "dx"}, {0xba}},
    {{"mov", "bx"}, {0xbb}},
    
    {{"mov", "sp"}, {0xbc}},
    {{"mov", "bp"}, {0xbd}},
    {{"mov", "si"}, {0xbe}},
    {{"mov", "di"}, {0xbf}},

    {{"jmp", ""}, {0xeb}},

    {{"jmp", "ax"}, {0xff, 0xe0}},
    {{"jmp", "cx"}, {0xff, 0xe1}},
    {{"jmp", "dx"}, {0xff, 0xe2}},
    {{"jmp", "bx"}, {0xff, 0xe3}},

    {{"jmp", "sp"}, {0xff, 0xe4}},
    {{"jmp", "bp"}, {0xff, 0xe5}},
    {{"jmp", "si"}, {0xff, 0xe6}},
    {{"jmp", "di"}, {0xff, 0xe7}},

    {{"jmp", "eax"}, {0x66, 0xff, 0xe0}},
    {{"jmp", "ecx"}, {0x66, 0xff, 0xe1}},
    {{"jmp", "edx"}, {0x66, 0xff, 0xe2}},
    {{"jmp", "ebx"}, {0x66, 0xff, 0xe3}},

    {{"jmp", "esp"}, {0x66, 0xff, 0xe4}},
    {{"jmp", "ebp"}, {0x66, 0xff, 0xe5}},
    {{"jmp", "esi"}, {0x66, 0xff, 0xe6}},
    {{"jmp", "edi"}, {0x66, 0xff, 0xe7}},

    {{"je", ""}, {0x74}},
    {{"jne", ""}, {0x75}},
    {{"jbe", ""}, {0x76}},
    {{"ja", ""}, {0x77}},
    {{"js", ""}, {0x78}},
    {{"jns", ""}, {0x79}},
    {{"jp", ""}, {0x7a}},
    {{"jnp", ""}, {0x7b}},

    {{"jl", ""}, {0x7c}},
    {{"jge", ""}, {0x7d}},
    {{"jle", ""}, {0x7e}},

    {{"jg", ""}, {0x7f}},

    {{"cmp", "al"}, {0x3c}},
    {{"cmp", "cl"}, {0x80, 0xf9}},
    {{"cmp", "dl"}, {0x80, 0xfa}},
    {{"cmp", "bl"}, {0x80, 0xfb}},

    {{"cmp", "ah"}, {0x80, 0xfc}},
    {{"cmp", "ch"}, {0x80, 0xfd}},
    {{"cmp", "dh"}, {0x80, 0xfe}},
    {{"cmp", "bh"}, {0x80, 0xff}},

    {{"cmp", "ax"}, {0x3d}},
    {{"cmp", "cx"}, {0x81, 0xf9}},
    {{"cmp", "dx"}, {0x81, 0xfa}},
    {{"cmp", "bx"}, {0x81, 0xfb}},

    {{"cmp", "sp"}, {0x81, 0xfc}},
    {{"cmp", "bp"}, {0x81, 0xfd}},
    {{"cmp", "si"}, {0x81, 0xfe}},
    {{"cmp", "di"}, {0x81, 0xff}},

    {{"cmp", "eax"}, {0x66, 0x3d}},
    {{"cmp", "ecx"}, {0x66, 0x81, 0xf9}},
    {{"cmp", "edx"}, {0x66, 0x81, 0xfa}},
    {{"cmp", "ebx"}, {0x66, 0x81, 0xfb}},

    {{"cmp", "esp"}, {0x66, 0x81, 0xfc}},
    {{"cmp", "ebp"}, {0x66, 0x81, 0xfd}},
    {{"cmp", "esi"}, {0x66, 0x81, 0xfe}},
    {{"cmp", "edi"}, {0x66, 0x81, 0xff}},
};
