#include "gmock/gmock.h"

#include <string>

#include "ClassificationData.h"
#include "Book.h"

using namespace std;
using namespace testing;
using namespace ClassificationData;

TEST(BookTest, PopulatesAllFieldsOnConstruction)
{
    Book book("title", "author", 1999, "classification");

    ASSERT_THAT(book.Title(), Eq("title"));
    ASSERT_THAT(book.Author(), Eq("author"));
    ASSERT_THAT(book.Year(), Eq(1999));
    ASSERT_THAT(book.Classification(), Eq("classification"));
    ASSERT_THAT(book.Type(), Eq(Book::TYPE_BOOK));
}

TEST(BookTest, NoArgConstructorInitializesFieldsToDefault)
{
    Book book;

    ASSERT_THAT(book.Title(), Eq(""));
    ASSERT_THAT(book.Author(), Eq(""));
    ASSERT_THAT(book.Year(), Eq(0));
    ASSERT_THAT("", Eq(book.Classification()));
}

TEST(BookTest, AllowsSpecificationOfTypeOnConstruction)
{
    Book book("", "", 0, "", Book::TYPE_MOVIE);

    ASSERT_THAT(book.Type(), Eq(Book::TYPE_MOVIE));
}

TEST(BookTest, IsEqualToCopyConstructedInstance)
{
    Book copy(THE_TRIAL);

    ASSERT_THAT(THE_TRIAL == copy, Eq(true));
}

TEST(BookTest, IsNotEqualWhenTitleDiffers)
{
    Book book(
        THE_TRIAL_TITLE + "x", THE_TRIAL_AUTHOR,
        THE_TRIAL_YEAR, THE_TRIAL_CLASSIFICATION);
    ASSERT_THAT(THE_TRIAL != book, Eq(true));
}

TEST(BookTest, IsNotEqualWhenAuthorDiffers)
{
    Book book(
        THE_TRIAL_TITLE, THE_TRIAL_AUTHOR + "x",
        THE_TRIAL_YEAR, THE_TRIAL_CLASSIFICATION);
    ASSERT_THAT(THE_TRIAL != book, Eq(true));
}

TEST(BookTest, IsNotEqualWhenYearDiffers)
{
    Book book(
        THE_TRIAL_TITLE, THE_TRIAL_AUTHOR,
        THE_TRIAL_YEAR + 1, THE_TRIAL_CLASSIFICATION);
    ASSERT_THAT(THE_TRIAL != book, Eq(true));
}

TEST(BookTest, IsNotEqualWhenClassificationDiffers)
{
    Book book(
        THE_TRIAL_TITLE, THE_TRIAL_AUTHOR,
        THE_TRIAL_YEAR, THE_TRIAL_CLASSIFICATION + "x");
    ASSERT_THAT(THE_TRIAL != book, Eq(true));
}

TEST(BookTest, IsNotEqualWhenTypeDiffers)
{
    Book book6(
        THE_TRIAL_TITLE, THE_TRIAL_AUTHOR,
        THE_TRIAL_YEAR, THE_TRIAL_CLASSIFICATION,
        Book::TYPE_MOVIE);
    ASSERT_THAT(THE_TRIAL != book6, Eq(true));
}

TEST(BookTest, LessThanBasedOnClassification)
{
    string classificationA("A123");
    string classificationB("B123");
    Book a("", "", 0, classificationA);
    Book b("", "", 0, classificationB);

    ASSERT_THAT(a < b, Eq(true));
}
