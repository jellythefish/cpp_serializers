#include "serializer.hpp"
#include "boost_json.hpp"

#include <fstream>

void Serializer::SerializeJSON() {
    current_type = SerializerType::JSON;
    current_mode = SerializerMode::RAM;
    ss.str(""); // clearing string stream buffer 0 ms time
    json::value jv = json::value_from(data_struct);
    ss << jv;
}

void Serializer::DeserializeJSON() {
    current_type = SerializerType::JSON;
    current_mode = SerializerMode::RAM;
    json::value jv = json::parse(ss.str());
    DataStruct data_struct_new(json::value_to<DataStruct>(jv));
}

void Serializer::SerializeJSONToFile() {
    current_type = SerializerType::JSON;
    current_mode = SerializerMode::File;
    filename = "demofile.json";
    std::ofstream ofs((filepath + filename).c_str());
    if (!ofs.is_open())
        throw std::runtime_error("Cannot open " + filename);
    json::value v = json::value_from(data_struct);
    ofs << v;
}

void Serializer::DeserializeJSONFromFile() {
    current_type = SerializerType::JSON;
    current_mode = SerializerMode::File;
    filename = "demofile.json";
    std::ifstream ifs((filepath + filename).c_str());
    if (!ifs.is_open()) {
        throw std::runtime_error("Cannot open " + filename);
    }
    // to deserialize JSON the string is needed, so first read file to stringstream, then convert it to string
    // and call implemented DeserializeJSON()
    ss.str("");
    ss << ifs.rdbuf();
    json::value jv = json::parse(ss.str());
    DataStruct data_struct_new(json::value_to<DataStruct>(jv));
}