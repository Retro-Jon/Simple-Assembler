#include "translator.hpp"
#include <iostream>
#include <string>
#include <iomanip>
#include "codes.hpp"

translator::translator(){}

translator::~translator(){}

std::vector<std::string> translator::SeparateCodes(const std::string source) const
{
    std::stringstream source_stream(source);
    std::vector<std::string> res;
    std::string line;

    while (std::getline(source_stream, line))
    {
        res.push_back(line + '\n');
    }

    return res;
}

std::vector<BYTE> translator::GetCode(const std::string code) const
{
    static int TotalBytes = 0;

    std::vector<BYTE> values;

    std::vector<std::string> ops;

    std::string current;
    int byte_start;
    bool hex_num = false;

    int num_bytes = 0;

    for (char c : code)
    {
        if ((c == ',' || c == '\n' || c == ' ') && current != "")
        {
            if (hex_num) current = std::to_string(std::stoi(current, 0, 16));

            if (num_bytes > 0)
            {
                ops.insert(ops.begin() + byte_start, current);
            } else {
                ops.push_back(current);
            }
            
            if (num_bytes > 0) num_bytes--;
            if (num_bytes == 0) byte_start = 0;

            if (registers.find(current) != registers.end())
            {
                num_bytes = registers.at(current);
                byte_start = ops.size();
            }

            if (c == '\n')
            {
                for (num_bytes; num_bytes > 0; num_bytes--)
                {
                    ops.push_back("0");
                }
            }
            
            current = "";
            hex_num = false;
        
        } else if (c != ' ')
        {
            if (current == "0x")
            {
                hex_num = true;
                current = "";
            }

            current += c;
        }
    }
    
    struct OP o = (OP){.opcode = ops[0], .reg = ops[1]};

    // Register not found
    bool reg_found = (registers.find(o.reg) != registers.end());

    o.reg = reg_found ? o.reg : ""; // if reg_found == true: o.reg = o.reg; else: o.reg = "";

    // std::cout << o.opcode << " : " << o.reg << " : " << ((opcodes.find(std::pair<std::string, std::string>(o.opcode, o.reg)) != opcodes.end()) ? "Yay" : "Nope") << std::endl;
    
    if (opcodes.find(std::pair<std::string, std::string>(o.opcode, o.reg)) != opcodes.end())
    {
        for (BYTE b : opcodes.at(std::pair<std::string, std::string>(o.opcode, o.reg)))
        {
            values.push_back(b);
            TotalBytes++;
        }

        // if reg_found == true: d = 2; else: d = 1;
        for (int d = reg_found ? 2 : 1; d < ops.size(); d++)
        {
            if (o.opcode == "jmp" || o.opcode == "je" || o.opcode == "jg" || o.opcode == "jl")
            {
                if (!reg_found)
                {
                    if (ops[1] == "$")
                        values.push_back(0xff - (BYTE)TotalBytes);
                    else if (ops[1].find("0x"))
                        values.push_back((0xff - (BYTE)TotalBytes) + (BYTE)std::stoi(ops[1]));
                }
                break;
            } else if (ops[d] == "$")
            {
                values.push_back((BYTE)TotalBytes);
            } else {
                values.push_back((BYTE)std::stoi(ops[d]));
            }
            
            TotalBytes++;
        }
    }

    return values;
}
