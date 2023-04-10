#ifndef IMAGEGENERATOR_H
#define IMAGEGENERATOR_H
#include <string>
#include <json/json.h>



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
