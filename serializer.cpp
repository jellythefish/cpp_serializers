#include "serializer.hpp"

Serializer::Serializer(const DataStruct& data_struct) :
    data_struct(data_struct),
    ds_message(GenerateProtoMessage(data_struct)) {}

size_t Serializer::GetDataSize() const {
    // TODO To fix size returned after protobuf serialization
    return ss.str().size();
}

std::string Serializer::GetFilename() const {
    return filepath + filename;
}
