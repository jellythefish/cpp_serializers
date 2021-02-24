#include <msgpack.hpp>

#include "serializer.hpp"

void Serializer::SerializeMsgPack() {
    current_type = SerializerType::MsgPack;
    current_mode = SerializerMode::RAM;
    ss.str("");
    msgpack::pack(ss, data_struct);
    ss.seekg(0);
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
    ofs.open((filepath + filename).c_str(), std::ios::binary);
    if (!ofs.is_open())
        throw std::runtime_error("Cannot open " + filename);
    msgpack::pack(ofs, data_struct);
    ofs.close();
}

void Serializer::DeserializeMsgPackFromFile() {
    current_type = SerializerType::MsgPack;
    current_mode = SerializerMode::File;
    filename = "demofile.msgp";
    ifs.open((filepath + filename).c_str(), std::ios::binary);
    if (!ifs.is_open())
        throw std::runtime_error("Cannot open " + filename);
    std::stringstream buffer;
    buffer << ifs.rdbuf();
    std::string str(buffer.str());
    msgpack::object_handle oh = msgpack::unpack(str.data(), str.size());
    msgpack::object deserialized = oh.get();
    DataStruct data_struct_new = deserialized.as<DataStruct>();
    ifs.close();
    std::cout << data_struct_new.str << std::endl;
}
