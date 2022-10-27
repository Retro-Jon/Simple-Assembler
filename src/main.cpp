#include <iostream>
#include <iomanip>
#include <vector>
#include "translator.hpp"
#include "file.hpp"

int main(int argc, char** argv)
{
    if (argc > 2)
    {
        std::string source = file_loader::load_text(argv[1]);

        std::vector<BYTE> data;

        translator T;

        for (std::string line : T.SeparateCodes(source))
        {
            for (BYTE b : T.GetCode(line))
            {
                data.push_back(b);
            }
        }

        for (int b : data)
        {
            std::cout << "0x" << std::setfill('0') << std::setw(2) << std::hex << b << std::endl;
        }

        file_loader::write_bin(argv[2], data);
    } else {
        std::cout << "Source file or output path NOT provided..." << std::endl;
    }

    return 0;
}