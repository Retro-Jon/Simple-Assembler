#include "file.hpp"
#include <iostream>

namespace file_loader
{
    void write_bin(const char* path, std::vector<BYTE> &wt)
    {
        std::fstream file;
        file.open(path, std::ios::out | std::ios::binary);

        for (int i = 0; i < wt.size(); i++)
            file.write((char*) &wt[i], sizeof(BYTE));

        file.close();
    }

    std::string load_text(const char* path)
    {
        std::string data;
        std::fstream file;
        file.open(path);

        if (file.is_open())
        {
            std::string line;

            while (std::getline(file, line))
            {
                data += line + '\n';
            }
            file.close();
        }

        return data;
    }
}