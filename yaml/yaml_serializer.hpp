#ifndef SERIALIZATION_YAML_YAML_SERIALIZER_H_
#define SERIALIZATION_YAML_YAML_SERIALIZER_H_

#include <c4/yml/std/map.hpp>
#include <c4/yml/std/string.hpp>

#include "struct.hpp"

bool read(c4::yml::NodeRef const& n, DataStruct *data_struct) {
    n["str"] >> data_struct->str;
    n["int_num"] >> data_struct->int_num;
    n["double_num"] >> data_struct->double_num;
    n["v_int"] >> data_struct->v_int;
    n["map_str_str"] >> data_struct->map_str_str;
    n["map_map"] >> data_struct->map_map;
    n["map_vector_map"] >> data_struct->map_vector_map;
    return true;
}

bool write(c4::yml::NodeRef *n, const DataStruct& data_struct) {
    *n |= c4::yml::MAP;

    c4::yml::NodeRef ch = n->append_child();
    ch.set_key("str");
    ch.set_val_serialized(data_struct.str);

    ch = n->append_child();
    ch.set_key("int_num");
    ch.set_val_serialized(data_struct.int_num);

    ch = n->append_child();
    ch.set_key("double_num");
    ch.set_val_serialized(data_struct.double_num);

    ch = n->append_child();
    ch.set_key("v_int");
    write(&ch, data_struct.v_int);

    ch = n->append_child();
    ch.set_key("map_str_str");
    write(&ch, data_struct.map_str_str);

    ch = n->append_child();
    ch.set_key("map_map");
    write(&ch, data_struct.map_map);

    ch = n->append_child();
    ch.set_key("map_vector_map");
    write(&ch, data_struct.map_vector_map);
    return true;
}

#endif // SERIALIZATION_YAML_YAML_SERIALIZER_H_