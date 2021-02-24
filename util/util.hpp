#ifndef SERIALIZATION_UTIL_UTIL_HEADER_H_
#define SERIALIZATION_UTIL_UTIL_HEADER_H_

#include "serializer.hpp"
#include <tabulate/table.hpp>

struct Entry {
    std::string type;
    std::string operation;
    std::string place;
};

void profile(void (Serializer::*function)(), Serializer& obj, const Entry& e, tabulate::Table& t);

#endif // SERIALIZATION_UTIL_UTIL_HEADER_H_
