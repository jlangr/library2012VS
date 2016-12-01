#include "NameNormalizer.h"
#include "StringUtil.h"

#include <string>
#include <vector>
#include <list>
#include <sstream>
#include <iostream>
#include <algorithm>

using namespace std;
using namespace stringutil;

string NameNormalizer::Normalize(const string& inputName)
{
    string suffix{""};
    if (count(inputName.begin(), inputName.end(), ',') > 1)
        throw InvalidNameException();

    size_t indexOfComma{ inputName.find(",") };
    string name{ indexOfComma != string::npos ? inputName.substr(0, indexOfComma) : inputName };

    vector<string> parts = split(trim(name), ' ');
    if (1 == parts.size())
        return name;

    list<string> partsList(parts.begin(), parts.end());

    string lastName = partsList.back();
    partsList.pop_back();
    string firstName = partsList.front();
    partsList.pop_front();

    return lastName + ", " + firstName + Initials(partsList) + Suffix(inputName, indexOfComma);
}

string NameNormalizer::Suffix(const string& name, size_t indexOfComma)
{
    return (indexOfComma == string::npos) ? "" : name.substr(indexOfComma);
}

string NameNormalizer::Initials(list<string> nameParts)
{
    stringstream s;
    for (auto namePart : nameParts)
        s << ' ' << Initial(namePart);
    return s.str();
}

string NameNormalizer::Initial(const string& namePart)
{
    if (namePart.length() == 1)
        return namePart;
    stringstream s;
    s << namePart[0] << ".";
    return s.str();
}
