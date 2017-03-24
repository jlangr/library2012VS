#pragma once

#include <string>
#include <exception>

#include "StringUtil.h"

using namespace std;

class InvalidNameException : public exception {};

class NormalizedName
{
public:
    NormalizedName(const string& name)
		: _name(name)
    {
		ThrowIfMoreThanOneComma();
		_name = stringutil::trim(_name);
    }

    ~NormalizedName() {}

    string AsString()
    {
		if (_name.empty()) return "";
		CaptureAndRemoveSuffix();
		SplitNameIntoParts();
		if (IsSinglePartName()) return _name;
		return LastName() + ", " + FirstName() + MiddleInitials() + Suffix();
    }

private:
	void SplitNameIntoParts()
	{
		_nameParts = stringutil::split(_name, ' ');
	}

	bool IsSinglePartName()
	{
		return 1 == _nameParts.size();
	}

	void ThrowIfMoreThanOneComma()
	{
		auto commaCount{count(_name.begin(), _name.end(), ',')};
		if (commaCount > 1)
			throw InvalidNameException{};
	}

	string MiddleInitials()
	{
		stringstream s;
		vector<string> middle{_nameParts.begin() + 1, _nameParts.end() - 1};
		for (auto part : middle)
			s << MiddleInitial(part);
		return s.str();
	}

	void CaptureAndRemoveSuffix()
	{
		if (HasSuffix()) {
			CaptureSuffix();
			RemoveSuffix();
		}
	}

	void CaptureSuffix()
	{
		_suffix = _name.substr(SuffixStart());
	}

	void RemoveSuffix()
	{
		_name = _name.substr(0, SuffixStart());
	}

	bool HasSuffix()
	{
		return _name.find(',') != string::npos;
	}
	
	size_t SuffixStart()
	{
		return _name.find(',');
	}

	string Suffix()
	{
		return _suffix;
	}

	string MiddleInitial(std::string& name)
	{
		return " " + (1 == name.length() ? name : Initial(name));
	}

	string Initial(std::string& name)
	{
		stringstream s;
		s << name[0] << '.';
		return s.str();
	}

	string LastName()
	{
		return _nameParts.back();
	}

	string FirstName()
	{
		return _nameParts.front(); 
	}

	string _name;
	string _suffix{ "" };
	vector<string> _nameParts;
};