#include <iostream>
#include <ctime>
#include <sstream>
#include <functional>

#include "boost_serialization/serialize.h"

using namespace std;

enum class SerializationType {
    RAM,
    Disk
};

// example function for profile()
void do_work() {
    for (uint64_t i = 0; i < 10000000000; ++i) {}
}

void profile(void (BoostSerializator::*function)(), BoostSerializator& obj, SerializationType st, const string& desc) {
    clock_t time;
    time = clock();
    (obj.*function)(); // calling function which is a non-static method of class BoostSerializator
    double diff = clock() - time;
    size_t dataSize;
    if (st == SerializationType::RAM) {
        dataSize = obj.getDataSize();
    } else {
        ifstream in_file(obj.getFilename(), ios::binary);
        in_file.seekg(0, ios::end);
        dataSize = in_file.tellg();
    }
    cout << desc << " took "<< diff / (CLOCKS_PER_SEC / 1000)  << " ms/" << diff / CLOCKS_PER_SEC << " s"
        << " and " << dataSize << " b/" << dataSize / 1024 << " Kb/" << dataSize / (1024 * 1024) << " Mb." << endl;
}

int main() {
    cout << "Generating Data Structure...\r";
    DataStruct dataStruct = generateStruct(StructSize::Large); // Small/Medium/Large
    BoostSerializator bs(dataStruct);
    cout << "Generating Data Structure...OK" << endl;

    cout << "Serialization started..." << endl;
    profile(&BoostSerializator::serializeBinary, bs, SerializationType::RAM, "Serialization of Binary:");
    profile(&BoostSerializator::deserializeBinary, bs, SerializationType::RAM, "Deserialization of Binary:");
    profile(&BoostSerializator::serializeXML, bs, SerializationType::RAM, "Serialization of XML:");
    profile(&BoostSerializator::deserializeXML, bs, SerializationType::RAM, "Deserialization of XML:");
    profile(&BoostSerializator::serializeText, bs, SerializationType::RAM, "Serialization of Raw Text:");
    profile(&BoostSerializator::deserializeText, bs, SerializationType::RAM, "Deserialization of Raw Text:");

    profile(&BoostSerializator::serializeBinaryToFile, bs, SerializationType::Disk, "Serialization of Binary to file:");
    profile(&BoostSerializator::deserializeBinaryFromFile, bs, SerializationType::Disk, "Deserialization of Binary from file:");
    profile(&BoostSerializator::serializeTextToFile, bs, SerializationType::Disk, "Serialization of Raw Text to file:");
    profile(&BoostSerializator::deserializeTextFromFile, bs, SerializationType::Disk, "Deserialization of Raw Text from file:");
    profile(&BoostSerializator::serializeXMLToFile, bs, SerializationType::Disk, "Serialization of XML to file:");
    profile(&BoostSerializator::deserializeXMLFromFile, bs, SerializationType::Disk, "Deserialization of XML from file:");
    cout << "Serialization finished." << endl;

}



