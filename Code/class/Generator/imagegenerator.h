#ifndef IMAGEGENERATOR_H
#define IMAGEGENERATOR_H

#ifdef __has_include
#if __has_include(<jsoncpp/json/json.h>)
#include <jsoncpp/json/json.h>
#elif __has_include(<json/json.h>)
#include <json/json.h>
#endif
#else
#include <json/json.h>
#endif

#include <string>

class imageGenerator{
private:
    std::string apikey; //api key that is used to generate the calls
protected:
    std::string getKey() const;
public:
    imageGenerator(std::string api = "sk-##############################################");//api key
    virtual std::string generate(std::string text) const = 0;
    virtual ~imageGenerator();
};


#endif // IMAGEGENERATOR_H
