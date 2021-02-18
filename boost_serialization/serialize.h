#ifndef SERIALIZATION_BOOST_SERIALIZATION_BOOST_SERIALIZE_H_
#define SERIALIZATION_BOOST_SERIALIZATION_BOOST_SERIALIZE_H_

#include "../struct.h"

#include <boost/serialization/map.hpp>
#include <boost/serialization/vector.hpp>

// The native and XML serializations were implemented with Boost.Serialization methods which hold Archive data structure
// and convert it to binary/xml/text.
namespace boost {
    namespace serialization {
        template<class Archive>
        void serialize(Archive& ar, DataStruct& data_struct, const unsigned int version);
    } // namespace serialization
} // namespace boost_serialization

#endif // SERIALIZATION_BOOST_SERIALIZATION_BOOST_SERIALIZE_H_
