#include <sstream>
#include <iomanip>
#include "product.h"
#include "movie.h"
#include "util.h"

using namespace std;

Movie::Movie(const std::string name, double price, int qty, std::string genre, const std::string rating):
    Product("movie", name, price, qty), genre_(genre), rating_(rating)
    {
    }
Movie::~Movie(){

}

/**
 * Returns the appropriate keywords that this product should be associated with
 */
std::set<std::string> Movie::keywords() const{
    std::string temp = "";

    temp +=  name_ + " " + genre_;
    
    return parseStringToWords(temp);
}

/**
 * Allows for a more detailed search beyond simple keywords
 */
bool Movie::isMatch(std::vector<std::string>& searchTerms) const{
    return false;
}

/**
 * Returns a string to display the product info for hits of the search
 */
std::string Movie::displayString() const{
    std::string display = name_ + "\n" + 
                "Genre: " + genre_ + "\n" + 
                "Rating: " + rating_ + "\n" + 
                "Price: $" + to_string(price_) + "\n" + 
                "Quantity: " + to_string(qty_);
    return display;
}

/**
 * Outputs the product info in the database format
 */
void Movie::dump(std::ostream& os) const{
    os << "movie" << "\n";
    os << name_ << "\n";
    os << price_ << "\n";
    os << qty_ << "\n";
    os << genre_ << "\n";
    os << rating_ << "\n";
}