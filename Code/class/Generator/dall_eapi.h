#ifndef DALL_E_GENERATOR_H
#define DALL_E_GENERATOR_H

#include "imagegenerator.h"
#include <iostream>
#include <QApplication>
#include <QByteArray>
#include <QLabel>
#include <QFile>
#include <QPixmap>

class DALL_E_generator : public imageGenerator{
private:
    static size_t callback(char* data, size_t size, size_t nmemb, std::string* buffer);
public:
    DALL_E_generator();
    std::string generate(const std::string description);
    std::string convert(std::string,std::string,std::string deck_name) const ;
};

#endif // DALL_E_GENERATOR_H
