#ifndef SERIALIZATION_BOOST_JSON_BOOST_JSON_H_
#define SERIALIZATION_BOOST_JSON_BOOST_JSON_H_

#include "struct.hpp"

#include <boost/json/src.hpp>

namespace json = boost::json;

// Defining a conversion from the DataStruct type to JSON value via defining an overload of tag_invoke method.
void tag_invoke(const json::value_from_tag&, json::value& jv, const DataStruct& data_struct) {
    jv = {
        {"str", data_struct.str},
        {"int_num", data_struct.int_num},
        {"double_num", data_struct.double_num},
        {"v_int", data_struct.v_int},
        {"map_str_str", data_struct.map_str_str},
        {"map_map", data_struct.map_map},
        {"map_vector_map", data_struct.map_vector_map},
    };
}

// Defining a conversion from the JSON value to DataStruct, which uses another overload of tag_invoke.
DataStruct tag_invoke(json::value_to_tag<DataStruct>, const json::value& jv) {
    const json::object& obj = jv.as_object();
    return DataStruct {
        json::value_to<std::string>(obj.at("str")),
        json::value_to<int>(obj.at("int_num")),
        json::value_to<double>(obj.at("double_num")),
        json::value_to<std::vector<int>>(obj.at("v_int")),
        json::value_to<std::map<std::string, std::string>>(obj.at("map_str_str")),
        json::value_to<std::map<std::string, std::map<std::string, int>>>(obj.at("map_map")),
        json::value_to<std::map<std::string, std::vector<std::map<std::string, std::string>>>>(obj.at("map_vector_map"))
    };
}

#endif // SERIALIZATION_BOOST_JSON_BOOST_JSON_H_
