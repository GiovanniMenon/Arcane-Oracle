#include "abstractcard.h"

int Card::nCardGenerated = 0;

Card::Card(std::string n, std::string d, std::string b64U, unsigned int c , bool status): name(n), description(d), b64Url(b64U), cost(c), save(status), grade(0) ,number(++nCardGenerated) {}

std::string Card::getName() const{ return name;}
std::string Card::getDescription() const{ return description;}
std::string Card::getUrl() const{ return b64Url;}
unsigned int Card::getCost() const {return cost;}
unsigned int Card::getGrade() const {return grade;}
unsigned int Card::getNumber() const {return number;}
bool Card::get_status() const {return save;}


std::ostream& Card::print(std::ostream& os) const {
    os<< "Name: " << name <<std::endl<< "Description: " << description <<std::endl<< "Base64Url: " << b64Url<<std::endl << "Cost: " << cost <<std::endl<< "Grade: " << grade <<std::endl;
    return os;
}

std::ostream& operator<<(std::ostream& os, const Card& c){
    return c.print(os);
}

bool Card::operator==(const Card& c) const{
    return c.name == name && c.description == description && c.b64Url == b64Url && c.grade == grade && c.cost == cost;
}

Json::Value Card::serialize() const {
    Json::Value json;
    json["save"] = save;
    json["name"] = name;
    json["description"] = description;
    json["b64url"] = b64Url;
    json["grade"] = grade;
    json["cost"] = cost;
    json["card_generated"] = number;

    return json;
}

void Card::init() {
    this->setGrade();
}

Card::~Card() {
    if(!save){
        ::remove(b64Url.c_str());
    }
}

void Card::set_status(){
    save = 1;
}
