#include "serializer.hpp"

#include "data_struct.pb.h"

void Serializer::SerializeProtobuf() {
    pb_ss.str(""); // clearing string stream buffer 0 ms time
    ds_message.SerializeToOstream(&pb_ss);
}

void Serializer::DeserializeProtobuf() {
    proto::DataStruct ds_message_new;
    ds_message_new.ParseFromIstream(&pb_ss);
}

void Serializer::SerializeProtobufToFile() {
    filename = "demofile.pb";
    ofs.open((filepath + filename).c_str(), std::ios::binary);
    if (!ofs.is_open())
        throw std::runtime_error("Cannot open " + filename);
    ds_message.SerializeToOstream(&ofs);
    ofs.close();
}

void Serializer::DeserializeProtobufFromFile() {
    proto::DataStruct ds_message_new;
    filename = "demofile.pb";
    ifs.open((filepath + filename).c_str(), std::ios::binary);
    if (!ifs.is_open())
        throw std::runtime_error("Cannot open " + filename);
    ds_message_new.ParseFromIstream(&ifs);
    ifs.close();
}
