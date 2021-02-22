#include "boost_serializer.hpp"
#include "serializer.hpp"

#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/archive/xml_iarchive.hpp>
#include <boost/archive/xml_oarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>

void Serializer::SerializeBinary() {
    current_type = SerializerType::Binary;
    current_mode = SerializerMode::RAM;
    ss.str(""); // clearing string stream buffer 0 ms time
    {
        boost::archive::binary_oarchive oa(ss);
        oa << data_struct;
    }
}

void Serializer::DeserializeBinary() {
    current_type = SerializerType::Binary;
    current_mode = SerializerMode::RAM;
    DataStruct data_struct_new;
    {
        boost::archive::binary_iarchive ia(ss);
        ia >> data_struct_new;
    }
}

void Serializer::SerializeXML() {
    current_type = SerializerType::XML;
    current_mode = SerializerMode::RAM;
    ss.str("");
    {
        boost::archive::xml_oarchive oa(ss);
        oa << BOOST_SERIALIZATION_NVP(data_struct);
    }
}

void Serializer::DeserializeXML() {
    current_type = SerializerType::XML;
    current_mode = SerializerMode::RAM;
    DataStruct data_struct_new;
    {
        boost::archive::xml_iarchive ia(ss);
        ia >> BOOST_SERIALIZATION_NVP(data_struct_new);
    }
}

void Serializer::SerializeText() {
    current_type = SerializerType::Text;
    current_mode = SerializerMode::RAM;
    ss.str("");
    {
        boost::archive::text_oarchive oa(ss);
        oa << data_struct;
    }
}

void Serializer::DeserializeText() {
    current_type = SerializerType::Text;
    current_mode = SerializerMode::RAM;
    DataStruct data_struct_new;
    {
        boost::archive::text_iarchive ia(ss);
        ia >> data_struct_new;
    }
}

void Serializer::SerializeBinaryToFile() {
    current_type = SerializerType::Binary;
    current_mode = SerializerMode::File;
    filename = "demofile.bin";
    ofs.open((filepath + filename).c_str(), std::ios::binary);
    if (!ofs.is_open())
        throw std::runtime_error("Cannot open " + filename);
    {
        boost::archive::binary_oarchive oa(ofs);
        oa << data_struct;
    }
    ofs.close(); // closing ofs, as ofs and ifs are class attributes which are out of scope of class methods
}

void Serializer::DeserializeBinaryFromFile() {
    current_type = SerializerType::Binary;
    current_mode = SerializerMode::File;
    DataStruct data_struct_new;
    filename = "demofile.bin";
    ifs.open((filepath + filename).c_str(), std::ios::binary);
    if (!ifs.is_open())
        throw std::runtime_error("Cannot open " + filename);
    {
        boost::archive::binary_iarchive ia(ifs);
        ia >> data_struct_new;
    }
    ifs.close();
}

void Serializer::SerializeXMLToFile() {
    current_type = SerializerType::XML;
    current_mode = SerializerMode::File;
    filename = "demofile.xml";
    ofs.open((filepath + filename).c_str());
    if (!ofs.is_open())
        throw std::runtime_error("Cannot open " + filename);
    {
        boost::archive::xml_oarchive oa(ofs);
        oa << BOOST_SERIALIZATION_NVP(data_struct);
    }
    ofs.close();
}

void Serializer::DeserializeXMLFromFile() {
    current_type = SerializerType::XML;
    current_mode = SerializerMode::File;
    DataStruct data_struct_new;
    filename = "demofile.xml";
    ifs.open((filepath + filename).c_str());
    if (!ifs.is_open())
        throw std::runtime_error("Cannot open " + filename);
    {
        boost::archive::xml_iarchive ia(ifs);
        ia >> BOOST_SERIALIZATION_NVP(data_struct_new);
    }
    ifs.close();
}

void Serializer::SerializeTextToFile() {
    current_type = SerializerType::Text;
    current_mode = SerializerMode::File;
    filename = "demofile.txt";
    ofs.open((filepath + filename).c_str());
    if (!ofs.is_open())
        throw std::runtime_error("Cannot open " + filename);
    {
        boost::archive::text_oarchive oa(ofs);
        oa << data_struct;
    }
    ofs.close();
}

void Serializer::DeserializeTextFromFile() {
    current_type = SerializerType::Text;
    current_mode = SerializerMode::File;
    DataStruct data_struct_new;
    filename = "demofile.txt";
    ifs.open((filepath + filename).c_str());
    if (!ifs.is_open())
        throw std::runtime_error("Cannot open " + filename);
    {
        boost::archive::text_iarchive ia(ifs);
        ia >> data_struct_new;
    }
    ifs.close();
}
