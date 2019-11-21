#include "loan.hh"
#include <iostream>

Loan::Loan(Book* book,
           Person* borrower,
           Date* today):
    book_(book),
    borrower_(borrower),
    date_(new Date(today->getDay(),today->getMonth(),today->getYear())),
    renew_count_(DEFAULT_RENEWAL_AMOUNT)
{

}

Loan::~Loan()
{
   delete date_;
   date_ = nullptr;

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
    return date_<today;
}

bool Loan::renew(){
    if(renew_count_ >= DEFAULT_RENEWAL_AMOUNT){
        return false;
    }else{
        date_->advance_by_loan_length();
        renew_count_ += 1;
        return true;
    }
}
