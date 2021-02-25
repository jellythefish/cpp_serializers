#ifndef SERIALIZATION_SERIALIZER_H_
#define SERIALIZATION_SERIALIZER_H_

#include "struct.hpp"
#include "data_struct.pb.h"

#include "avro/Encoder.hh"
#include "avro/Decoder.hh"

#include <ryml_std.hpp>
#include <ryml.hpp>

#include <fstream>
#include <sstream>
#include <memory>

enum SerializerType {
    Binary,
    XML,
    Text,
    JSON,
    Protobuf,
    Avro,
    Yaml,
    MsgPack
};

enum SerializerMode {
    RAM,
    File
};

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

    void SerializeJSON();
    void DeserializeJSON();
    void SerializeJSONToFile();
    void DeserializeJSONFromFile();

    void SerializeProtobuf();
    void DeserializeProtobuf();
    void SerializeProtobufToFile();
    void DeserializeProtobufFromFile();

    void SerializeAvro();
    void DeserializeAvro();
    void SerializeAvroToFile();
    void DeserializeAvroFromFile();

    void SerializeYAML();
    void DeserializeYAML();
    void SerializeYAMLToFile();
    void DeserializeYAMLFromFile();

    void SerializeMsgPack();
    void DeserializeMsgPack();
    void SerializeMsgPackToFile();
    void DeserializeMsgPackFromFile();

    size_t GetDataSize() const;

private:
    std::stringstream ss; // a memory buffer for serialized data
    // TODO to fix this
    std::stringstream pb_ss; // separate for brotobufs, don't know why protobuf ser/deser breaks basic ss
    std::ofstream ofs; // for serialization to file
    std::ifstream ifs; // for deserialization from file

    std::unique_ptr<avro::OutputStream> avro_os = avro::memoryOutputStream(); // avro output stream
    std::unique_ptr<avro::InputStream> avro_is;
    std::unique_ptr<avro::OutputStream> avro_of; // avro output stream
    std::unique_ptr<avro::InputStream> avro_if; // avro output stream

    ryml::Tree tree;

    SerializerType current_type;
    SerializerMode current_mode;

    const DataStruct& data_struct;
    proto::DataStruct ds_message;

    std::string filepath = "../datafiles/";
    std::string filename; // is defined in class methods
};

#endif  // SERIALIZATION_SERIALIZER_H_

