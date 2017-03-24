#pragma once

#include <string>
#include <unordered_map>
#include <numeric>

#include "StockService.h"

using namespace std;

class Portfolio
{
public:
	void SetStockService(StockService* service)
	{
		_stockService = service;
	}

	unsigned int Value() const
	{
		if (IsEmpty())
			return 0;
		//auto total{ 0 };
		//for (auto holding : _holdings) 
		//{
		//	auto symbol{ holding.first };
		//	total += _stockService->CurrentPrice(symbol) * Shares(symbol);
		//}
		//return total;

		return accumulate(_holdings.begin(), _holdings.end(),
			0,
			[&](auto total, auto holding)
		{
		   auto symbol{ holding.first };
		   return total + 
			   _stockService->CurrentPrice(symbol) * Shares(symbol);
		});
	}

	unsigned int Size() const
	{
		return _holdings.size();
	}

	bool IsEmpty() const
	{
		return _holdings.empty();
	}

	void Purchase(const string& symbol, unsigned int shares)
	{
		ThrowOnPurchaseOfZeroShares(shares);
		Add(symbol, shares);
	}

	unsigned int Shares(const string& symbol) const
	{
		return FindWithDefault(_holdings, symbol, 0);
	}

	void Sell(const string& symbol, unsigned int shares)
	{
		ThrowWhenSellingTooMany(symbol, shares);
		Add(symbol, -1 * shares);
		RemoveIfNoSharesLeft(symbol);
	}

private:
	void Add(const string& symbol, int shares)
	{
		_holdings[symbol] = Shares(symbol) + shares;
	}

	void RemoveIfNoSharesLeft(const string& symbol)
	{
		if (0 == Shares(symbol))
			_holdings.erase(symbol);
	}

	void ThrowWhenSellingTooMany(const string& symbol, unsigned int shares) const
	{
		if (shares > Shares(symbol))
			throw exception();
	}

	void ThrowOnPurchaseOfZeroShares(unsigned int shares) const
	{
		if (0 == shares)
			throw exception();
	}

	// TODO this belongs elsewhere
	template<typename T>
	const typename T::mapped_type& FindWithDefault(
		const T& m,
		const typename T::key_type& key,
		const typename T::mapped_type& defaultValue) const
	{
		typename T::const_iterator it = m.find(key);
		if (it == m.end())
			return defaultValue;
		return it->second;
	}

	unordered_map<string, unsigned int> _holdings;
	StockService* _stockService;
};