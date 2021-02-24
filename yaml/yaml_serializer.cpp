#include "yaml_serializer.hpp"

#include "serializer.hpp"

void Serializer::SerializeYAML() {
    current_type = SerializerType::Yaml;
    current_mode = SerializerMode::RAM;
    yaml_node_out.reset();
    yaml_node_out = data_struct;
}

void Serializer::DeserializeYAML() {
    current_type = SerializerType::Yaml;
    current_mode = SerializerMode::RAM;
    DataStruct data_struct_new = yaml_node_out.as<DataStruct>();
}

void Serializer::SerializeYAMLToFile() {
    current_type = SerializerType::Yaml;
    current_mode = SerializerMode::File;
    filename = "demofile.yaml";
    ofs.open((filepath + filename).c_str());
    if (!ofs.is_open())
        throw std::runtime_error("Cannot open " + filename);
    yaml_node_out.reset();
    yaml_node_out = data_struct;
    ofs << yaml_node_out;
    ofs.close();
}

void Serializer::DeserializeYAMLFromFile() {
    current_type = SerializerType::Yaml;
    current_mode = SerializerMode::File;
    filename = "demofile.yaml";
    YAML::Node config = YAML::LoadFile((filepath + filename).c_str());
    if (!config) {
        throw std::runtime_error("Cannot open " + filename);
    }
    DataStruct data_struct_new = config.as<DataStruct>();
}


