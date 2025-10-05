#include "util.h"
#include "mydatastore.h"
#include "product.h"
#include "book.h"
#include "clothing.h"
#include "movie.h"
struct ProdNameSorter {
    bool operator()(Product* p1, Product* p2) {
        return (p1->getName() < p2->getName());
    }
};
MyDataStore::MyDataStore(){

}

MyDataStore::~MyDataStore(){
    for (Product* p : products){
        delete p;
    }

    for (std::map<std::string, User*>::iterator it = users.begin(); it != users.end(); ++it){
        delete it->second;
    }
}

void MyDataStore::addUser(User* user){
    std::string newUser = convToLower(user->getName());
    users.insert(std::make_pair(newUser, user));
}

void MyDataStore::addProduct(Product* product){
    products.push_back(product);
    std::set<std::string> tempKey = product->keywords();
    for (std::string s : tempKey){
        s = convToLower(s);
        if (keyToProducts.find(s) != keyToProducts.end()){
            keyToProducts[s].insert(product);
        }
        else{
            std::set<Product*> temp = {product};
            keyToProducts.insert(std::make_pair(s, temp));
        }
    }
}

std::vector<Product*> MyDataStore::search(std::vector<std::string>& terms, int type){
    std::string tempString;
    for (std::string& s : terms){
        tempString += s + " ";
    }  
    std::set<std::string> tempTerms = parseStringToWords(tempString);  
    std::vector<std::set<Product*>> hits;
    for (std::set<std::string>::iterator it = tempTerms.begin(); it != tempTerms.end(); ++it){
        std::map<std::string, std::set<Product*>>::iterator tempKeyTerm = keyToProducts.find(*it);
        if (tempKeyTerm != keyToProducts.end()){
            hits.push_back(tempKeyTerm->second);
        }
    }
    std::set<Product*> temp;
    if (type){
        for (std::set<Product*> s : hits){
            temp = setUnion(temp, s);
        }
    }else{
        if (!hits.empty()){
            temp = hits[0];
            for (size_t i = 1; i < hits.size(); i++){
                temp = setIntersection(temp, hits[i]);
            }
        }
    }
    lastHits.clear();
    lastHits.assign(temp.begin(), temp.end());
    std::sort(lastHits.begin(), lastHits.end(), ProdNameSorter());
    return lastHits;
}

void MyDataStore::dump(std::ostream& ofile) {
    ofile << "<products>" << std::endl;
    for (Product* p : products){
        p->dump(ofile);
    }
    ofile << "</products>" << std::endl;

    ofile << "<users>" << std::endl;
    for (std::map<std::string, User*>::iterator it = users.begin(); it != users.end(); ++it){
        it->second->dump(ofile);
    }
    ofile << "</users>" << std::endl;

}

void MyDataStore::addToCart(const std::string& username, int hitIdx){
    std::map<std::string, User*>::iterator aUser = users.find(convToLower(username));
    if (aUser != users.end() && (hitIdx >= 1 && hitIdx <= (int)lastHits.size())){
        if (userCart.find(convToLower(username)) == userCart.end()){
            std::vector<Product*> temp;
            userCart.insert(std::make_pair(convToLower(username), temp));
        }
        userCart[convToLower(username)].push_back(lastHits[hitIdx - 1]);
    }else{
        std::cout << "Invalid request" << std::endl;
    }
}
void MyDataStore::viewCart(const std::string& username){
    std::map<std::string, std::vector<Product*>>::iterator cartIt = userCart.find(convToLower(username));
    if (users.find(convToLower(username)) == users.end()){
        std::cout << "Invalid username" << std::endl;
    }else{
        if (cartIt != userCart.end()) {
            int i = 1;
            for (Product* p : cartIt->second) {
                std::cout << "Item " << i << std::endl;
                std::cout << p->displayString() << std::endl;
                i++;
            }
        }
    }
}
void MyDataStore::buyCart(const std::string& username){
    std::map<std::string, User*>::iterator aUser = users.find(convToLower(username));
    if (aUser != users.end()){
        std::map<std::string, std::vector<Product*>>::iterator tempCart = userCart.find(convToLower(username));
        if (tempCart != userCart.end()){
            std::vector<Product*>::iterator it = tempCart->second.begin();
            while (it != tempCart->second.end()){
                if ((*it)->getQty() > 0 && aUser->second->getBalance() >= (*it)->getPrice()){
                    (*it)->subtractQty(1);
                    aUser->second->deductAmount((*it)->getPrice());
                    it = tempCart->second.erase(it);
                }else{
                    ++it;
                }
            }
        }
    }else{
        std::cout << "Invalid username" << std::endl;
    }
}