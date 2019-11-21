/* Module: Loan
 * ------------
 * This class and its bahaviour should be defined by the student.
 *
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
         Date* date,
    );
    ~Loan();
    
    //returns book that is loaned
    std::string get_book() const;
    
    //return borrower
    std::string get_borrower() const;

    //return due date
    std::string get_due() const;

    //return true if loan is late
    bool is_late(Date* today) const;

    //renew loan
    bool renew();

private:
    Book* book_;
    Person* borrower_;
    Date* date_;
    int renew_count_;
};

#endif // LOAN_HH
