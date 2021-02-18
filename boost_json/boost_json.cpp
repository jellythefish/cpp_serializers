#include "../serializer.hpp"
#include "boost_json.hpp"

#include <iostream>

void Serializer::SerializeJSON() {
    json::value jv = json::value_from(data_struct);
    ss.str(""); // clearing string stream buffer 0 ms time
    ss << jv;
}

void Serializer::DeserializeJSON() {
    json::value jv = json::parse(ss.str());
    DataStruct data_struct_new(json::value_to<DataStruct>(jv));
}

void Serializer::SerializeJSONToFile() {
    filename = "demofile.json";
    ofs.open((filepath + filename).c_str());
    if (!ofs.is_open())
        throw std::runtime_error("Cannot open " + filename);
    json::value v = json::value_from(data_struct);
    ofs << v;
    ofs.close(); // closing ofs, as ofs and ifs are class attributes wh
}

void Serializer::DeserializeJSONFromFile() {
    filename = "demofile.json";
    ifs.open((filepath + filename).c_str());
    if (!ifs.is_open()) {
        throw std::runtime_error("Cannot open " + filename);
    }
    // to deserialize JSON the string is needed, so first read file to stringstream, then convert it to string
    // and call implemented DeserializeJSON()
    ss.str("");
    ss << ifs.rdbuf();
    DeserializeJSON();
    ifs.close();
}