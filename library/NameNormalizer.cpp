#include "NameNormalizer.h"
#include "StringUtil.h"

#include <string>
#include <vector>

using namespace std;
using namespace stringutil;

/* static */ string NameNormalizer::Normalize(const string& name)
{
    vector<string> parts = split(trim(name), ' ');
    if (1 == parts.size())
        return name;

    return parts[1] + ", " + parts[0];
}
