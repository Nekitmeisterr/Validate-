#pragma once
#include <iostream>
#include <string>
#include <fstream>

class CleanHTML
{ public :
    std::string condense(std::ifstream& stream)
    {
        std::string file_no_whitespace;

        if (stream.is_open())
        {
            std::string cur_token;
            while (stream >> cur_token)
                file_no_whitespace += cur_token;
        }
        else
            std::cerr << "File is not open!" << std::endl;

        return file_no_whitespace;
    }


};

