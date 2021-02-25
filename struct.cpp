#include "struct.hpp"

#include <ctime>
#include <iostream>
#include <climits>

std::string GenerateRandomString(size_t size) {
    std::string res;
    for (size_t i = 0; i < size; ++i) {
        char c = (char) ('a' + rand() % 26); // random char from ascii 97 - 'a' to 122 - 'z'
        res += c;
    }
    return res;
}

void FillVector(std::vector<int>& v, size_t vec_size) {
    for (size_t i = 0; i < vec_size; ++i) {
        v.push_back(rand() % INT_MAX);
    }
}

void FillMap(std::map<std::string, std::string>& m, size_t map_size, size_t string_size) {
    for (size_t i = 0; i < map_size; ++i) {
        m[GenerateRandomString(string_size)] = GenerateRandomString(string_size);
    }
}

void FillMapMap(std::map<std::string, std::map<std::string, int>>& m,
                size_t map_size, size_t nested_map_size, size_t string_size) {
    for (size_t i = 0; i < map_size; ++i) {
        std::map<std::string, int> p;
        for (size_t j = 0; j < nested_map_size; ++j) {
            p[GenerateRandomString(string_size)] = rand() % INT_MAX;
        }
        m[GenerateRandomString(string_size)] = p;
    }
}

void FillMapVectorMap(std::map<std::string, std::vector<std::map<std::string, std::string>>>& m,
                      size_t map_size, size_t vector_size, size_t second_map_size, size_t string_size) {
    for (size_t i = 0; i < map_size; ++i) {
        std::vector<std::map<std::string, std::string>> v;
        for (size_t j = 0; j < vector_size; ++j) {
            std::map<std::string, std::string> second_map;
            FillMap(second_map, second_map_size, string_size);
            v.push_back(second_map);
        }
        m[GenerateRandomString(string_size)] = v;
    }
}

DataStruct GetSimpleStruct() {
    DataStruct data_struct;
    data_struct.str = "Hello From Slava!";
    data_struct.int_num = 42;
    data_struct.double_num = 3.1415926;
    data_struct.v_int = std::vector<int>({1, 2, 3, 4, 5});
    data_struct.map_str_str = std::map<std::string, std::string>
    {
        {"statusCode", "200"},
        {"message", "i am ok"}
    };
    data_struct.map_map = std::map<std::string, std::map<std::string, int>>
    {
        {"Jack",
            {{"age", 25}, {"birthYear", 1996}}
        },
        {"Mary",
            {{"age", 22}, {"birthYear", 1999}}
        }
    };
    data_struct.map_vector_map = std::map<std::string, std::vector<std::map<std::string, std::string>>>
    {
        {"requests",
            {
                {{"method", "POST"}, {"data", "post it"}},
                {{"method", "GET"}, {"data", "get me some"}},
                {{"method", "PUT"}, {"data", "put it or die"}}
            }
        },
        { "responses",
            {
                {{"statusCode", "400"}, {"message", "loh"}},
                {{"statusCode", "200"}, {"message", "ok, boy"}},
                {{"statusCode", "418"}, {"message", "I'm a teapot"}}
            }
        }
    };
    return data_struct;
}

DataStruct GenerateStruct(StructSize size) {
    // TODO: to change randomization method later
    srand(time(nullptr)); // use current time as seed for random generator
    DataStruct data_struct;
    data_struct.str = "Test string: Hello From Slava!";
    data_struct.int_num = 42;
    data_struct.double_num = 3.1415926;
    size_t string_size, vec_size, map_size, nested_map_size;
    if (size == StructSize::Small) { // configuring size for different scale of D
        string_size = 20, vec_size = 40, map_size = 80, nested_map_size = 15;
    } else if (size == StructSize::Medium) {
        string_size = 100, vec_size = 130, map_size = 50, nested_map_size = 30;
    } else {
        string_size = 200, vec_size = 200, map_size = 100, nested_map_size = 50;
    }
    FillVector(data_struct.v_int, vec_size);
    FillMap(data_struct.map_str_str, map_size, string_size);
    FillMapMap(data_struct.map_map, map_size, nested_map_size, string_size);
    FillMapVectorMap(data_struct.map_vector_map, map_size, vec_size, nested_map_size, string_size);
    return data_struct;
}

proto::DataStruct GenerateProtoMessage(const DataStruct& data_struct) {
    proto::DataStruct ds_message;
    ds_message.set_str(data_struct.str);
    ds_message.set_int_num(data_struct.int_num);
    ds_message.set_double_num(data_struct.double_num);
    *ds_message.mutable_v_int() = {data_struct.v_int.begin(), data_struct.v_int.end()};

    for (const auto& [key, value] : data_struct.map_str_str) {
        proto::DataStruct::BasicMap* bm = ds_message.add_map_str_str();
        bm->set_key(key);
        bm->set_value(value);
    }

    for (const auto& [key, nest_map] : data_struct.map_map) {
        proto::DataStruct::MapMap* mm = ds_message.add_map_map();
        mm->set_key(key);
        for (const auto& [second_key, value] : nest_map) {
            proto::DataStruct::SecondBasicMap* bm_tmp = mm->add_value();
            bm_tmp->set_key(second_key);
            bm_tmp->set_value(value);
        }
    }

    for (const auto& [key, vec_map] : data_struct.map_vector_map) {
        proto::DataStruct::MapVectorMap* vmv = ds_message.add_map_vector_map();
        vmv->set_key(key);
        for (const auto& map_ : vec_map) {
            proto::DataStruct::VectorMap* vm = vmv->add_value();
            for (const auto& [second_key, value] : map_) {
                proto::DataStruct::BasicMap* bm_tmp_ = vm->add_vm();
                bm_tmp_->set_key(second_key);
                bm_tmp_->set_value(value);
            }
        }
    }

    return ds_message;
}