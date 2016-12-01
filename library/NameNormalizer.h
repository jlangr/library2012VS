#pragma once

#include <string>
#include <exception>

#include "StringUtil.h"

class InvalidNameException : public std::exception {};

class NormalizedName
{
public:
    NormalizedName(const std::string& name)
    {
    }

    ~NormalizedName() {}

    std::string AsString()
    {
        return "wha?";
    }
};