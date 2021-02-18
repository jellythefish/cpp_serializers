#include <iostream>
#include <ctime>
#include <sstream>
#include <functional>

#include "serializer.h"

enum class SerializationType {
    RAM,
    Disk
};

// example function for profile()
void do_work() {
    for (uint64_t i = 0; i < 10000000000; ++i) {}
}

void profile(void (Serializer::*function)(), Serializer& obj, SerializationType st, const std::string& desc) {
    clock_t time;
    time = clock();
    (obj.*function)(); // calling function which is a non-static method of class Serializer
    double diff = clock() - time;
    size_t dataSize;
    if (st == SerializationType::RAM) {
        dataSize = obj.GetDataSize();
    } else {
        std::ifstream in_file(obj.GetFilename(), std::ios::binary);
        in_file.seekg(0, std::ios::end);
        dataSize = in_file.tellg();
    }
    std::cout << desc << " took "<< diff / (CLOCKS_PER_SEC / 1000)  << " ms/" << diff / CLOCKS_PER_SEC << " s"
         << " and " << dataSize << " b/" << dataSize / 1024 << " Kb/" << dataSize / (1024 * 1024) << " Mb." << std::endl;
}

int main() {
    std::cout << "Generating Data Structure...\r";
    DataStruct dataStruct = GenerateStruct(StructSize::Small); // Small/Medium/Large
    Serializer bs(dataStruct);
    std::cout << "Generating Data Structure...OK" << std::endl;

    std::cout << "Serialization started..." << std::endl;
    profile(&Serializer::SerializeBinary, bs, SerializationType::RAM, "Serialization of Binary:");
    profile(&Serializer::DeserializeBinary, bs, SerializationType::RAM, "Deserialization of Binary:");
    profile(&Serializer::SerializeXML, bs, SerializationType::RAM, "Serialization of XML:");
    profile(&Serializer::DeserializeXML, bs, SerializationType::RAM, "Deserialization of XML:");
    profile(&Serializer::SerializeText, bs, SerializationType::RAM, "Serialization of Raw Text:");
    profile(&Serializer::DeserializeText, bs, SerializationType::RAM, "Deserialization of Raw Text:");

    profile(&Serializer::SerializeBinaryToFile, bs, SerializationType::Disk, "Serialization of Binary to file:");
    profile(&Serializer::DeserializeBinaryFromFile, bs, SerializationType::Disk, "Deserialization of Binary from file:");
    profile(&Serializer::SerializeTextToFile, bs, SerializationType::Disk, "Serialization of Raw Text to file:");
    profile(&Serializer::DeserializeTextFromFile, bs, SerializationType::Disk, "Deserialization of Raw Text from file:");
    profile(&Serializer::SerializeXMLToFile, bs, SerializationType::Disk, "Serialization of XML to file:");
    profile(&Serializer::DeserializeXMLFromFile, bs, SerializationType::Disk, "Deserialization of XML from file:");
    std::cout << "Serialization finished." << std::endl;
    return 0;
}





