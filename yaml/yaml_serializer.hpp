#ifndef SERIALIZATION_YAML_YAML_SERIALIZER_H_
#define SERIALIZATION_YAML_YAML_SERIALIZER_H_

#include <vector>
#include <map>

#include "struct.hpp"

#include "yaml-cpp/yaml.h"

namespace YAML {
    template<>
    struct convert<DataStruct> {
        static Node encode(const DataStruct& data_struct) {
            Node node;

            node["str"] = data_struct.str;
            node["int_num"] = data_struct.int_num;
            node["double_num"] = data_struct.double_num;
            node["v_int"] = data_struct.v_int;
            node["map_str_str"] = data_struct.map_str_str;
            node["map_map"] = data_struct.map_map;
            node["map_vector_map"] = data_struct.map_vector_map;

            return node;
        }

        static bool decode(const Node& node, DataStruct& data_struct) {
            data_struct.str = node["str"].as<std::string>();
            data_struct.int_num = node["int_num"].as<int>();
            data_struct.double_num = node["double_num"].as<double>();
            data_struct.v_int = node["v_int"].as<std::vector<int>>();
            data_struct.map_str_str = node["map_str_str"].as<std::map<std::string, std::string>>();
            data_struct.map_map = node["map_map"].as<std::map<std::string, std::map<std::string, int>>>();
            data_struct.map_vector_map = node["map_vector_map"].as<std::map<std::string, std::vector<std::map<std::string, std::string>>>>();
            return true;
        }
    };
}

#endif // SERIALIZATION_YAML_YAML_SERIALIZER_H_
