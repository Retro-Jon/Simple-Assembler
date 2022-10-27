#pragma once
#include <map>
#include <string>
#include <vector>

typedef unsigned char BYTE;

class translator
{
    public:
        translator();
        ~translator();

        std::vector<std::string> SeparateCodes(std::string) const;
        std::vector<BYTE> GetCode(std::string) const;
};