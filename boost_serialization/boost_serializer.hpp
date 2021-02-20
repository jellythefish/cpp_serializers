#ifndef SERIALIZATION_BOOST_SERIALIZATION_BOOST_SERIALIZE_H_
#define SERIALIZATION_BOOST_SERIALIZATION_BOOST_SERIALIZE_H_

#include "struct.hpp"

#include <boost/serialization/map.hpp>
#include <boost/serialization/vector.hpp>

// The native and XML serializations were implemented with Boost.Serialization methods which hold Archive data structure
// and convert it to binary/xml/text.
namespace boost {
    namespace serialization {
        template<class Archive>
        void serialize(Archive& ar, DataStruct& data_struct, const unsigned int version) {
            // Data is saved to the archive with either the << or the & operator.
            ar & make_nvp("str", data_struct.str); // make_nvp is needed for naming of each class data member in XML
            ar & make_nvp("int_num", data_struct.int_num);
            ar & make_nvp("double_num", data_struct.double_num);
            ar & make_nvp("v_int", data_struct.v_int);
            ar & make_nvp("map_str_str", data_struct.map_str_str);
            ar & make_nvp("map_map", data_struct.map_map);
            ar & make_nvp("map_vector_map", data_struct.map_vector_map);
        }
    } // namespace serialization
} // namespace boost_serialization

#endif // SERIALIZATION_BOOST_SERIALIZATION_BOOST_SERIALIZE_H_
