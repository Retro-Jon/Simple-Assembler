#pragma once

#include <fstream>
#include <vector>
#include <string>

typedef unsigned char BYTE;

namespace file_loader
{
    void write_bin(const char* path, std::vector<BYTE> &wt);
    std::string load_text(const char* path);
};
