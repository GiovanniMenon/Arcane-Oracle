#ifndef DALL_E_GENERATOR_H
#define DALL_E_GENERATOR_H

#include <iostream>
#include <QApplication>
#include <QByteArray>
#include <QLabel>
#include <QFile>
#include <QPixmap>

#ifdef __has_include
#if __has_include(<jsoncpp/json/json.h>)
#include <jsoncpp/json/json.h>
#elif __has_include(<json/json.h>)
#include <json/json.h>
#endif
#else
#include <json/json.h>
#endif

class DALL_E_generator {
private:
    static size_t callback(char* data, size_t size, size_t nmemb, std::string* buffer);

public:
    std::string apiKey;
    DALL_E_generator();
    std::string generate(const std::string description);
    std::string convert(std::string,std::string,std::string deck_name) const ;
};

#endif // DALL_E_GENERATOR_H
