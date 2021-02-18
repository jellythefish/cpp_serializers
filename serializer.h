#ifndef SERIALIZATION_SERIALIZER_H_
#define SERIALIZATION_SERIALIZER_H_

#include "struct.h"

#include <fstream>
#include <sstream>

class Serializer {
public:
    Serializer(const DataStruct& dataStruct);

    void SerializeBinary();
    void DeserializeBinary();
    void SerializeBinaryToFile();
    void DeserializeBinaryFromFile();

    void SerializeXML();
    void DeserializeXML();
    void SerializeXMLToFile();
    void DeserializeXMLFromFile();

    void SerializeText();
    void DeserializeText();
    void SerializeTextToFile();
    void DeserializeTextFromFile();

    size_t GetDataSize() const;
    std::string GetFilename() const;

private:
    std::stringstream ss; // a buffer for serialized data
    std::ofstream ofs; // for serialization to file
    std::ifstream ifs; // for deserialization from file
    const DataStruct& dataStruct;

    std::string filepath = "C:/Users/Slava/Desktop/serialization/";
    std::string filename; // is defined in class methods
};

#endif  // SERIALIZATION_SERIALIZER_H_

