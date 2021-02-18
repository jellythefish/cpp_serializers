#include "serializer.hpp"

size_t Serializer::GetDataSize() const {
    return ss.str().size();
}

std::string Serializer::GetFilename() const {
    return filepath + filename;
}
