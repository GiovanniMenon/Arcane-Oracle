#include "imagegenerator.h"

imageGenerator::imageGenerator(std::string api) : apikey(api){}

std::string imageGenerator::getKey() const { return apikey;}

imageGenerator::~imageGenerator() {}


