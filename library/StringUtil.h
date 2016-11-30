#pragma once

#include <string>
#include <vector>

class StringUtil
{
public:
    StringUtil();
    ~StringUtil();

    static std::vector<std::string> split(const std::string&, char sep);
};

