#pragma once

#include <string>
#include <list>
#include <exception>

class InvalidNameException : public std::exception {};

class NameNormalizer
{
public:
    NameNormalizer() {}
    ~NameNormalizer() {}
    static std::string Normalize(const std::string&);

private:
    static std::string Initial(const std::string&);
    static std::string Initials(std::list<std::string> nameParts);
    static std::string Suffix(const std::string& name, size_t indexOfComma);
};