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

//#include "../../Ui/Visitor/visitor.h"


class Card{
friend std::ostream& operator<<(std::ostream& os, const Card& c);
private:
    std::string name;
    std::string description;
    std::string b64Url;     //base64 url of the image of the card
    unsigned int cost;      //cost in Mana of the card
    bool save ;
protected:
    virtual std::ostream& print(std::ostream& os) const;
public:
    Card(std::string n, std::string desc, std::string b64U, unsigned int c , bool save=0);
    std::string getName() const;
    std::string getDescription() const;
    std::string getUrl() const;
    unsigned int getCost() const;
    void set_status ();
    bool get_status() const ;
    virtual Card* clone() const = 0;
    virtual  Json::Value  serialize() const;
    virtual bool operator ==(const Card&) const;
    virtual ~Card();
    //virtual void accept(visitor *);

};

#endif // ABSTRACTCARD_H
