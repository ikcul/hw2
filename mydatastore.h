//smth smth
#ifndef MYDATAcSTORE_H
#define MYDATASTORE_H
#include "datastore.h"
#include "product.h"
#include "user.h"
#include "book.h"
#include "clothing.h"
#include "movie.h"
#include <vector>
#include <map>
#include <string>
#include <set>

class MyDataStore : public DataStore{
public:
    MyDataStore();
    virtual ~MyDataStore();

    void addUser(User* user);
    void addProduct(Product* product);
    std::vector<Product*> search(std::vector<std::string>& terms, int type);
    void dump(std::ostream& ofile);

    void addToCart(const std::string& username, int hitIdx);
    void viewCart(const std::string& username);
    void buyCart(const std::string& username);

private:
    std::vector<Product*> products;
    std::vector<Product*> lastHits;
    std::map<std::string, std::set<Product*>> keyToProducts;
    std::map<std::string, User*> users;
    std::map<std::string, std::vector<Product*>> userCart;
};

#endif