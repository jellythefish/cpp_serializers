#pragma once

#include "../struct.h"

#include <fstream>
#include <sstream>
#include <boost/serialization/map.hpp>
#include <boost/serialization/vector.hpp>

// defining serialization of DataStruct with boost_serialization library
namespace boost {
    namespace serialization {
        template<class Archive>
        void serialize(Archive& ar, DataStruct& dataStruct, const unsigned int version) {
            // Data is saved to the archive with either the << or the & operator.
            ar & make_nvp("str", dataStruct.str); // make_nvp is needed for naming of each class data member of XML
            ar & make_nvp("int_num", dataStruct.int_num);
            ar & make_nvp("double_num", dataStruct.double_num);
            ar & make_nvp("v_int", dataStruct.v_int);
            ar & make_nvp("map_", dataStruct.map_);
            ar & make_nvp("map_map", dataStruct.map_map);
            ar & make_nvp("map_vector_map", dataStruct.map_vector_map);
        }
    } // namespace serialization
} // namespace boost_serialization

class BoostSerializator {
public:
    BoostSerializator(const DataStruct& dataStruct);

    void serializeBinary();
    void deserializeBinary();
    void serializeBinaryToFile();
    void deserializeBinaryFromFile();

    void serializeXML();
    void deserializeXML();
    void serializeXMLToFile();
    void deserializeXMLFromFile();

    void serializeText();
    void deserializeText();
    void serializeTextToFile();
    void deserializeTextFromFile();

    size_t getDataSize() const;
    std::string getFilename() const;

private:
    std::stringstream ss; // a buffer for serialized data
    std::ofstream ofs; // for serialization to file
    std::ifstream ifs; // for deserialization from file
    const DataStruct& dataStruct;

    std::string filepath = "C:\\Users\\Slava\\Desktop\\serialization\\";
    std::string filename = ""; // is defined in class methods
};

