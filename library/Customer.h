#pragma once

#include <string>
#include <vector>
#include <sstream>
#include <iomanip>

#include "PriceCode.h"
#include "Rental.h"

class Customer
{
public:
	Customer(const std::string& name) : mName(name) {}

	~Customer() {}

	void add(const Rental& rental)
	{
		// points cached in the object for performance reason!
		mTotalFrequentRenterPoints += FrequentRenterPoints(Rental{ rental });
		mRentals.push_back(rental);
	}

	std::string name() const
	{
		return mName;
	}

	std::vector<Rental> rentals() const
	{
		return mRentals;
	}

	std::string statement()
	{
		std::stringstream result;
		ConfigureStream(result);
		AppendHeader(result);
		for (auto rental: mRentals)
			AppendDetail(result, rental);
		AppendFooter(result);
		return result.str();
	}

private:
	void AppendFooter(std::stringstream& result)
	{
		result << "Amount owed is " << TotalRentalFee() << "\n";
		result << "You earned " << TotalFrequentRenterPoints() << " frequent renter points";
	}

	int TotalFrequentRenterPoints()
	{
		return mTotalFrequentRenterPoints;
	}

	double TotalRentalFee() 
	{
		auto totalRentalFee{ 0.0 };
		for (auto rental: mRentals)
			totalRentalFee += rental.Fee();
		return totalRentalFee;
	}

	void AppendDetail(std::stringstream& result, Rental &rental)
	{
		result << "\t" << rental.movie().title() << "\t" << rental.Fee() << "\n";
	}

	int FrequentRenterPoints(Rental& each)
	{
		auto frequentRenterPoints{ 1 };
		// Add bonus for a two-day new release rental
		if ((each.movie().priceCode() == PriceCode::NEW_RELEASE) &&
			 each.daysRented() > 1) 
			frequentRenterPoints++;
		return frequentRenterPoints;
	}

	void ConfigureStream(std::stringstream& result)
	{
		result << std::setprecision(2) << std::fixed << std::showpoint;
	}

	void AppendHeader(std::stringstream& result)
	{
		result << "Rental Record for " << mName << "\n";
	}

	std::vector<Rental> mRentals;
	std::string mName;
	int mTotalFrequentRenterPoints{ 0 };
};
