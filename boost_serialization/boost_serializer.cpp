#include "boost_serializer.hpp"
#include "serializer.hpp"

#include <fstream>

#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/archive/xml_iarchive.hpp>
#include <boost/archive/xml_oarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>

void Serializer::SerializeBinary() {
    current_type = SerializerType::Binary;
    current_mode = SerializerMode::RAM;
    ss.clear(); ss.str(""); // resetting string stream buffer 0 ms time
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
    ss.clear(); ss.str("");
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
    ss.clear(); ss.str("");
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
    std::ofstream ofs((filepath + filename).c_str(), std::ios::binary);
    if (!ofs.is_open())
        throw std::runtime_error("Cannot open " + filename);
    {
        boost::archive::binary_oarchive oa(ofs);
        oa << data_struct;
    }
}

void Serializer::DeserializeBinaryFromFile() {
    current_type = SerializerType::Binary;
    current_mode = SerializerMode::File;
    DataStruct data_struct_new;
    filename = "demofile.bin";
    std::ifstream ifs((filepath + filename).c_str(), std::ios::binary);
    if (!ifs.is_open())
        throw std::runtime_error("Cannot open " + filename);
    {
        boost::archive::binary_iarchive ia(ifs);
        ia >> data_struct_new;
    }
}

void Serializer::SerializeXMLToFile() {
    current_type = SerializerType::XML;
    current_mode = SerializerMode::File;
    filename = "demofile.xml";
    std::ofstream ofs((filepath + filename).c_str());
    if (!ofs.is_open())
        throw std::runtime_error("Cannot open " + filename);
    {
        boost::archive::xml_oarchive oa(ofs);
        oa << BOOST_SERIALIZATION_NVP(data_struct);
    }
}

void Serializer::DeserializeXMLFromFile() {
    current_type = SerializerType::XML;
    current_mode = SerializerMode::File;
    DataStruct data_struct_new;
    filename = "demofile.xml";
    std::ifstream ifs((filepath + filename).c_str());
    if (!ifs.is_open())
        throw std::runtime_error("Cannot open " + filename);
    {
        boost::archive::xml_iarchive ia(ifs);
        ia >> BOOST_SERIALIZATION_NVP(data_struct_new);
    }
}

void Serializer::SerializeTextToFile() {
    current_type = SerializerType::Text;
    current_mode = SerializerMode::File;
    filename = "demofile.txt";
    std::ofstream ofs((filepath + filename).c_str());
    if (!ofs.is_open())
        throw std::runtime_error("Cannot open " + filename);
    {
        boost::archive::text_oarchive oa(ofs);
        oa << data_struct;
    }
}

void Serializer::DeserializeTextFromFile() {
    current_type = SerializerType::Text;
    current_mode = SerializerMode::File;
    DataStruct data_struct_new;
    filename = "demofile.txt";
    std::ifstream ifs((filepath + filename).c_str());
    if (!ifs.is_open())
        throw std::runtime_error("Cannot open " + filename);
    {
        boost::archive::text_iarchive ia(ifs);
        ia >> data_struct_new;
    }
}
