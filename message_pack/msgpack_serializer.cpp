#include <msgpack.hpp>

#include <fstream>

#include "serializer.hpp"

void Serializer::SerializeMsgPack() {
    current_type = SerializerType::MsgPack;
    current_mode = SerializerMode::RAM;
    ss.clear(); ss.str("");
    msgpack::pack(ss, data_struct);
}

void Serializer::DeserializeMsgPack() {
    current_type = SerializerType::MsgPack;
    current_mode = SerializerMode::RAM;
    std::string str(ss.str());
    msgpack::object_handle oh = msgpack::unpack(str.data(), str.size());
    msgpack::object deserialized = oh.get();
    DataStruct data_struct_new = deserialized.as<DataStruct>();
}

void Serializer::SerializeMsgPackToFile() {
    current_type = SerializerType::MsgPack;
    current_mode = SerializerMode::File;
    filename = "demofile.msgp";
    std::ofstream ofs((filepath + filename).c_str(), std::ios::binary);
    if (!ofs.is_open())
        throw std::runtime_error("Cannot open " + filename);
    msgpack::pack(ofs, data_struct);
}

void Serializer::DeserializeMsgPackFromFile() {
    current_type = SerializerType::MsgPack;
    current_mode = SerializerMode::File;
    filename = "demofile.msgp";
    std::ifstream ifs((filepath + filename).c_str(), std::ios::binary);
    if (!ifs.is_open())
        throw std::runtime_error("Cannot open " + filename);
    ss.clear(); ss.str("");
    ss << ifs.rdbuf();
    std::string str(ss.str());
    msgpack::object_handle oh = msgpack::unpack(str.data(), str.size());
    msgpack::object deserialized = oh.get();
    DataStruct data_struct_new = deserialized.as<DataStruct>();
}
