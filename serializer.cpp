#include "serializer.h"

#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/archive/xml_iarchive.hpp>
#include <boost/archive/xml_oarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>

Serializer::Serializer(const DataStruct& dataStruct) : dataStruct(dataStruct) {}

void Serializer::SerializeBinary() {
    ss.str(""); // clearing string stream buffer 0 ms time
    {
        boost::archive::binary_oarchive oa(ss);
        oa << dataStruct;
    }
}

void Serializer::DeserializeBinary() {
    DataStruct dataStruct_new;
    {
        boost::archive::binary_iarchive ia(ss);
        ia >> dataStruct_new;
    }
}

void Serializer::SerializeXML() {
    ss.str("");
    {
        boost::archive::xml_oarchive oa(ss);
        oa << BOOST_SERIALIZATION_NVP(dataStruct);
    }
}

void Serializer::DeserializeXML() {
    DataStruct dataStruct_new;
    {
        boost::archive::xml_iarchive ia(ss);
        ia >> BOOST_SERIALIZATION_NVP(dataStruct_new);
    }
}

void Serializer::SerializeText() {
    ss.str("");
    {
        boost::archive::text_oarchive oa(ss);
        oa << dataStruct;
    }
}

void Serializer::DeserializeText() {
    DataStruct dataStruct_new;
    {
        boost::archive::text_iarchive ia(ss);
        ia >> dataStruct_new;
    }
}

void Serializer::SerializeBinaryToFile() {
    filename = "demofile.bin";
    ofs.open((filepath + filename).c_str(), std::ios::binary);
    if (!ofs.is_open())
        throw std::runtime_error("Cannot open " + filename);
    {
        boost::archive::binary_oarchive oa(ofs);
        oa << dataStruct;
    }
    ofs.close(); // closing ofs, as ofs and ifs are class attributes which are out of scope of class methods
}

void Serializer::DeserializeBinaryFromFile() {
    DataStruct dataStruct_new;
    filename = "demofile.bin";
    ifs.open((filepath + filename).c_str(), std::ios::binary);
    if (!ifs.is_open())
        throw std::runtime_error("Cannot open " + filename);
    {
        boost::archive::binary_iarchive ia(ifs);
        ia >> dataStruct_new;
    }
    ifs.close();
}

void Serializer::SerializeXMLToFile() {
    filename = "demofile.xml";
    ofs.open((filepath + filename).c_str());
    if (!ofs.is_open())
        throw std::runtime_error("Cannot open " + filename);
    {
        boost::archive::xml_oarchive oa(ofs);
        oa << BOOST_SERIALIZATION_NVP(dataStruct);
    }
    ofs.close();
}

void Serializer::DeserializeXMLFromFile() {
    DataStruct dataStruct_new;
    filename = "demofile.xml";
    ifs.open((filepath + filename).c_str());
    if (!ifs.is_open())
        throw std::runtime_error("Cannot open " + filename);
    {
        boost::archive::xml_iarchive ia(ifs);
        ia >> BOOST_SERIALIZATION_NVP(dataStruct_new);
    }
    ifs.close();
}

void Serializer::SerializeTextToFile() {
    filename = "demofile.txt";
    ofs.open((filepath + filename).c_str());
    if (!ofs.is_open())
        throw std::runtime_error("Cannot open " + filename);
    {
        boost::archive::text_oarchive oa(ofs);
        oa << dataStruct;
    }
    ofs.close();
}

void Serializer::DeserializeTextFromFile() {
    DataStruct dataStruct_new;
    filename = "demofile.txt";
    ifs.open((filepath + filename).c_str());
    if (!ifs.is_open())
        throw std::runtime_error("Cannot open " + filename);
    {
        boost::archive::text_iarchive ia(ifs);
        ia >> dataStruct_new;
    }
    ifs.close();
}

size_t Serializer::GetDataSize() const {
    return ss.str().size();
}

std::string Serializer::GetFilename() const {
    return filepath + filename;
}

