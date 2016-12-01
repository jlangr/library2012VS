#pragma once

#include <string>

class NameNormalizer
{
public:
    NameNormalizer() {}
    ~NameNormalizer() {}
    static std::string Normalize(const std::string&);
};