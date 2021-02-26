#include "serializer.hpp"

#include <fstream>

#include "data_struct.pb.h"

void Serializer::SerializeProtobuf() {
    current_type = SerializerType::Protobuf;
    current_mode = SerializerMode::RAM;
    pb_ss.str(""); // clearing string stream buffer 0 ms time
    ds_message.SerializeToOstream(&pb_ss);
}

void Serializer::DeserializeProtobuf() {
    current_type = SerializerType::Protobuf;
    current_mode = SerializerMode::RAM;
    proto::DataStruct ds_message_new;
    ds_message_new.ParseFromIstream(&pb_ss);
}

void Serializer::SerializeProtobufToFile() {
    current_type = SerializerType::Protobuf;
    current_mode = SerializerMode::File;
    filename = "demofile.pb";
    std::ofstream ofs((filepath + filename).c_str(), std::ios::binary);
    if (!ofs.is_open())
        throw std::runtime_error("Cannot open " + filename);
    ds_message.SerializeToOstream(&ofs);
}

void Serializer::DeserializeProtobufFromFile() {
    current_type = SerializerType::Protobuf;
    current_mode = SerializerMode::File;
    filename = "demofile.pb";
    std::ifstream ifs((filepath + filename).c_str(), std::ios::binary);
    if (!ifs.is_open()) {
        throw std::runtime_error("Cannot open " + filename);
    }
    proto::DataStruct ds_message_new;
    ds_message_new.ParseFromIstream(&ifs);
}
