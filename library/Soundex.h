#pragma once

#include <map>
#include <string>
#include <sstream>
#include <algorithm>
#include <iostream>

using namespace std; // tsk tsk

class Soundex
{
public:
    const static unsigned int MAX_LENGTH;
    const static string SOFT_SOUNDS;
    const static string SOFT_CONSONANTS;
    const static string VOWELS;

    Soundex(void) 
    {
        InitializeConsonantToDigitTable();
    }
    virtual ~Soundex(void) {}

    // +++ do not change any of these helper methods +++
    char Digit(char consonant) const
    {
        map<char,char>::const_iterator it = consonantIndices.find(consonant);
        if (it == consonantIndices.end())
            return '0';
        return it->second;
    }

    bool IsSoftSound(char letter) const
    {
        return SOFT_SOUNDS.find(letter) != string::npos;
    }

    bool IsSoftConsonant(char letter) const
    {
        return SOFT_CONSONANTS.find(letter) != string::npos;
    }

    bool IsVowel(char letter) const
    {
        return VOWELS.find(letter) != string::npos;
    }
    // ^^^ do not change any of the above helper methods ^^^

    void AppendFirstLetter(stringstream& stream, const string& text) const
    {
        stream << text[0];
    }

    void AppendDigit(stringstream& stream, char letter) const
    {
        stream << Digit(letter);
    }

    void PadWithZeros(stringstream& stream) const
    {
        int zeros = MAX_LENGTH - stream.str().length();
        stream << string(zeros, '0');
    }

    char Last(stringstream& stream) const
    {
        unsigned int length = stream.str().length();
        return stream.str()[length - 1];
    }

    bool IsDuplicateHardSound(stringstream& stream, char letter) const
    {
        if (stream.str().length() < 2)
            return false;
        return Last(stream) == Digit(letter);
    }

    string Convert(const string& text) const
    {
        return string(1, text[0]) + "000";
    }

private:

    map<char,char> consonantIndices;

    void InitializeConsonantToDigitTable()
    {
        consonantIndices['b'] = '1';
        consonantIndices['f'] = '1';
        consonantIndices['p'] = '1';
        consonantIndices['v'] = '1';
        consonantIndices['c'] = '2';
        consonantIndices['g'] = '2';
        consonantIndices['j'] = '2';
        consonantIndices['k'] = '2';
        consonantIndices['q'] = '2';
        consonantIndices['s'] = '2';
        consonantIndices['x'] = '2';
        consonantIndices['z'] = '2';
        consonantIndices['d'] = '3';
        consonantIndices['t'] = '3';
        consonantIndices['l'] = '4';
        consonantIndices['m'] = '5';
        consonantIndices['n'] = '5';
        consonantIndices['r'] = '6';
    }
};
