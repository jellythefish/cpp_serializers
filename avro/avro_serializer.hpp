#ifndef SERIALIZATION_AVRO_AVRO_SERIALIZER_HPP_
#define SERIALIZATION_AVRO_AVRO_SERIALIZER_HPP_

#include "struct.hpp"

#include "avro/Encoder.hh"
#include "avro/Decoder.hh"
#include "avro/Specific.hh"

namespace avro {
    template<typename T>
    struct codec_traits {
        static void encode(Encoder &e, const DataStruct &data_struct) {
            avro::encode(e, data_struct.str);
            avro::encode(e, data_struct.int_num);
            avro::encode(e, data_struct.double_num);
            avro::encode(e, data_struct.v_int);
            avro::encode(e, data_struct.map_str_str);
            avro::encode(e, data_struct.map_map);
            avro::encode(e, data_struct.map_vector_map);
        }

        static void decode(Decoder &d, DataStruct &data_struct) {
            avro::decode(d, data_struct.str);
            avro::decode(d, data_struct.int_num);
            avro::decode(d, data_struct.double_num);
            avro::decode(d, data_struct.v_int);
            avro::decode(d, data_struct.map_str_str);
            avro::decode(d, data_struct.map_map);
            avro::decode(d, data_struct.map_vector_map);
        }
    };
}

#endif // SERIALIZATION_AVRO_AVRO_SERIALIZER_HPP_
