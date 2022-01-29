#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <unordered_set>
#include "Validator.h"
#include "CleanHTML.h"

using namespace std;

int main()
{
  
    cout << "Enter file path:" << endl;
    string path;
    cin >> path;
    std::ifstream html_stream(path);
    CleanHTML h;
    const std::string html_string = h.condense(html_stream);
    Validator v;
    const bool html_valid = v.validate(html_string);
    cout << "Checking the file :" << endl;

    // Выводит строку
    std::cout << html_string << '\n' << std::endl;

    if (html_valid)
        std::cout << "Valid HTML!" << std::endl;
    else
        std::cout << "Invalid HTML..." << std::endl;
}

