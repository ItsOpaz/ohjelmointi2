/* Module: Loan
 * ------------
 * Represents one loan in library with relating book, person and date
 * member can return vital information about loan and edit due date of the loan
 * TIE-0220x S2019
 * */
#ifndef LOAN_HH
#define LOAN_HH

#include "person.hh"
#include "book.hh"
#include "date.hh"
#include <string>
#include <vector>

const int DEFAULT_RENEWAL_AMOUNT = 6;

class Loan
{
public:
    Loan(Book* book,
         Person* borrower,
         Date* date
    );
    ~Loan();
    
    //returns book title that is loaned
    std::string get_book() const;
    
    //return borrower name related to loan
    std::string get_borrower() const;

    //return due date of the loan
    std::string get_due() const;

    //return true if loan is late
    bool is_late(Date* today) const;

    //returns false if all renews are used, else adds to due date and returns true
    bool renew();


private:
    //pointer to book related to loan
    Book* book_;
    //pointer to person realted to loan
    Person* borrower_;
    //due date, accuired from today member and made to own mamber
    Date* date_;
    //how many renews loan has available
    int renew_count_;
};

#endif // LOAN_HH
