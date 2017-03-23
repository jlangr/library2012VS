#include "Rental.h"
#include "Movie.h"

Rental::Rental(const Movie& movie, int daysRented)
	: mMovie(movie)
	, mDaysRented(daysRented)
{
}

Rental::~Rental()
{
}

double Rental::Fee() const
{
	return movie().Fee(daysRented());
}

int Rental::daysRented() const
{
	return mDaysRented;
}

const Movie& Rental::movie() const
{
	return mMovie;
}
