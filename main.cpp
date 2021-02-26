#include <iostream>
#include <ctime>
#include <sstream>

#include "serializer.hpp"
#include "util/util.hpp"

int main(int argc, char** argv) {
    std::stringstream ss_err;
    if (argc != 3) {
        ss_err << "Wrong number of arguments: expected 3, but provided " << argc;
        throw std::invalid_argument(ss_err.str());
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
        ss_err << "Size argument is invalid: " << size_argument;
        throw std::invalid_argument(ss_err.str());
    }
    errno = 0; char* endptr;
    long int iter = strtol(argv[2], &endptr, 10); // number of iterations for serialization and deserialization for each method
    if (endptr == argv[2] || *endptr || errno == ERANGE || iter <= 0) {
        ss_err << "Invalid number of iterations: " << argv[2];
        throw std::invalid_argument(ss_err.str());
    }

    std::cout << "Generating " << size_argument << " data structure...\r" << std::flush;
//    DataStruct data_struct = GetSimpleStruct();
    DataStruct data_struct = GenerateStruct(size); // Small/Medium/Large
    Serializer bs(data_struct);
    std::cout << "Generating " << size_argument << " data structure...OK" << std::endl;

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

    std::cout << "Serialization running..." << std::endl;
    profile(&Serializer::SerializeBinary, &Serializer::DeserializeBinary, iter, bs, {"Binary (Boost)", "RAM"}, table_info);
    profile(&Serializer::SerializeXML, &Serializer::DeserializeXML, iter, bs, {"XML", "RAM"}, table_info);
    profile(&Serializer::SerializeText, &Serializer::DeserializeText, iter, bs, {"Raw text", "RAM"}, table_info);
    profile(&Serializer::SerializeJSON, &Serializer::DeserializeJSON, iter, bs, {"JSON", "RAM"}, table_info);
    profile(&Serializer::SerializeProtobuf, &Serializer::DeserializeProtobuf, iter, bs, {"Protobuf", "RAM"}, table_info);
    profile(&Serializer::SerializeAvro, &Serializer::DeserializeAvro, iter, bs, {"Avro", "RAM"}, table_info);
    profile(&Serializer::SerializeYAML, &Serializer::DeserializeYAML, iter, bs, {"YAML", "RAM"}, table_info);
    profile(&Serializer::SerializeMsgPack, &Serializer::DeserializeMsgPack, iter, bs, {"MsgPack", "RAM"}, table_info);

    table_info.add_row({"-----------","---------------","---------","---------------------","----------------------"});

    profile(&Serializer::SerializeBinaryToFile, &Serializer::DeserializeBinaryFromFile, iter, bs, {"Binary (Boost)", "File"}, table_info);
    profile(&Serializer::SerializeXMLToFile, &Serializer::DeserializeXMLFromFile, iter, bs, {"XML", "File"}, table_info);
    profile(&Serializer::SerializeTextToFile, &Serializer::DeserializeTextFromFile, iter, bs, {"Raw text", "File"}, table_info);
    profile(&Serializer::SerializeJSONToFile, &Serializer::DeserializeJSONFromFile, iter, bs,{"JSON", "File"}, table_info);
    profile(&Serializer::SerializeProtobufToFile, &Serializer::DeserializeProtobufFromFile, iter, bs, {"Protobuf", "File"}, table_info);
    profile(&Serializer::SerializeAvroToFile, &Serializer::DeserializeAvroFromFile, iter, bs, {"Avro", "File"}, table_info);
    profile(&Serializer::SerializeYAMLToFile, &Serializer::DeserializeYAMLFromFile, iter, bs, {"YAML", "File"}, table_info);
    profile(&Serializer::SerializeMsgPackToFile, &Serializer::DeserializeMsgPackFromFile, iter, bs, {"MsgPack", "File"}, table_info);
    std::cout << "Serialization finished." << std::endl;

    std::cout << table_info << std::endl;
    return 0;
}





