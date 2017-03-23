#pragma once

#include "Movie.h"

class Rental
{
public:
	explicit Rental(const Movie& movie, int daysRented);
	virtual ~Rental();
	int daysRented() const;
	const Movie& movie() const;
	double Fee() const;

private:
	Movie mMovie;
	int mDaysRented;
};

