#ifndef ABSTRACTCARD_H
#define ABSTRACTCARD_H
#include <string>
#include <iostream>

#ifdef __has_include
#if __has_include(<jsoncpp/json/json.h>)
#include <jsoncpp/json/json.h>
#elif __has_include(<json/json.h>)
#include <json/json.h>
#endif
#else
#include <json/json.h>
#endif

class Visitor;


class Card{
friend std::ostream& operator<<(std::ostream& os, const Card& c);
private:
    std::string name;
    std::string description;
    std::string b64Url;
    unsigned int cost;
    bool save ;
public:
    Card(std::string n, std::string desc, std::string b64U, unsigned int c , bool save=0);
    virtual Card* clone() const = 0;
    virtual  Json::Value  serialize() const;
    virtual bool operator ==(const Card&) const;
    virtual ~Card();

    //Getter
    std::string getName() const;
    std::string getDescription() const;
    std::string getUrl() const;
    unsigned int getCost() const;
    bool get_status() const ;


    //Setter
    void set_status ();
    void setName(const std::string& newName);
    void setCost(unsigned int newCost);
    void setPath(const std::string& newb64url);

    //Metodi Visitor
    virtual void accept(Visitor *) = 0;

};

#endif // ABSTRACTCARD_H
