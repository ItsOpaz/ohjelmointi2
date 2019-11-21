#include "library.hh"
#include <iostream>

// Let's use the date when the project was published as the first date.
Library::Library():
    today_(new Date(13, 11, 2019)),
    books_({}),
    authors_({}),
    accounts_({})
{

}

Library::~Library()
{
    // Free all memory reserved with the keyword new.
    delete today_; today_ = nullptr;
    for ( std::pair<std::string, Book*> book : books_ ){
        delete book.second;
        book.second = nullptr;
    }
    for ( std::pair<std::string, Person*> author : authors_ ){
        delete author.second;
        author.second = nullptr;
    }
    for ( std::pair<std::string, Person*> account : accounts_ ){
        delete account.second;
        account.second = nullptr;
    }
}

void Library::all_books()
{
    for ( std::pair<std::string, Book*> book : books_ ){
        std::cout << book.first << std::endl;
    }
}

void Library::all_books_with_info()
{
    std::cout << SEPARATOR_LINE << std::endl;
    for ( std::pair<std::string, Book*> book : books_ ){
        book.second->print_info();
        std::cout << SEPARATOR_LINE << std::endl;
    }
}

void Library::all_borrowers()
{
    for ( std::pair<std::string, Person*> borrower : accounts_ ){
        std::cout << borrower.first << std::endl;
    }
}

void Library::all_borrowers_with_info()
{
    std::cout << SEPARATOR_LINE << std::endl;
    for ( std::pair<std::string, Person*> borrower : accounts_ ){
        borrower.second->print_info();
        std::cout << SEPARATOR_LINE << std::endl;
    }
}

bool Library::add_book(const std::string &title, const std::vector<std::string> authors, const std::string &description, const std::set<std::string> genres)
{
    if ( authors.empty() ){
        std::cout << MISSING_AUTHOR_ERROR << std::endl;
        return false;
    }
    std::vector<Person*> author_ptrs;
    for ( std::string author : authors ){
        Person* n_person;
        if ( authors_.find(author) == authors_.end() ){
            n_person = new Person(author, "", "");
            authors_.insert({author, n_person});
        } else {
            n_person = authors_.at(author);
        }
        author_ptrs.push_back(n_person);
    }
    Book* n_book = new Book(title, author_ptrs, description, genres);
    books_.insert({title, n_book});
    return true;
}

void Library::add_borrower(const std::string &name, const std::string &email,
                           const std::string &address)
{
    if ( accounts_.find(name) != accounts_.end()){
        std::cout << DUPLICATE_PERSON_ERROR << std::endl;
        return;
    }

    Person* n_person = new Person(name, email, address);
    accounts_.insert({name, n_person});
}

void Library::set_date(int day, int month, int year)
{
    delete today_;
    today_ = new Date(day, month, year);
    today_->show();
}

void Library::advance_date(int days)
{
    today_->advance_by(days);
    today_->show();
}

void Library::loaned_books()
{
    if(loans_.size()==0){

    }else{
        std::cout << LOAN_INFO << std::endl;
        for(long unsigned int i=0; i <= loans_.size()-1; ++i){
            std::cout << loans_.at(i)->get_book() << " : " <<
                         loans_.at(i)->get_borrower() << " : " <<
                         loans_.at(i)->get_due() << " : " <<
                         loans_.at(i)->is_late(today_) << std::endl;
        }
    }
}

void Library::loans_by(const std::string &borrower)
{
    for(Loan* loan : loans_){
        if (loan->get_borrower()==borrower){
            std::cout <<loan->get_book() << " : " <<
                        loan->get_due() << " : " <<
                        loan->is_late(today_) << std::endl;
        }
    }
}

void Library::loan(const std::string &book_title, const std::string &borrower_id)
{
    if(!valid_book(book_title)){
        std::cout <<CANT_FIND_BOOK_ERROR <<std::endl;
    }else if(!valid_person(borrower_id)){
        std::cout <<CANT_FIND_ACCOUNT_ERROR <<std::endl;
    }else if (is_loaned(book_title)){
        std::cout <<ALREADY_LOANED_ERROR <<std::endl;
    }else{
    Loan* new_loan = new Loan(books_.at(book_title),
                              accounts_.at(borrower_id),
                              today_);
    loans_.push_back(new_loan);
    }
}

void Library::renew_loan(const std::string &book_title)
{
    if (!is_loaned(book_title)){
        std::cout <<LOAN_NOT_FOUND_ERROR <<std::endl;
    }else{
        for(Loan* loan : loans_){
            if(loan->get_book()==book_title){
                if(loan->renew()){
                    std::cout <<RENEWAL_SUCCESSFUL <<std::endl;
                }else{
                    std::cout <<OUT_OF_RENEWALS_ERROR <<std::endl;
                }
            }
        }
    }
}

void Library::return_loan(const std::string &book_title)
{
    if (!is_loaned(book_title)){
        std::cout <<LOAN_NOT_FOUND_ERROR <<std::endl;
    }else{
        int i = 0;
        for(Loan* loan:loans_){
            if(loan->get_book()==book_title){
                Loan* returned = loan;
                delete returned;
                loans_.erase(loans_.begin()+i);
                returned = nullptr;
            }else{
                ++i;
            }
        }
        std::cout <<RETURN_SUCCESSFUL <<std::endl;
    }
}

bool Library::valid_book(const std::string &book_title)
{
    if(books_.count(book_title)==0){
        return true;
    }else{
        return false;
    }
}

bool Library::valid_person(const std::string &borrower)
{
    if(accounts_.count(borrower)==0){
        return true;
    }else{
        return false;
    }
}

bool Library::is_loaned(const std::string &book_title)
{
    for(Loan* loan : loans_){
        if(loan->get_book()==book_title){
            return true;
        }else{
            continue;
        }
    }
    return false;
}
