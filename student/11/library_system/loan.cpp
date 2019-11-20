#include "loan.hh"
#include <iostream>

Loan::Loan(Book* book,
           Person* borrower,
           Date* date):
    book_(book),
    borrower_(borrower),
    date_(date)
{

}

Loan::~Loan()
{

}

std::string Loan::get_book() const{
    return book_->get_title();
}

std::string Loan::get_borrower() const{
    return borrower_->get_name();
}

std::string Loan::get_due() const{
    return date_->to_string();
}

bool Loan::is_late(Date* today) const{
    return date_>today;
}
