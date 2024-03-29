#include "abstractcard.h"



Card::Card(std::string n, std::string d, std::string b64U, unsigned int c , bool status): name(n), description(d), b64Url(b64U), cost(c), save(status) {}

std::string Card::getName() const{ return name;}
std::string Card::getDescription() const{ return description;}
std::string Card::getUrl() const{ return b64Url;}
unsigned int Card::getCost() const {return cost;}

bool Card::get_status() const {return save;}

bool Card::operator==(const Card& c) const{
    return c.name == name && c.description == description;
}

Json::Value Card::serialize() const {
    Json::Value json;
    json["save"] = save;
    json["name"] = name;
    json["description"] = description;
    json["b64url"] = b64Url;
    json["cost"] = cost;


    return json;
}

Card::~Card() {
    if(!save){
        std::string imgPath = b64Url;

        std::string searchString = "Card";
        size_t lastSlashPos = imgPath.find_last_of('/');
        size_t secondLastSlashPos = imgPath.find_last_of('/', lastSlashPos - 1);
        size_t substringLength = lastSlashPos - secondLastSlashPos - 1;
        size_t index = imgPath.find(searchString, secondLastSlashPos + 1);

        if (index != std::string::npos) {
                imgPath.replace(index, substringLength, "CardImg");
            }

        ::remove(imgPath.c_str());
        ::remove(b64Url.c_str());

    }
}

void Card::set_status(){
    save = 1;
}

//Metodi Visitor


void Card::setName(const std::string& newName) {
        name = newName;
}

void Card::setCost(unsigned int newCost) {
        cost = newCost;
}

void Card::setPath(const std::string& newb64url){
    b64Url = newb64url;
}
