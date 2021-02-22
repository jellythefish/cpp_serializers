#include "serializer.hpp"

Serializer::Serializer(const DataStruct& data_struct) :
    data_struct(data_struct),
    ds_message(GenerateProtoMessage(data_struct)) {}

size_t Serializer::GetDataSize() const {
    if (current_mode == SerializerMode::RAM) {
        switch (current_type) {
            case SerializerType::Binary:
            case SerializerType::XML:
            case SerializerType::Text:
            case SerializerType::JSON:
                return ss.str().size();
            case SerializerType::Protobuf:
                return pb_ss.str().size();
            case SerializerType::Avro:
                return avro_os->byteCount();
        }
    } else {
        std::ifstream in_file(filepath + filename, std::ios::binary);
        in_file.seekg(0, std::ios::end);
        return in_file.tellg();
    }
    return -1;
}
