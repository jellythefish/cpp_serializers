#ifndef SERIALIZATION_UTIL_UTIL_HEADER_H_
#define SERIALIZATION_UTIL_UTIL_HEADER_H_

#include "serializer.hpp"
#include <tabulate/table.hpp>

#include <random>

struct Entry {
    std::string type;
    std::string place;
};

void profile(void (Serializer::*ser_func)(), void (Serializer::*deser_func)(), long int iter,
             Serializer& obj, const Entry& e, tabulate::Table& t);

class Randomizer {
public:
    Randomizer();
    int32_t GetRandInt();
private:
    std::mt19937 gen_int;
    std::uniform_int_distribution<> rand_ind; // from [a, b]
};

#endif // SERIALIZATION_UTIL_UTIL_HEADER_H_
