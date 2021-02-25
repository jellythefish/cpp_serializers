#include <iostream>
#include <ctime>
#include <sstream>

#include "serializer.hpp"
#include "util/util.hpp"

int main(int argc, char** argv) {
    if (argc != 2) {
        throw std::invalid_argument("Wrong number of arguments.");
    }
    std::string size_argument = argv[1];
    StructSize size;
    if (size_argument == "small") {
        size = StructSize::Small;
    } else if (size_argument == "medium") {
        size = StructSize::Medium;
    } else if (size_argument == "large") {
        size = StructSize::Large;
    } else {
        throw std::invalid_argument("Size argument is invalid.");
    }

    std::cout << "Generating Data Structure...\r" << std::flush;
//    DataStruct data_struct = GetSimpleStruct();
    DataStruct data_struct = GenerateStruct(size); // Small/Medium/Large
    Serializer bs(data_struct);
    std::cout << "Generating Data Structure...OK" << std::endl;

    // configuring beautiful output magic :)
    tabulate::Table table_info;
    table_info.add_row({"Type", "Operation", "Place", "Time", "Memory"});
    table_info.format().font_align(tabulate::FontAlign::center);
    for (size_t i = 0; i < 5; ++i) {
        table_info[0][i].format()
            .font_align(tabulate::FontAlign::center)
            .font_color(tabulate::Color::grey)
            .font_style({tabulate::FontStyle::bold})
            .font_background_color(tabulate::Color::white);
    }

    std::cout << "Serialization running...\r" << std::flush;
    profile(&Serializer::SerializeBinary, bs, {"Binary\n(Boost)", "Serialization", "RAM"}, table_info);
    profile(&Serializer::DeserializeBinary, bs, {"Binary\n(Boost)", "Deserialization", "RAM"}, table_info);
    profile(&Serializer::SerializeXML, bs, {"XML", "Serialization", "RAM"}, table_info);
    profile(&Serializer::DeserializeXML, bs, {"XML", "Deserialization", "RAM"}, table_info);
    profile(&Serializer::SerializeText, bs, {"Raw text", "Serialization", "RAM"}, table_info);
    profile(&Serializer::DeserializeText, bs, {"Raw text", "Deserialization", "RAM"}, table_info);
    profile(&Serializer::SerializeJSON, bs, {"JSON", "Serialization", "RAM"}, table_info);
    profile(&Serializer::DeserializeJSON, bs, {"JSON", "Deserialization", "RAM"}, table_info);
    profile(&Serializer::SerializeProtobuf, bs, {"Protobuf", "Serialization", "RAM"}, table_info);
    profile(&Serializer::DeserializeProtobuf, bs, {"Protobuf", "Deserialization", "RAM"}, table_info);
    profile(&Serializer::SerializeAvro, bs, {"Avro", "Serialization", "RAM"}, table_info);
    profile(&Serializer::DeserializeAvro, bs, {"Avro", "Deserialization", "RAM"}, table_info);
    profile(&Serializer::SerializeYAML, bs, {"YAML", "Serialization", "RAM"}, table_info);
    profile(&Serializer::DeserializeYAML, bs, {"YAML", "Deserialization", "RAM"}, table_info);
    profile(&Serializer::SerializeMsgPack, bs, {"MsgPack", "Serialization", "RAM"}, table_info);
    profile(&Serializer::DeserializeMsgPack, bs, {"MsgPack", "Deserialization", "RAM"}, table_info);

    table_info.add_row({"-----------","---------------","---------","---------------------","----------------------"});

    profile(&Serializer::SerializeBinaryToFile, bs, {"Binary\n(Boost)", "Serialization", "File"}, table_info);
    profile(&Serializer::DeserializeBinaryFromFile, bs, {"Binary\n(Boost)", "Deserialization", "File"}, table_info);
    profile(&Serializer::SerializeXMLToFile, bs, {"XML", "Serialization", "File"}, table_info);
    profile(&Serializer::DeserializeXMLFromFile, bs, {"XML", "Deserialization", "File"}, table_info);
    profile(&Serializer::SerializeTextToFile, bs, {"Raw text", "Serialization", "File"}, table_info);
    profile(&Serializer::DeserializeTextFromFile, bs, {"Raw text", "Deserialization", "File"}, table_info);
    profile(&Serializer::SerializeJSONToFile, bs,{"JSON", "Serialization", "File"}, table_info);
    profile(&Serializer::DeserializeJSONFromFile, bs,{"JSON", "Deserialization", "File"}, table_info);
    profile(&Serializer::SerializeProtobufToFile, bs, {"Protobuf", "Serialization", "File"}, table_info);
    profile(&Serializer::DeserializeProtobufFromFile, bs, {"Protobuf", "Deserialization", "File"}, table_info);
    profile(&Serializer::SerializeAvroToFile, bs, {"Avro", "Serialization", "File"}, table_info);
    profile(&Serializer::DeserializeAvroFromFile, bs, {"Avro", "Deserialization", "File"}, table_info);
    profile(&Serializer::SerializeYAMLToFile, bs, {"YAML", "Serialization", "File"}, table_info);
    profile(&Serializer::DeserializeYAMLFromFile, bs, {"YAML", "Deserialization", "File"}, table_info);
    profile(&Serializer::SerializeMsgPackToFile, bs, {"MsgPack", "Serialization", "File"}, table_info);
    profile(&Serializer::DeserializeMsgPackFromFile, bs, {"MsgPack", "Deserialization", "File"}, table_info);
    // TODO to implement progress bar
    std::cout << "Serialization running...OK" << std::endl;
    std::cout << table_info << std::endl;
    std::cout << "Serialization finished." << std::endl;
    return 0;
}





