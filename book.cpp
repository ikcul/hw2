#include <sstream>
#include <iomanip>
#include "product.h"
#include "book.h"
#include "util.h"

using namespace std;

Book::Book(const std::string name, double price, int qty, std::string ISBN, const std::string author):
    Product("book", name, price, qty), author_(author), ISBN_(ISBN)
    {
    }
Book::~Book(){

}

/**
 * Returns the appropriate keywords that this product should be associated with
 */
std::set<std::string> Book::keywords() const{
    std::string temp = "";

    temp +=  name_ + " " + ISBN_ + " " + author_;
    
    return parseStringToWords(temp);
}

/**
 * Allows for a more detailed search beyond simple keywords
 */
bool Book::isMatch(std::vector<std::string>& searchTerms) const{
    return false;
}

/**
 * Returns a string to display the product info for hits of the search
 */
std::string Book::displayString() const{
    std::string display = name_ + "\n" + 
                "Author: " + author_ + " ISBN: " + ISBN_ + "\n" + 
                to_string(price_) + " " + to_string(qty_) + " left.";
    return display;
}

/**
 * Outputs the product info in the database format
 */
void Book::dump(std::ostream& os) const{
    os << "book" << "\n";
    os << name_ << "\n";
    os << price_ << "\n";
    os << qty_ << "\n";
    os << ISBN_ << "\n";
    os << author_ << "\n";
}