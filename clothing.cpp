#include <sstream>
#include <iomanip>
#include "product.h"
#include "clothing.h"
#include "util.h"

using namespace std;

Clothing::Clothing(const std::string name, double price, int qty, std::string size, const std::string brand):
    Product("clothing", name, price, qty), brand_(brand), size_(size)
    {
    }
Clothing::~Clothing(){

}

/**
 * Returns the appropriate keywords that this product should be associated with
 */
std::set<std::string> Clothing::keywords() const{
    std::string temp = "";

    temp +=  name_ + " " + brand_;
    
    return parseStringToWords(temp);
}

/**
 * Allows for a more detailed search beyond simple keywords
 */
bool Clothing::isMatch(std::vector<std::string>& searchTerms) const{
    return false;
}

/**
 * Returns a string to display the product info for hits of the search
 */
std::string Clothing::displayString() const{
    std::stringstream ss;
    ss << std::fixed << std::setprecision(2);
    ss << name_ << "\n";
    ss << "Size: " << size_ << " Brand: " << brand_ << "\n";
    ss << price_ << " " << qty_ << " left.";
    return ss.str();
}

/**
 * Outputs the product info in the database format
 */
void Clothing::dump(std::ostream& os) const{
    os << "clothing" << "\n";
    os << name_ << "\n";
    os << price_ << "\n";
    os << qty_ << "\n";
    os << size_ << "\n";
    os << brand_ << "\n";
}