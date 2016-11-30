#include "StringUtil.h"

#include <string>
#include <vector>

using namespace std;

StringUtil::StringUtil()
{
}


StringUtil::~StringUtil()
{
}

/* static */ vector<string> StringUtil::split(const string &text, char sep) {
    vector<string> tokens;
    size_t start = 0, end = 0;
    while ((end = text.find(sep, start)) != string::npos) {
        tokens.push_back(text.substr(start, end - start));
        start = end + 1;
    }
    tokens.push_back(text.substr(start));
    return tokens;
}