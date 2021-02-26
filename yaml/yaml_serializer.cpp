#include "serializer.hpp"

#include <fstream>

#include "yaml_serializer.hpp"

void Serializer::SerializeYAML() {
    current_type = SerializerType::Yaml;
    current_mode = SerializerMode::RAM;
    tree.clear();
    tree.rootref() << data_struct;
}

void Serializer::DeserializeYAML() {
    current_type = SerializerType::Yaml;
    current_mode = SerializerMode::RAM;
    DataStruct data_struct_new;
    tree.rootref() >> data_struct_new;
}

void Serializer::SerializeYAMLToFile() {
    current_type = SerializerType::Yaml;
    current_mode = SerializerMode::File;
    filename = "demofile.yaml";
    std::ofstream ofs((filepath + filename).c_str());
    if (!ofs.is_open())
        throw std::runtime_error("Cannot open " + filename);
    tree.clear();
    tree.rootref() << data_struct;
    ofs << tree;
}

void Serializer::DeserializeYAMLFromFile() {
    current_type = SerializerType::Yaml;
    current_mode = SerializerMode::File;
    filename = "demofile.yaml";
    std::ifstream ifs((filepath + filename).c_str());
    if (!ifs.is_open())
        throw std::runtime_error("Cannot open " + filename);
    std::stringstream buffer;
    buffer << ifs.rdbuf();
    ryml::Tree tree_new = ryml::parse(c4::to_csubstr(buffer.str()));

    DataStruct data_struct_new;
    tree_new.rootref() >> data_struct_new;
}
