#pragma once

#include <string>

class Portfolio
{
public:
	bool IsEmpty() const 
	{
		return _isEmpty;
	}

	void Purchase(const std::string& symbol, unsigned int shares)
	{
		_shares = shares;
		_isEmpty = false;
	}

	unsigned int Shares(const std::string& symbol)
	{
		return _shares;
	}

private:
	unsigned int _shares{ 0 };
	bool _isEmpty{ true };
};
